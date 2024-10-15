#include <SDL.h>
#include <iostream>






// 窗口宽高
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// 玩家角色大小和速度
const int PLAYER_SIZE = 50;
const int PLAYER_SPEED = 5;

int main(int argc, char* argv[]) {
    // 初始化 SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL 初始化失败: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 创建窗口
    SDL_Window* window = SDL_CreateWindow("Simple SDL2 Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        std::cerr << "窗口创建失败: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "渲染器创建失败: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 玩家初始位置
    SDL_Rect player = { WINDOW_WIDTH / 2 - PLAYER_SIZE / 2, WINDOW_HEIGHT / 2 - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE };

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // 处理事件
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // 键盘输入
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_UP]) {
            player.y -= PLAYER_SPEED;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            player.y += PLAYER_SPEED;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            player.x -= PLAYER_SPEED;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            player.x += PLAYER_SPEED;
        }

        // 防止玩家移出窗口边界
        if (player.x < 0) player.x = 0;
        if (player.x + PLAYER_SIZE > WINDOW_WIDTH) player.x = WINDOW_WIDTH - PLAYER_SIZE;
        if (player.y < 0) player.y = 0;
        if (player.y + PLAYER_SIZE > WINDOW_HEIGHT) player.y = WINDOW_HEIGHT - PLAYER_SIZE;

        // 清空屏幕并设置背景颜色
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 绘制玩家矩形并设置颜色
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player);

        // 更新屏幕
        SDL_RenderPresent(renderer);

        // 控制帧率
        SDL_Delay(16);  // 大约每秒60帧
    }

    // 清理资源
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}