#include <SDL2/SDL.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <sycl/sycl.hpp>

#include "Actor.hpp"
#include "DifferentialEq.hpp"
#include "MathHelper.hpp"
#include "ParseInputFile.hpp"
#include "Path.hpp"
#include "RandomNumber.hpp"
#include "Room.hpp"
#include "VectorMaths.hpp"

uint GLOBALSEED;

void init(int &SCALE, int &DELAY, SDL_Window *&win, SDL_Renderer *&render,
          std::vector<Actor> &actors, Room &room, std::vector<Path> &paths,
          int argc, char **argv) {
    int WIDTH;
    int HEIGHT;

    // Read from input file path JSON
    if (argc > 1) {
        std::string inputPath = argv[1];
        parseInputFile(inputPath, actors, room, paths, WIDTH, HEIGHT, SCALE,
                       DELAY);
    }

    // Seed RNG with current time in seconds
    GLOBALSEED = uint(time(0));
    for (auto actor : actors) {
        GLOBALSEED = randXorShift(GLOBALSEED);
        actor.setSeed(GLOBALSEED);
    }

    // Initialise SDL
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("SYCL Crowd Simulation", SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED, WIDTH * SCALE,
                           HEIGHT * SCALE, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

void drawCircle(SDL_Renderer *&render, SDL_Point center, int radius,
                SDL_Color color) {
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(render, center.x + dx, center.y + dy);
            }
        }
    }
}

void update(sycl::queue &myQueue, sycl::buffer<Actor> &actorBuf, sycl::buffer<std::array<vecType, 2>> &wallsBuf,
            sycl::buffer<Path> &pathsBuf) {
    try {
        myQueue
            .submit([&](sycl::handler &cgh) {
                auto actorAcc =
                    actorBuf.get_access<sycl::access::mode::read_write>(cgh);

                auto wallsAcc =
                    wallsBuf.get_access<sycl::access::mode::read>(cgh);

                auto pathsAcc =
                    pathsBuf.get_access<sycl::access::mode::read>(cgh);

                auto out = sycl::stream{1024, 768, cgh};

                cgh.parallel_for(
                    sycl::range<1>{actorAcc.size()}, [=](sycl::id<1> index) {
                        if (!actorAcc[index].getAtDestination()) {
                            differentialEq(index, actorAcc, wallsAcc, pathsAcc,
                                           out);
                        }
                    });
            })
            .wait_and_throw();
    } catch (const sycl::exception &e) {
        std::cout << "SYCL exception caught:\n" << e.what() << "\n[update]";
    }
}

void updateVariations(sycl::queue &myQueue, sycl::buffer<Actor> &actorBuf) {
    try {
        myQueue
            .submit([&](sycl::handler &cgh) {
                auto actorAcc =
                    actorBuf.get_access<sycl::access::mode::read_write>(cgh);

                cgh.parallel_for(
                    sycl::range<1>{actorAcc.size()}, [=](sycl::item<1> item) {
                        actorAcc[item.get_id()].refreshVariations();
                    });
            })
            .wait_and_throw();
    } catch (const sycl::exception &e) {
        std::cout << "SYCL exception caught:\n"
                  << e.what() << "\n[updateVariations]";
    }
}

void updateBBox(sycl::queue &myQueue, sycl::buffer<Actor> &actorBuf) {
    try {
        myQueue
            .submit([&](sycl::handler &cgh) {
                auto actorAcc =
                    actorBuf.get_access<sycl::access::mode::read_write>(cgh);

                cgh.parallel_for(sycl::range<1>{actorAcc.size()},
                                 [=](sycl::id<1> index) {
                                     Actor *currentActor = &actorAcc[index];
                                     vecType pos = currentActor->getPos();
                                     int row = sycl::floor(pos[0]);
                                     int col = sycl::floor(pos[1]);
                                     currentActor->setBBox({row, col});
                                 });
            })
            .wait_and_throw();
    } catch (const sycl::exception &e) {
        std::cout << "SYCL exception caught:\n" << e.what() << "\n[updateBBox]";
    }
}

