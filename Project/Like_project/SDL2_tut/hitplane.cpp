#include <SDL.h>

// Constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int RECT_WIDTH = 100;
const int RECT_HEIGHT = 20;
const int RECT_SPEED = 5;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Simple SDL2 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;
    int rectX = (SCREEN_WIDTH - RECT_WIDTH) / 2;
    int rectY = SCREEN_HEIGHT - RECT_HEIGHT - 10;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT) {
                    rectX -= RECT_SPEED;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                    rectX += RECT_SPEED;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render rectangle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = { rectX, rectY, RECT_WIDTH, RECT_HEIGHT };
        SDL_RenderFillRect(renderer, &rect);

        // Present renderer
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(5); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}