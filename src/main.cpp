#include <sycl/sycl.hpp>
#include <SDL2/SDL.h>
#include <iostream>

#include "Actor.hpp"
#include "Room.hpp"
#include "MathHelper.hpp"
#include "DifferentialEq.hpp"
#include "VectorMaths.hpp"

constexpr int WIDTH = 9; // metres
constexpr int HEIGHT = 9; // metres
constexpr int SCALE = 100;
constexpr int DELAY = 0;

using vecType = std::array<float, 2>;

void init(SDL_Window* &win, SDL_Renderer* &render, std::vector<Actor> &actors) {
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("SYCL Crowd Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * SCALE, HEIGHT * SCALE, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            actors.push_back(Actor{{float(0.5 + (i * 0.5)), float(0.5 + (j * 0.5))},
                    {0.01, 0.01}, 
                    {0.02, 0.02},
                    {float(6.5 + (i * 0.5)), float(6.5 + (j * 0.5))},
                    50, 0.05, false, {255, 0, 0}});
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            actors.push_back(Actor{{float(6.5 + (i * 0.5)), float(0.5 + (j * 0.5))},
                    {0.01, 0.01}, 
                    {0.02, 0.02},
                    {float(0.5 + (i * 0.5)), float(6.5 + (j * 0.5))},
                    50, 0.05, false, {0, 255, 0}});
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            actors.push_back(Actor{{float(6.5 + (i * 0.5)), float(6.5 + (j * 0.5))},
                    {0.01, 0.01}, 
                    {0.02, 0.02},
                    {float(0.5 + (i * 0.5)), float(0.5 + (j * 0.5))},
                    50, 0.05, false, {0, 0, 255}});
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            actors.push_back(Actor{{float(0.5 + (i * 0.5)), float(6.5 + (j * 0.5))},
                    {0.01, 0.01}, 
                    {0.02, 0.02},
                    {float(6.5 + (i * 0.5)), float(0.5 + (j * 0.5))},
                    50, 0.05, false, {150, 150, 150}});
        }
    }
}

void drawCircle(SDL_Renderer* &render, SDL_Point center, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(render, center.x + dx, center.y + dy);
            }
        }
    }
}

void update(sycl::queue myQueue, std::vector<Actor> &actors, Room room) {
    auto actorBuf = sycl::buffer<Actor>(actors.data(), actors.size());

    auto walls = room.getWalls();
    auto wallsBuf = sycl::buffer<std::array<vecType, 2>>(walls.data(), walls.size());

    myQueue.submit([&](sycl::handler& cgh) {
        auto actorAcc = actorBuf.get_access<sycl::access::mode::read_write>(cgh);

        auto wallsAcc = wallsBuf.get_access<sycl::access::mode::read>(cgh);

        auto out = sycl::stream{1024, 768, cgh};

        cgh.parallel_for(sycl::range<1>{actors.size()}, [=](sycl::id<1> index) {
            if (!actorAcc[index].getAtDestination()) {
                differentialEq(index, actorAcc, wallsAcc, out);
            }
        });
    }).wait();
}

void draw(SDL_Renderer* &render, std::vector<Actor> actors, Room room) {
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);

    for (Actor actor : actors) {
        SDL_Point pos = {int(actor.getPos()[0] * SCALE), int(actor.getPos()[1] * SCALE)};
        SDL_Color actorColor = {Uint8(actor.getColor()[0]), Uint8(actor.getColor()[1]), Uint8(actor.getColor()[2]), 255};
        drawCircle(render, pos, actor.getRadius() * SCALE, actorColor);
    }

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    auto walls = room.getWalls();
    for (auto wall : walls) {
        SDL_RenderDrawLine(render, wall[0][0] * SCALE, wall[0][1] * SCALE, wall[1][0] * SCALE, wall[1][1] * SCALE);
    }

    SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
    SDL_Rect r;
    r.x = 35; r.y = 195; r.w = 10; r.h = 10;
    SDL_RenderDrawRect(render, &r);

    SDL_RenderPresent(render);
}

void close(SDL_Window* win) {
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int main() {
    SDL_Window* win = NULL;
    SDL_Surface* surface = NULL;
    SDL_Renderer* render = NULL;

    std::vector<Actor> actors;
    Room room = Room({{vecType{3, 3}, vecType{4.25, 3}}, 
                      {vecType{4.25, 3}, vecType{4.25, 4.25}}, 
                      {vecType{4.25, 4.25}, vecType{3, 4.25}},
                      {vecType{3, 4.25}, vecType{3, 3}}, 
                      {vecType{4.75, 3}, vecType{6, 3}},
                      {vecType{6, 3}, vecType{6, 4.25}},
                      {vecType{6, 4.25}, vecType{4.75, 4.25}},
                      {vecType{4.75, 4.25}, vecType{4.75, 3}},
                      {vecType{3, 4.75}, vecType{4.25, 4.75}},
                      {vecType{4.25, 4.75}, vecType{4.25, 6}},
                      {vecType{4.25, 6}, vecType{3, 6}},
                      {vecType{3, 6}, vecType{3, 4.75}},
                      {vecType{4.75, 4.75}, vecType{6, 4.75}},
                      {vecType{6, 4.75}, vecType{6, 6}},
                      {vecType{6, 6}, vecType{4.75, 6}},
                      {vecType{4.75, 6}, vecType{4.75, 4.75}},
    });
    // Room room = Room({{vecType{2, 3.5}, vecType{6, 3.5}}});
    // Room room = Room({{vecType{3.5, 0.5}, vecType{4.5, 5.5}}});

    sycl::queue myQueue{sycl::gpu_selector()};

    init(win, render, actors);

    draw(render, actors, room);

    int delayCounter = 0;
    bool isQuit = false;
    SDL_Event event;

    while(!isQuit) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isQuit = true;
            }
        }
        if (delayCounter >= DELAY) {
            delayCounter = 0;
            update(myQueue, actors, room);
            draw(render, actors, room);
        }
        else {
            delayCounter++;
        }
    }

    close(win);
    return 0;
}
