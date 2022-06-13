#include <sycl/sycl.hpp>
#include <SDL2/SDL.h>
#include <iostream>

#include "Actor.hpp"
#include "Room.hpp"
#include "MathHelper.hpp"
#include "DifferentialEq.hpp"
#include "GeometricVector.hpp"

constexpr int WIDTH = 8; // metres
constexpr int HEIGHT = 6; // metres
constexpr int SCALE = 100;
constexpr int DELAY = 10000;

void init(SDL_Window* &win, SDL_Renderer* &render, std::vector<Actor> &actors) {
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("SYCL Crowd Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * SCALE, HEIGHT * SCALE, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    actors.push_back(Actor{GeometricVector({4, 0}),
                           GeometricVector({0.01, 0.01}), 
                           GeometricVector({0.02, 0.02}),
                           GeometricVector({1, 2}),
                           50, 0.05});
    actors.push_back(Actor{GeometricVector({8, 6}), 
                           GeometricVector({-0.02, -0.02}),
                           GeometricVector({-0.03, -0.03}),
                           GeometricVector({1, 2}),
                           60, 0.08});

    // Make actor move towards destination
    actors[0].setVelocity(velToPoint(0.01, actors[0].getPos(), actors[0].getDestination()));
    actors[1].setVelocity(velToPoint(0.008, actors[1].getPos(), actors[1].getDestination()));
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

void update(std::vector<Actor> &actors, Room room) {
    sycl::queue myQueue{sycl::gpu_selector()};

    auto actorBuf = sycl::buffer<Actor>(actors.data(), actors.size());

    auto walls = room.getWalls();
    auto wallsBuf = sycl::buffer<std::array<float, 4>>(walls.data(), walls.size());

    myQueue.submit([&](sycl::handler& cgh) {
        auto actorAcc = actorBuf.get_access<sycl::access::mode::read_write>(cgh);

        auto wallsAcc = wallsBuf.get_access<sycl::access::mode::read_write>(cgh);

        auto out = sycl::stream{1024, 120, cgh};

        cgh.parallel_for(sycl::range<1>{actors.size()}, [=](sycl::id<1> index) {
            differentialEq(actorAcc[index], actorAcc, wallsAcc);
        });
    }).wait();

    myQueue.submit([&](sycl::handler& cgh) {
        auto actorAcc = actorBuf.get_access<sycl::access::mode::read_write>(cgh);

        cgh.parallel_for(sycl::range<1>{actors.size()}, [=](sycl::id<1> index) {
            Actor current = actorAcc[index];
            actorAcc[index].setPos(current.getPos() + current.getVelocity());
        });
    }).wait();
}

void draw(SDL_Renderer* &render, std::vector<Actor> actors, Room room) {
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);

    SDL_Color red = {255, 0, 0, 255};
    for (Actor actor : actors) {
        SDL_Point pos = {int(actor.getPos()[0] * SCALE), int(actor.getPos()[1] * SCALE)};
        drawCircle(render, pos, actor.getRadius() * SCALE, red);
    }

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    auto walls = room.getWalls();
    for (int x = 0; x < walls.size(); x++) {
        SDL_RenderDrawLine(render, walls[x][0] * SCALE, walls[x][1] * SCALE, walls[x][2] * SCALE, walls[x][3] * SCALE);
    }

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
    Room room = Room({{0.5, 0.5, 0.5, 1.5}, 
                      {0.5, 2.5, 0.5, 5.5}, 
                      {0.5, 5.5, 7.5, 5.5},
                      {7.5, 5.5, 7.5, 0.5}, 
                      {7.5, 0.5, 0.5, 0.5}
    });

    init(win, render, actors);

    draw(render, actors, room);

    int delayCounter = 0;
    bool isQuit = false;
    SDL_Event event;

    std::cout << distanceToWall(GeometricVector({-2, 4}), {1, 2, 4, 0});

    while(!isQuit) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isQuit = true;
            }
        }
        if (delayCounter >= DELAY) {
            delayCounter = 0;
            update(actors, room);
            draw(render, actors, room);
        }
        else {
            delayCounter++;
        }
    }

    close(win);
    return 0;
}
