#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#undef main

#define WIDTH 1000
#define HEIGHT 600

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Init Failed: %s", SDL_GetError());
        return -1;
    }

    SDL_Window* win = SDL_CreateWindow(
        "TestWindow",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);
    SDL_Rect rect = { 100, 100, 100, 100 };

    srand(static_cast<unsigned int>(time(0))); // Cast time_t to unsigned int
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;
    int8_t dx = 8;
    int8_t dy = 10;

    int x = rect.x + rect.w / 2;
    int y = rect.y + rect.h / 2;

    SDL_Event event;
    while (1)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
        }

        SDL_RenderClear(renderer);

        rect.x += dx;
        x = rect.x + rect.w / 2;
        if (rect.x + rect.w >= WIDTH || rect.x <= 0)
        {
            dx = -dx;
            rect.y += dy;
            y = rect.y + rect.h / 2;
            if (rect.y + rect.h >= HEIGHT || rect.y <= 0)
            {
                dy = -dy;
            }

            r = rand() % 256;
            g = rand() % 256;
            b = rand() % 256;
        }

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int i = rect.x; i < rect.x + rect.w; i++)
        {
            for (int j = rect.y; j < rect.y + rect.h; j++)
            {
                if ((i - x) * (i - x) + (j - y) * (j - y) > rect.w * rect.h / 4)
                {
                    SDL_RenderDrawPoint(renderer, i, j);
                }
            }
        }
        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
