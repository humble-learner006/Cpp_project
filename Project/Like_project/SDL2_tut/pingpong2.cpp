#include <SDL.h>
#include <iostream>

// Constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int RECT_WIDTH = 100;
const int RECT_HEIGHT = 20;
const float RECT_SPEED = 300.0f; // Pixels per second
const int BALL_SIZE = 15;
const float BALL_SPEED = 200.0f; // Pixels per second

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Ping Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;
    float rectX = (SCREEN_WIDTH - RECT_WIDTH) / 2;
    float rectY = SCREEN_HEIGHT - RECT_HEIGHT - 10;
    float ballX = SCREEN_WIDTH / 2;
    float ballY = SCREEN_HEIGHT / 2;
    float ballVelX = BALL_SPEED;
    float ballVelY = BALL_SPEED;
    int lives = 3;
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

        // Update ball position
        ballX += ballVelX * deltaTime;
        ballY += ballVelY * deltaTime;

        // Ball collision with walls
        if (ballX <= 0 || ballX >= SCREEN_WIDTH - BALL_SIZE) {
            ballVelX = -ballVelX;
        }
        if (ballY <= 0) {
            ballVelY = -ballVelY;
        }

        // Ball collision with paddle
        if (ballY + BALL_SIZE >= rectY && ballX + BALL_SIZE >= rectX && ballX <= rectX + RECT_WIDTH) {
            ballVelY = -ballVelY;
            ballY = rectY - BALL_SIZE; // Prevent ball from sticking to the paddle
        }

        // Ball missed the paddle
        if (ballY >= SCREEN_HEIGHT) {
            lives--;
            ballX = SCREEN_WIDTH / 2;
            ballY = SCREEN_HEIGHT / 2;
            ballVelY = BALL_SPEED;
            if (lives <= 0) {
                running = false;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render paddle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = { static_cast<int>(rectX), rectY, RECT_WIDTH, RECT_HEIGHT };
        SDL_RenderFillRect(renderer, &rect);

        // Render ball
        SDL_Rect ball = { static_cast<int>(ballX), static_cast<int>(ballY), BALL_SIZE, BALL_SIZE };
        SDL_RenderFillRect(renderer, &ball);

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