#include <CL/sycl.hpp>
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

SDL_Window* win = NULL;
SDL_Surface* surface = NULL;
SDL_Renderer* render = NULL;

const int WIDTH = 800;
const int HEIGHT = 600;

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("SYCL Crowd Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

void draw() {
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);

    SDL_RenderPresent(render);
}

void close() {
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int main() {
    init();

    draw();

    bool isQuit = false;
    SDL_Event event;

    while(!isQuit) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isQuit = true;
            }
        }

        draw();
    }

    close();
    return 0;
}