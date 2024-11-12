/* 游戏主循环内容控制
* 所有具体的东西在这里发生
*/

#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "interactiveObject.h"

using namespace std;

GameObject* player;
GameObject* tmp;
interactiveObject* plant;

SDL_Renderer* Game::renderer = nullptr;

bool isPossess = false;

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
		//cout << "Subsystems Initialized!..." << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			//cout << "Window created!" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	player = new GameObject("../00_Asset/spirit.png", 0, 300, 320, 320);
	player->animation(true, 7, 150);
	plant = new interactiveObject("../00_Asset/bunny_grass.png", "../00_Asset/bunny_outline.png",  200, 300, 200, 200);
	tmp = new GameObject("", 0, 300, 320, 320);
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
	if (state[SDL_SCANCODE_TAB]) {
		plant->highlight();
	}
	else
	{
		plant->dehighlight();
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

		default:
			break;
		}
		//按r键附身可互动物品移动-未完成
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
			if (!isPossess) {
				isPossess = true;
				tmp = player;
				player = plant;
			}
			else
			{	
				isPossess = false;
				player = tmp;
			}
			
		}
	}
}
void Game::update() {
	player->Update();
	tmp->Update();
	plant->Update();
}
void Game::render() {
	SDL_RenderClear(renderer);
	// this is where to add stuff on render
	// first rect: source rect; secnd rect: destination rect
	player->Render();
	plant->Render();

	SDL_RenderPresent(renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	//cout << "game cleaned" << endl;
}