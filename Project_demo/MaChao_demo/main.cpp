#include <SDL.h>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int RECT_SIZE = 50;

int main(int argc, char* argv[]) {
    // 初始化 SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // 创建窗口
    SDL_Window* window = SDL_CreateWindow("SDL2 Game",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // 方块位置
    SDL_Rect rect = { (WINDOW_WIDTH - RECT_SIZE) / 2, (WINDOW_HEIGHT - RECT_SIZE) / 2, RECT_SIZE, RECT_SIZE };

    // 游戏主循环
    bool running = true;
    SDL_Event event;

    while (running) {
        // 处理事件
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // 获取键盘状态
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_UP]) rect.y -= 5;
        if (state[SDL_SCANCODE_DOWN]) rect.y += 5;
        if (state[SDL_SCANCODE_LEFT]) rect.x -= 5;
        if (state[SDL_SCANCODE_RIGHT]) rect.x += 5;

        // 确保方块不移出窗口
        if (rect.x < 0) rect.x = 0;
        if (rect.x > WINDOW_WIDTH - RECT_SIZE) rect.x = WINDOW_WIDTH - RECT_SIZE;
        if (rect.y < 0) rect.y = 0;
        if (rect.y > WINDOW_HEIGHT - RECT_SIZE) rect.y = WINDOW_HEIGHT - RECT_SIZE;

        // 清空屏幕
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 黑色
        SDL_RenderClear(renderer);

        // 绘制方块
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 红色
        SDL_RenderFillRect(renderer, &rect);

        // 显示渲染结果
        SDL_RenderPresent(renderer);
    }

    // 清理
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
