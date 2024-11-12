/* ��Ϸ��ѭ�����ݿ���
* ���о���Ķ��������﷢��
*/

#include "Game.h"
#include "Button.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "interactiveObject.h"

GameObject* player;
GameObject* tmp;
interactiveObject* plant;
map* scene_music;
Label* label;

SDL_Renderer* Game::renderer = nullptr;

bool isPossess = false;

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

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	startButton = new Button("Begin", 100, 100, 200, 50, renderer);
	settingsButton = new Button("Settings", 100, 200, 200, 50, renderer);
	quitButton = new Button("Exit", 100, 300, 200, 50, renderer);

	player = new GameObject("../00_Asset/spirit.png", 0, 300, 320, 320);
	player->animation(true, 7, 150);
	plant = new interactiveObject("../00_Asset/bunny_grass.png", "../00_Asset/bunny_outline.png",  1000, 500, 200, 200);
	tmp = new GameObject("", 0, 300, 320, 320);

	scene_music = new map("../00_Asset/scene1_music.png",0, 0, 1536, 1024);
	scene_music->setBond(0, 1200, 150, 700);

	label = new Label("testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttestte", 1536, 1024, 300, renderer);
}

void Game::handleEvent() {
	//���̿����ƶ��Ż������ں�˿��
	// SDL_GetKeyboardState����������Ӧ������ÿ֡����ȡ����״̬
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (currentState == PLAYING){
		if (state[SDL_SCANCODE_A]) {
			player->Move(-10, 0, scene_music);  // �����ƶ�
		}
		if (state[SDL_SCANCODE_D]) {
			player->Move(10, 0, scene_music);  // �����ƶ�
		}
		if (state[SDL_SCANCODE_W]) {
			player->Move(0, -10, scene_music);  // �����ƶ�
		}
		if (state[SDL_SCANCODE_S]) {
			player->Move(0, 10, scene_music);  // �����ƶ�
		}
		if (state[SDL_SCANCODE_TAB]) {
			plant->highlight();
		}
		else
		{
			plant->dehighlight();
		}
	}


	// SDL_Event contains one of any sub-event(the union of sub-event)
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}

		label->HandleEvent(event);

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
	\
		//��r�������ɻ�����Ʒ�ƶ�-δ���
		/*if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
			player->Possess(plant);
			player = plant;
		}*/
	}
}
void Game::update() {
	Uint32 currentTime = SDL_GetTicks();

	if (currentState == PLAYING) {
		player->Update();
		tmp->Update();
		plant->Update();
		label->Update(currentTime);
	}
}
void Game::render() {
	SDL_RenderClear(renderer);
	if (currentState == MENU) {
		startButton->Render();
		settingsButton->Render();
		quitButton->Render();
	}
	else if (currentState == PLAYING) {
		scene_music->DrawMap();
		player->Render();
		plant->Render();
		label->Render();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	delete startButton;
	delete settingsButton;
	delete quitButton;
	delete player;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}