#include <SDL.h>
#include <iostream>






// ���ڿ��
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// ��ҽ�ɫ��С���ٶ�
const int PLAYER_SIZE = 50;
const int PLAYER_SPEED = 5;

int main(int argc, char* argv[]) {
    // ��ʼ�� SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL ��ʼ��ʧ��: " << SDL_GetError() << std::endl;
        return 1;
    }

    // ��������
    SDL_Window* window = SDL_CreateWindow("Simple SDL2 Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        std::cerr << "���ڴ���ʧ��: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // ������Ⱦ��
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "��Ⱦ������ʧ��: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // ��ҳ�ʼλ��
    SDL_Rect player = { WINDOW_WIDTH / 2 - PLAYER_SIZE / 2, WINDOW_HEIGHT / 2 - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE };

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // �����¼�
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // ��������
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

        // ��ֹ����Ƴ����ڱ߽�
        if (player.x < 0) player.x = 0;
        if (player.x + PLAYER_SIZE > WINDOW_WIDTH) player.x = WINDOW_WIDTH - PLAYER_SIZE;
        if (player.y < 0) player.y = 0;
        if (player.y + PLAYER_SIZE > WINDOW_HEIGHT) player.y = WINDOW_HEIGHT - PLAYER_SIZE;

        // �����Ļ�����ñ�����ɫ
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // ������Ҿ��β�������ɫ
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player);

        // ������Ļ
        SDL_RenderPresent(renderer);

        // ����֡��
        SDL_Delay(16);  // ��Լÿ��60֡
    }

    // ������Դ
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}