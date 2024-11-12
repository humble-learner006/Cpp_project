#pragma once
#ifndef Game_h
#define Game_h
#include "SDL.h"
#include <stdio.h>
#include "SDL_image.h"
#include "Button.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvent();
	void update();
	void render();
	void clean();
	
	bool running() { return isRunning; }	

	static SDL_Renderer* renderer;
private:
	enum GameState { MENU, PLAYING };
	GameState currentState;

	bool isRunning;
	SDL_Window* window;
	Button* startButton;
    Button* settingsButton;
    Button* quitButton;
};

#endif // !Game_h
