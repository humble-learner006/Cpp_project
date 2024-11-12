/* ��Ϸ��ѭ�����ݿ���
* ���о���Ķ��������﷢��
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

	player = new GameObject("../00_Asset/spirit.png", 0, 300, 320, 320);
	player->animation(true, 7, 150);
	plant = new interactiveObject("../00_Asset/bunny_grass.png", "../00_Asset/bunny_outline.png",  200, 300, 200, 200);
	tmp = new GameObject("", 0, 300, 320, 320);
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
	while (SDL_PollEvent(&event)) {  // ʹ�� while ѭ�����������¼�
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
		}
		//��r������ɻ�����Ʒ�ƶ�-δ���
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