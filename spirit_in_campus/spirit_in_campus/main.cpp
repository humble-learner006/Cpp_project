#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_main.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	// ֡������
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("DEMO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

	// e->a = (*e).a
	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvent();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}