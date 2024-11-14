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

	Mix_Music* music;
	bool isRunning = true;
	// Load music
	music = Mix_LoadMUS("../00_Asset/Nighttime-Escape_v001.mp3");
	if (!music) {
		// Handle error
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "could not init Mixer: %s\n", Mix_GetError());
		isRunning = false;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		// Handle error
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "could not init Mixer: %s\n", Mix_GetError());
		isRunning = false;
	}

	game->init("DEMO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 1024, false);

	AudioManager audioManager;
	if (!audioManager.init()) {
		SDL_Log("Failed to initialize AudioManager");
		return -1;
	}

	// ������Ƶ�ļ�
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
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	return 0;
}