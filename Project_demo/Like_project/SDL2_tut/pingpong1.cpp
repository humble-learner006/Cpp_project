#include <SDL.h>

// Constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int RECT_WIDTH = 100;
const int RECT_HEIGHT = 20;
const float RECT_SPEED = 300.0f; // Pixels per second

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Smooth Movement SDL2 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;
    float rectX = (SCREEN_WIDTH - RECT_WIDTH) / 2;
    float rectY = SCREEN_HEIGHT - RECT_HEIGHT - 10;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f; // Convert milliseconds to seconds
        lastTime = currentTime;

        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT]) {
            rectX -= RECT_SPEED * deltaTime;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            rectX += RECT_SPEED * deltaTime;
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render rectangle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = { static_cast<int>(rectX), rectY, RECT_WIDTH, RECT_HEIGHT };
        SDL_RenderFillRect(renderer, &rect);

        // Present renderer
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(1); // Small delay to prevent CPU overuse
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}