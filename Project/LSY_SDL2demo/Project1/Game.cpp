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
				
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_A:
						player->Move(2);
						break;
						
					case SDL_SCANCODE_D:
						player->Move(1);
						break;
						
					case SDL_SCANCODE_W:
						player->Move(3);
						break;
						
					case SDL_SCANCODE_S:
						player->Move(4);
						break;
						
					default:
						break;
				}
				break;

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