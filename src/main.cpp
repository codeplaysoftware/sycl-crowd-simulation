/***************************************************************************
 *
 *  Copyright (C) 2022 Codeplay Software Ltd.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  Codeplay's crowd-simulation
 *
 *  main.cpp
 *
 *  Description:
 *    SYCL implementation of social force model for crowd simulation
 * 
 **************************************************************************/

#ifndef PROFILING_MODE
#include <SDL2/SDL.h>
#endif
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
#ifdef STATS
#include "Stats.hpp"
#endif

uint GLOBALSEED;

void init(int &WIDTH, int &HEIGHT, int &SCALE, int &DELAY,
          std::array<int, 3> &BGCOLOR, std::array<int, 3> &WALLCOLOR,
          bool &HEATMAPENABLED,
          std::vector<Actor> &actors, Room &room, std::vector<Path> &paths,
          int argc, char **argv) {
    // Read from input file path JSON
    if (argc == 2) {
        std::string inputPath = argv[1];
        parseInputFile(inputPath, actors, room, paths, WIDTH, HEIGHT, SCALE,
                       DELAY, BGCOLOR, WALLCOLOR, HEATMAPENABLED);
    } else if (argc < 2) {
        throw std::invalid_argument(
            "Input configuration file must be supplied");
    } else {
        throw std::invalid_argument("Too many inputs were supplied");
    }

    // Seed RNG with current time in seconds
    GLOBALSEED = uint(time(0));
    // Seed each actor's RNG using global seed
    for (auto actor : actors) {
        GLOBALSEED = randXorShift(GLOBALSEED);
        actor.setSeed(GLOBALSEED);
    }
}

