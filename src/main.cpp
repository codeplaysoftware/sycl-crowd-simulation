#include <CL/sycl.hpp>
#include <SDL2/SDL.h>
#include <iostream>

#include "Actor.hpp"
#include "Room.hpp"

const int WIDTH = 8; // metres
const int HEIGHT = 6; // metres
const int SCALE = 100;
const int DELAY = 10000;

void init(SDL_Window* &win, SDL_Renderer* &render, std::vector<Actor> &actors) {
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("SYCL Crowd Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * SCALE, HEIGHT * SCALE, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    actors.push_back(Actor{{1, 2}, {0.01, 0.01}, {0.02, 0.02}, 50, 0.05});
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

void update(std::vector<Actor> &actors) {
    for (auto &actor : actors) {
        actor.setPos({actor.getPos()[0] + actor.getVelocity()[0],
                      actor.getPos()[1] + actor.getVelocity()[1]});
    }
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
    for (std::array<float, 4> wall : room.getWalls()) {
        SDL_RenderDrawLine(render, wall[0] * SCALE, wall[1] * SCALE, wall[2] * SCALE, wall[3] * SCALE);
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
    Room room = Room({{0.5, 0.5, 0.5, 1.5}, {0.5, 2.5, 0.5, 5.5}, {0.5, 5.5, 7.5, 5.5}, {7.5, 5.5, 7.5, 0.5}, {7.5, 0.5, 0.5, 0.5}}, {});

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
            update(actors);
            draw(render, actors, room);
        }
        else {
            delayCounter++;
        }
    }

    close(win);
    return 0;
}