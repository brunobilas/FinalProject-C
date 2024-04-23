#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGTH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);

    SDL_Rect player = (SDL_Rect){50, 50, 50, 100};
    player.x += 100;
    int speed = 2;


    SDL_Rect enemy = (SDL_Rect){50, 250, 50, 50};

    SDL_Event event;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&event)){ //loop to quit or not quit
            if (event.type == SDL_QUIT){
                quit = true;
            }
        }

        // Set render color to xxx
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        // Clear the window with the render color (clear previous frame)
        SDL_RenderClear(renderer);

        if(state[SDL_SCANCODE_D]) {
            player.x += speed;
        }

         if(state[SDL_SCANCODE_A]) {
            player.x -= speed;
        }

        if(state[SDL_SCANCODE_S]) {
            player.y += speed;
        }

        if(state[SDL_SCANCODE_W]) {
            player.y -= speed;
        }


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player);

        if(SDL_HasIntersection(&player, &enemy) == SDL_TRUE) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &enemy);
        }

        else{
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &enemy);
        }


        // Update the screen (load next frame with current content)
        SDL_RenderPresent(renderer);

    // SDL_Rect

    }

    // Clean up resources (shit that happens when you close the program (when the quit loop is true))
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}