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
	// ��ʼ��ʱ��ѡ���Ƿ�ȫ��
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	// ȷ��SDL�Ƿ�ɹ���ʼ������������
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
	//���̿����ƶ��Ż������ں�˿��
	// SDL_GetKeyboardState����������Ӧ������ÿ֡����ȡ����״̬
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_A]) {
		player->Move(2);  // �����ƶ�
	}
	if (state[SDL_SCANCODE_D]) {
		player->Move(1);  // �����ƶ�
	}
	if (state[SDL_SCANCODE_W]) {
		player->Move(3);  // �����ƶ�
	}
	if (state[SDL_SCANCODE_S]) {
		player->Move(4);  // �����ƶ�
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
	while (SDL_PollEvent(&event)) {  // ʹ�� while ѭ�����������¼�
		switch (event.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			
			// ���̿����ƶ����棬�л�����˳��
			/*pollevent�������ȡ�¼���������Ӧһ�����¼���
			���絥�������İ��º��ͷţ����������ס����ϣ���ƶ�
			������ӳ٣���Ϊ��Ҫ��׽����������Ϊ*/

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