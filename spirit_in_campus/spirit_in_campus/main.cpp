/*
	Where game starts, do not change for now 2024.11.13
*/
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_main.h"
#include "Game.h"

#include "AudioManager.hpp"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	// Frame limitation
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("DEMO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 1024, false);

	AudioManager audioManager;
	if (!audioManager.init()) {
		SDL_Log("Failed to initialize AudioManager");
		return -1;
	}

	// ¼ÓÔØÒôÆµÎÄ¼ş
	audioManager.loadMusic("background", "../00_Asset/Nighttime-Escape_v001.mp3");
	audioManager.playMusic("background");
	
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