#ifndef PROFILING_MODE
void initSDL(int WIDTH, int HEIGHT, int SCALE, SDL_Window *&win,
             SDL_Renderer *&render) {
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

void draw(int SCALE, std::array<int, 3> BGCOLOR, std::array<int, 3> WALLCOLOR,
          SDL_Renderer *&render,
          sycl::host_accessor<Actor, 1, sycl::access::mode::read> actors,
          Room room) {
    SDL_SetRenderDrawColor(render, BGCOLOR[0], BGCOLOR[1], BGCOLOR[2], 255);
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

    SDL_SetRenderDrawColor(render, WALLCOLOR[0], WALLCOLOR[1], WALLCOLOR[2],
                           255);
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
#endif

void update(sycl::queue &myQueue, sycl::buffer<Actor> &actorBuf,
            sycl::buffer<std::array<sycl::float2, 2>> &wallsBuf,
            sycl::buffer<Path> &pathsBuf, sycl::buffer<bool> &heatmapEnabledBuf) {
    try {
        myQueue.submit([&](sycl::handler &cgh) {
            auto actorAcc =
                actorBuf.get_access<sycl::access::mode::read_write>(cgh);

            auto wallsAcc = wallsBuf.get_access<sycl::access::mode::read>(cgh);

            auto pathsAcc = pathsBuf.get_access<sycl::access::mode::read>(cgh);

            auto heatmapEnabledAcc = heatmapEnabledBuf.get_access<sycl::access::mode::read>(cgh);

            cgh.parallel_for(
                sycl::range<1>{actorAcc.size()}, [=](sycl::id<1> index) {
                    if (!actorAcc[index].getAtDestination()) {
                        differentialEq(index, actorAcc, wallsAcc, pathsAcc, heatmapEnabledAcc);
                    }
                });
        });
        myQueue.throw_asynchronous();
    } catch (const sycl::exception &e) {
        std::cout << "SYCL exception caught:\n" << e.what() << "\n[update]";
    }
}

void updateBBox(sycl::queue &myQueue, sycl::buffer<Actor> &actorBuf) {
    try {
        myQueue.submit([&](sycl::handler &cgh) {
            auto actorAcc =
                actorBuf.get_access<sycl::access::mode::read_write>(cgh);

            cgh.parallel_for(sycl::range<1>{actorAcc.size()},
                             [=](sycl::id<1> index) {
                                 Actor *currentActor = &actorAcc[index];
                                 sycl::float2 pos = currentActor->getPos();
                                 int row = sycl::floor(pos[0]);
                                 int col = sycl::floor(pos[1]);
                                 currentActor->setBBox({row, col});
                             });
        });
        myQueue.throw_asynchronous();
    } catch (const sycl::exception &e) {
        std::cout << "SYCL exception caught:\n" << e.what() << "\n[updateBBox]";
    }
}

int main(int argc, char *argv[]) {
    //testsycl::float2();

    int WIDTH;  // metres
    int HEIGHT; // metres
    int SCALE;
    int DELAY;
    bool HEATMAPENABLED;

    std::array<int, 3> BGCOLOR;
    std::array<int, 3> WALLCOLOR;

    std::vector<Actor> actors;
    Room room = Room({});
    std::vector<Path> paths;

    auto asyncHandler = [&](sycl::exception_list exceptionList) {
        for (auto &e : exceptionList) {
            std::rethrow_exception(e);
        }
    };

    sycl::queue myQueue{sycl::gpu_selector(), asyncHandler};

    init(WIDTH, HEIGHT, SCALE, DELAY, BGCOLOR, WALLCOLOR, HEATMAPENABLED, actors, room, paths,
         argc, argv);

#ifndef PROFILING_MODE
    SDL_Window *win;
    SDL_Renderer *render;
    initSDL(WIDTH, HEIGHT, SCALE, win, render);
#endif

    // Buffer creation
    auto actorBuf = sycl::buffer<Actor>(actors.data(), actors.size());
    auto walls = room.getWalls();
    auto wallsBuf =
        sycl::buffer<std::array<sycl::float2, 2>>(walls.data(), walls.size());
    wallsBuf.set_final_data(nullptr);
    auto pathsBuf = sycl::buffer<Path>(paths.data(), paths.size());
    pathsBuf.set_final_data(nullptr);
    auto heatmapEnableBuf = sycl::buffer<bool>(&HEATMAPENABLED, 1);

    int delayCounter = 0;
    int updateBBoxCounter = 0;
    int timestepCounter = 0;
    bool isPause = false;
#ifndef PROFILING_MODE
    SDL_Event event;
    bool isQuit = false;
#endif

// Initialise stats variables if STATS flag is true
#ifdef STATS
    std::vector<float> averageForces;
    int updateStatsCounter = 49;
    auto startTime = std::chrono::high_resolution_clock::now();
    std::vector<std::array<int, 2>> destinationTimes;
    for (int x = 0; x < actors.size(); x++) {
        destinationTimes.push_back({0, 0});
    }
    std::vector<int> kernelDurations;
    auto globalStart = std::chrono::high_resolution_clock::now();
#endif

#ifdef PROFILING_MODE
    while (timestepCounter <= 500) {
#else
    while(!isQuit) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isQuit = true;
            } else if (event.type == SDL_KEYDOWN &&
                       event.key.keysym.sym == SDLK_SPACE) {
                isPause = !isPause;
            }
        }
#endif

        if (!isPause) {
            if (delayCounter >= DELAY) {
                delayCounter = 0;

#ifdef STATS
                auto kernelStart = std::chrono::high_resolution_clock::now();
#endif

                if (updateBBoxCounter <= 0) {
                    updateBBox(myQueue, actorBuf);
                    updateBBoxCounter = 20;
                }

                update(myQueue, actorBuf, wallsBuf, pathsBuf, heatmapEnableBuf);

#ifdef STATS
                auto kernelEnd = std::chrono::high_resolution_clock::now();
                auto kernelDuration =
                    std::chrono::duration_cast<std::chrono::microseconds>(
                        kernelEnd - kernelStart);
                kernelDurations.push_back(kernelDuration.count());

                if (updateStatsCounter >= 100) {
                    updateStats(myQueue, actorBuf, averageForces,
                                destinationTimes, startTime, timestepCounter);
                    updateStatsCounter = 0;
                } else {
                    updateStatsCounter++;
                }
#endif

                sycl::host_accessor<Actor, 1, sycl::access::mode::read>
                    actorHostAcc(actorBuf);

#ifndef PROFILING_MODE
                draw(SCALE, BGCOLOR, WALLCOLOR, render, actorHostAcc, room);
#endif

                updateBBoxCounter--;

                timestepCounter++;
            } else {
                delayCounter++;
            }
        }
    }

#ifdef STATS
    auto globalEnd = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        globalEnd - globalStart);

    finalizeStats(myQueue, averageForces, destinationTimes, kernelDurations,
                  actors.size(), duration.count());
#endif

#ifndef PROFILING_MODE
    close(win, render);
#endif

    return 0;
}