void draw(int SCALE, SDL_Renderer *&render, sycl::host_accessor<Actor, 1, sycl::access::mode::read> actors,
          Room room) {
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);

    for (int i = 0; i < actors.size(); i++) {
        auto actor = actors[i];
        SDL_Point pos = {int(actor.getPos()[0] * SCALE),
                         int(actor.getPos()[1] * SCALE)};
        SDL_Color actorColor = {Uint8(actor.getColor()[0]),
                                Uint8(actor.getColor()[1]),
                                Uint8(actor.getColor()[2]), 255};
        drawCircle(render, pos, actor.getRadius() * SCALE, actorColor);
    }

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    auto walls = room.getWalls();
    for (auto wall : walls) {
        SDL_RenderDrawLine(render, wall[0][0] * SCALE, wall[0][1] * SCALE,
                           wall[1][0] * SCALE, wall[1][1] * SCALE);
    }

    SDL_RenderPresent(render);
}

void close(SDL_Window *win, SDL_Renderer *render) {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    int WIDTH;  // metres
    int HEIGHT; // metres
    int SCALE;
    int DELAY;

    SDL_Window *win;
    SDL_Renderer *render;

    std::vector<Actor> actors;
    Room room = Room({});
    std::vector<Path> paths;

    auto asyncHandler = [&](sycl::exception_list exceptionList) {
        for (auto &e : exceptionList) {
            std::rethrow_exception(e);
        }
    };

    sycl::queue myQueue{sycl::gpu_selector(), asyncHandler};

    init(SCALE, DELAY, win, render, actors, room, paths, argc, argv);

    // Buffer creation
    auto actorBuf = sycl::buffer<Actor>(actors.data(), actors.size());
    auto walls = room.getWalls();
    auto wallsBuf = sycl::buffer<std::array<vecType, 2>>(walls.data(), walls.size());
    auto pathsBuf = sycl::buffer<Path>(paths.data(), paths.size());

    int delayCounter = 0;
    int updateBBoxCounter = 0;
    bool isQuit = false;
    bool isPause = false;
    SDL_Event event;

    std::vector<int> executionTimes;

    while (!isQuit) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isQuit = true;
            } else if (event.type == SDL_KEYDOWN &&
                       event.key.keysym.sym == SDLK_SPACE) {
                isPause = !isPause;
            }
        }

        if (!isPause) {
            if (delayCounter >= DELAY) {
                delayCounter = 0;
                auto start = std::chrono::high_resolution_clock::now();

                if (updateBBoxCounter <= 0) {
                    updateBBox(myQueue, actorBuf);
                    updateBBoxCounter = 20;
                }

                updateVariations(myQueue, actorBuf);
                update(myQueue, actorBuf, wallsBuf, pathsBuf);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        end - start);
                executionTimes.push_back(duration.count());
                // std::cout << "fps: " << (1000.0f / duration.count()) <<
                // std::endl;

                sycl::host_accessor<Actor, 1, sycl::access::mode::read> actorHostAcc(actorBuf);

                draw(SCALE, render, actorHostAcc, room);
                updateBBoxCounter--;
            } else {
                delayCounter++;
            }
        }
    }

    // // For Profiling
    // int updateBBoxCounterr = 0;
    // for (int x = 0; x < 500; x++) {
    //     if (updateBBoxCounterr <= 0) {
    //         updateBBox(myQueue, actorBuf);
    //         updateBBoxCounterr = 20;
    //     }
    //     updateVariations(myQueue, actorBuf);
    //     update(myQueue, actorBuf, wallsBuf, pathsBuf);
    //     sycl::host_accessor<Actor, 1, sycl::access::mode::read> actorHostAcc(actorBuf);
    //     updateBBoxCounterr--;
    // }

    executionTimes.erase(executionTimes.begin());
    float count = static_cast<float>(executionTimes.size());
    float mean =
        std::accumulate(executionTimes.begin(), executionTimes.end(), 0.0) /
        count;
    std::cout << "Mean execution time: " << mean << std::endl;

    close(win, render);
    return 0;
}
