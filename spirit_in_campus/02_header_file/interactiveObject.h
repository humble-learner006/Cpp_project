#pragma once
#include "Game.h"
#include "GameObject.h"

class interactiveObject :public GameObject
{
public:
	interactiveObject(const char* texturesheet, const char* outlineTexture, SDL_Renderer* ren, int x, int y, int w, int h);
	~interactiveObject();
	void highlight();
	void dehighlight();

	SDL_Texture* outline;
	SDL_Texture* normal;

	bool isHighlighted;

private:

};

