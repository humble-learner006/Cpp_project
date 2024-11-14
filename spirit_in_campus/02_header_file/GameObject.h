/*
	GameObject is for moving the player(spirit),
	the core part is the implementation of
	Move method
*/
#pragma once
#include "Game.h"
#include "map.h"

class GameObject
{
public:
	GameObject(const char* texturesheet, int x, int y, int w, int h);
	GameObject(const char* texturesheet, const char* outlineTexture, int x, int y, int w, int h);
	~GameObject();

	void highlight();
	void dehighlight();

	void animation(bool isani, int nframe, int mspeed);

	void Update();
	void Render();

	// Control player's movement
	void Move(int speeds, int speedy, const map* gameMap);

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	int GetDistance(GameObject *a, GameObject *b);

	SDL_Texture* objTexture;
	SDL_Texture* normal;
	SDL_Texture* outline;

private:

	bool isanimated = false;
	int frame = 0;
	int speed = 100;

	int xpos;
	int ypos;
	
	int width;
	int height;

	bool isHighlighted;

	SDL_Rect srcRect, destRect;

};

