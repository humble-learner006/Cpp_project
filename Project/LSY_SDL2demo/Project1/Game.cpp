#include "Game.h"
#include <iostream>
#include "TextureManager.h"
#include "GameObject.h"

using namespace std;

GameObject* player;

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	// 初始化时可选择是否全屏
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	// 确认SDL是否成功初始化并建立窗口
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "Subsystems Initialized!..." << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			cout << "Window created!" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 102, 102, 255, 0);
			cout << "Renderer created" << endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	player = new GameObject("sprite.png", renderer,0, 300);

}

void Game::handleEvent() {
	//键盘控制移动优化，现在很丝滑
	// SDL_GetKeyboardState处理连续响应按键，每帧都获取按键状态
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_A]) {
		player->Move(2);  // 向左移动
	}
	if (state[SDL_SCANCODE_D]) {
		player->Move(1);  // 向右移动
	}
	if (state[SDL_SCANCODE_W]) {
		player->Move(3);  // 向上移动
	}
	if (state[SDL_SCANCODE_S]) {
		player->Move(4);  // 向下移动
	}

	
	// SDL_Event contains one of any sub-event(the union of sub-event)
	SDL_Event event;
	// pull the first event from the queue. copying the value into a parameter of type SDL_Event
	// retuen 0 if event queue is empty
	/* SDL_PollEvent common use
	* -------------------------
	*	SDL_Event ev;
		bool running = true;

		// Main loop
		while ( running ) {
			// Event loop
			while ( SDL_PolLEvent( &ev )) {
				// Test members of ev
			}	

			// Wait before next frame
			SDL_Delay(100);
		}
	*
	*/
	while (SDL_PollEvent(&event)) {  // 使用 while 循环处理所有事件
		switch (event.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			
			// 键盘控制移动初版，切换不够顺畅
			/*pollevent是逐个提取事件，用于响应一次性事件，
			比如单个按键的按下和释放，如果持续按住按键希望移动
			会出现延迟，因为需要捕捉持续按键行为*/

			/*case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_w)
				{
					SDL_Log("UP");
					player->Move(3);
				}
				if (event.key.keysym.sym == SDLK_s)
				{
					SDL_Log("DOWN");
					player->Move(4);
				}
				if (event.key.keysym.sym == SDLK_a)
				{
					SDL_Log("LEFT");
					player->Move(2);
				}
				if (event.key.keysym.sym == SDLK_d)
				{
					SDL_Log("RIGHT");
					player->Move(1);
				}
				break;*/

			default:
				break;
		}
	}
}
void Game::update() {
	player->Update();
}
void Game::render() {
	SDL_RenderClear(renderer);
	// this is where to add stuff on render
	// first rect: source rect; secnd rect: destination rect
	player->Render();
	SDL_RenderPresent(renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "game cleaned" << endl;
}