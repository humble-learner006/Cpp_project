#include <SDL.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <chrono>

// 定义窗口大小
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// 定义玩家方块大小和速度
const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 50;
const int PLAYER_SPEED = 5;

// 定义障碍物大小和数量
const int OBSTACLE_WIDTH = 50;
const int OBSTACLE_HEIGHT = 50;
const int OBSTACLE_COUNT = 5;
const int OBSTACLE_SPEED = 3; // 障碍物移动速度

bool gameOver = false; // 用于判断游戏是否结束

// 初始化 SDL
bool init(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Block Avoidance Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

// 处理键盘事件
void handleEvents(bool& running, SDL_Rect& player) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (!gameOver) { // 只有游戏没有结束时，才处理玩家移动
        if (state[SDL_SCANCODE_UP]) {
            player.y -= PLAYER_SPEED;
            if (player.y < 0) player.y = 0;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            player.y += PLAYER_SPEED;
            if (player.y + PLAYER_HEIGHT > WINDOW_HEIGHT) player.y = WINDOW_HEIGHT - PLAYER_HEIGHT;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            player.x -= PLAYER_SPEED;
            if (player.x < 0) player.x = 0;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            player.x += PLAYER_SPEED;
            if (player.x + PLAYER_WIDTH > WINDOW_WIDTH) player.x = WINDOW_WIDTH - PLAYER_WIDTH;
        }
    }
}

// 检测碰撞
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}

// 渲染游戏
void render(SDL_Renderer* renderer, SDL_Rect& player, std::vector<SDL_Rect>& obstacles) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // 背景颜色：黑色
    SDL_RenderClear(renderer);

    // 绘制玩家（蓝色方块）
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &player);

    // 绘制障碍物（红色方块）
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (const SDL_Rect& obstacle : obstacles) {
        SDL_RenderFillRect(renderer, &obstacle);
    }

    // 如果游戏结束，显示 "Game Over" 字样
    if (gameOver) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // 白色背景
        SDL_Rect gameOverRect = {WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 50, 200, 100}; // "Game Over" 背景
        SDL_RenderFillRect(renderer, &gameOverRect);

        // 用文字显示 "Game Over"
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 黑色文字
        SDL_RenderDrawRect(renderer, &gameOverRect); // 绘制边框
        // 这里我们使用简单的矩形来代替文本
        // 实际应用中可以使用 SDL_ttf 库来绘制文本

        // 在中心位置绘制文本的矩形
        SDL_Rect textRect = {WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 25, 100, 50};
        SDL_RenderDrawRect(renderer, &textRect); // 绘制一个黑色矩形来模拟文本
    }

    SDL_RenderPresent(renderer);
}

// 更新障碍物状态（随机移动）
void updateObstacles(std::vector<SDL_Rect>& obstacles, std::vector<int>& velX, std::vector<int>& velY) {
    for (size_t i = 0; i < obstacles.size(); ++i) {
        obstacles[i].x += velX[i];
        obstacles[i].y += velY[i];

        // 碰到边界反弹
        if (obstacles[i].x < 0 || obstacles[i].x + OBSTACLE_WIDTH > WINDOW_WIDTH) {
            velX[i] = -velX[i];
        }
        if (obstacles[i].y < 0 || obstacles[i].y + OBSTACLE_HEIGHT > WINDOW_HEIGHT) {
            velY[i] = -velY[i];
        }
    }
}

// 关闭 SDL
void close(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

#undef main
int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!init(window, renderer)) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    // 玩家方块初始位置
    SDL_Rect player = {100, WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT};

    // 障碍物初始位置和速度
    std::vector<SDL_Rect> obstacles(OBSTACLE_COUNT);
    std::vector<int> velX(OBSTACLE_COUNT);
    std::vector<int> velY(OBSTACLE_COUNT);
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < OBSTACLE_COUNT; ++i) {
        obstacles[i] = {rand() % (WINDOW_WIDTH - OBSTACLE_WIDTH), rand() % (WINDOW_HEIGHT - OBSTACLE_HEIGHT), OBSTACLE_WIDTH, OBSTACLE_HEIGHT};
        velX[i] = (rand() % 2 == 0 ? 1 : -1) * OBSTACLE_SPEED;
        velY[i] = (rand() % 2 == 0 ? 1 : -1) * OBSTACLE_SPEED;
    }

    bool running = true;

    std::thread consoleThread([&running]() {
        // 在控制台输出游戏状态
        while (running) {
            std::cout << "Game is running..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1)); // 每秒输出一次
        }
        std::cout << "Game Over! The program will exit." << std::endl; // 游戏结束时输出
    });

    while (running) {
        handleEvents(running, player); // 处理玩家输入

        if (!gameOver) {
            updateObstacles(obstacles, velX, velY); // 更新障碍物位置
        }

        // 检测玩家是否碰到障碍物
        for (const SDL_Rect& obstacle : obstacles) {
            if (checkCollision(player, obstacle)) {
                gameOver = true; // 游戏结束
                break;
            }
        }

        render(renderer, player, obstacles); // 渲染游戏画面

        SDL_Delay(16); // 控制帧率，大约 60 FPS
    }

    // 等待控制台线程完成
    consoleThread.join();

    close(window, renderer);

    return 0;
}
