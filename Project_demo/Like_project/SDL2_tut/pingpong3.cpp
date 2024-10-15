#include <SDL.h>
#include <iostream>
#include <vector>

// Constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int RECT_WIDTH = 100;
const int RECT_HEIGHT = 20;
const float RECT_SPEED = 300.0f; // Pixels per second
const int BALL_SIZE = 15;
const float BALL_SPEED = 200.0f; // Pixels per second
const int NUM_BALLS = 10;

struct Ball {
    float x, y;
    float velX, velY;
    bool bounced;
};

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Ping Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;
    float rectX = (SCREEN_WIDTH - RECT_WIDTH) / 2;
    float rectY = SCREEN_HEIGHT - RECT_HEIGHT - 10;
    std::vector<Ball> balls(NUM_BALLS);
    int lives = 3;
    Uint32 lastTime = SDL_GetTicks();

    // Initialize balls
    for (int i = 0; i < NUM_BALLS; ++i) {
        balls[i].x = SCREEN_WIDTH / 2;
        balls[i].y = SCREEN_HEIGHT / 2;
        balls[i].velX = BALL_SPEED * (i % 2 == 0 ? 1 : -1); // Alternate direction
        balls[i].velY = BALL_SPEED;
        balls[i].bounced = false;
    }

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

        // Ensure the paddle stays within the screen bounds
        if (rectX < 0) {
            rectX = 0;
        }
        if (rectX > SCREEN_WIDTH - RECT_WIDTH) {
            rectX = SCREEN_WIDTH - RECT_WIDTH;
        }

        // Update ball positions
        for (auto &ball : balls) {
            ball.x += ball.velX * deltaTime;
            ball.y += ball.velY * deltaTime;

            // Ball collision with paddle
            if (!ball.bounced && ball.y + BALL_SIZE >= rectY && ball.x + BALL_SIZE >= rectX && ball.x <= rectX + RECT_WIDTH) {
                ball.velY = -ball.velY;
                ball.y = rectY - BALL_SIZE; // Prevent ball from sticking to the paddle
                ball.bounced = true;
            }

            // Ball missed the paddle
            if (ball.y >= SCREEN_HEIGHT) {
                lives--;
                ball.x = SCREEN_WIDTH / 2;
                ball.y = SCREEN_HEIGHT / 2;
                ball.velY = BALL_SPEED;
                ball.bounced = false;
                if (lives <= 0) {
                    running = false;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render paddle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = { static_cast<int>(rectX), rectY, RECT_WIDTH, RECT_HEIGHT };
        SDL_RenderFillRect(renderer, &rect);

        // Render balls
        for (const auto &ball : balls) {
            SDL_Rect ballRect = { static_cast<int>(ball.x), static_cast<int>(ball.y), BALL_SIZE, BALL_SIZE };
            SDL_RenderFillRect(renderer, &ballRect);
        }

        // Present renderer
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(1); // Small delay to prevent CPU overuse
    }

    // Game over screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect gameOverRect = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 100 };
    SDL_RenderFillRect(renderer, &gameOverRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000); // Show "Game Over" for 3 seconds

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}