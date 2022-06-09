#include <CL/sycl.hpp>
#include <SDL2/SDL.h>
#include "Actor.hpp"
#include <iostream>

const int WIDTH = 8; // metres
const int HEIGHT = 6; // metres
const int SCALE = 100;

void init(SDL_Window* win, SDL_Renderer* render, std::vector<Actor> &actors) {
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("SYCL Crowd Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * SCALE, HEIGHT * SCALE, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    actors.push_back(Actor{{1,2}, {3,4}, {5,6}, 3, 4});
}

void drawCircle(SDL_Renderer* render, SDL_Point center, int radius, SDL_Color color) {
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

void draw(SDL_Renderer* render, std::vector<Actor> &actors) {
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);



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

    init(win, render, actors);

    draw(render, actors);

    Actor test = Actor({0, 2}, {3, 4}, {5,6}, 12, 3);

    bool isQuit = false;
    SDL_Event event;

    while(!isQuit) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isQuit = true;
            }
        }

        draw(render, actors);
    }

    close(win);
    return 0;
}