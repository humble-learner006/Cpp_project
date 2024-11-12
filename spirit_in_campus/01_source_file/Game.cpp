/* ��Ϸ��ѭ�����ݿ���
* ���о���Ķ��������﷢��
*/

#include "Game.h"
#include "Button.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "interactiveObject.h"

using namespace std;

GameObject* player;
interactiveObject* plant;

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
		//cout << "Subsystems Initialized!..." << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			//cout << "Window created!" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 102, 102, 255, 0);
			//cout << "Renderer created" << endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	startButton = new Button("Begin", 100, 100, 200, 50, renderer);
	settingsButton = new Button("Settings", 100, 200, 200, 50, renderer);
	quitButton = new Button("Exit", 100, 300, 200, 50, renderer);

	player = new GameObject("../00_Asset/sprite.png", renderer, 0, 300, 64, 64);
	plant = new interactiveObject("../00_Asset/bunny_grass.png", "../00_Asset/bunny_outline.png", renderer, 200, 300, 200, 200);

	currentState = MENU;
}

void Game::handleEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}

		if (currentState == MENU) {
			if (startButton->IsClicked(event)) {
				currentState = PLAYING;
			}
			else if (settingsButton->IsClicked(event)) {
				// �������ð�ť����¼�
			}
			else if (quitButton->IsClicked(event)) {
				isRunning = false;
			}
		}
		else if (currentState == PLAYING) {
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
			if (state[SDL_SCANCODE_TAB]) {
				plant->highlight();
			}
			else {
				plant->dehighlight();
			}
		}
	}
}

void Game::update() {
	player->Update();
	plant->Update();
}
void Game::render() {
	SDL_RenderClear(renderer);
	if (currentState == MENU) {
		startButton->Render();
		settingsButton->Render();
		quitButton->Render();
	}
	else if (currentState == PLAYING) {
		player->Render();
		plant->Render();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	delete startButton;
	delete settingsButton;
	delete quitButton;
	delete player;
	delete plant;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}