/* 
 * Game loop implementation
 * 1. Initialize the game
 * 2. Check whether the game is running (MENU PLAYING SCENE1)
 * 3. Handle player's events keyboard/mouse
 * 4. Update postions of moving objects
 * 5. Render objects occur on the screen
 * 6. Clean up
*/
#pragma once
#ifndef Game_h
#define Game_h
#include "SDL.h"
#include <stdio.h>
#include "SDL_image.h"
#include "Button.h"
#include "Menu.h"
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();
	// Generate screen method
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	// Handle user input method (keyboard, mouse)
	void handleEvent();

	// Update positions of moving objects (players, enemies, possesions)
	void update();

	// Render the objects occur on the screen (button, label, moving objects)
	void render();

	// Release memory method
	void clean();
	
	/* 
		To check whether the game loop is continuing
		If user choose to exit the game, isRunning = false, else isRunning 
		should always be true
	*/
	bool running() { return isRunning; }	

	
	static SDL_Renderer* renderer; // Use to render
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

	//1128
	static void AddTile(int id, int x, int y);

private:
	// Through different current state, we can do different operations
	enum GameState { MAIN, SETTING, PLAYING, PAUSE, SCENE1};
	GameState currentState;
	GameState lastState;

	// Be used in running method
	bool isRunning;

	SDL_Window* window;
};
#endif
