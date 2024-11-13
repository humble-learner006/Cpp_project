/*
	interactiveObject is to highlight the object
	(flowerpot)
*/
#pragma once
#include "Game.h"
#include "GameObject.h"

class interactiveObject :public GameObject
{
public:
	interactiveObject(const char* texturesheet, const char* outlineTexture, int x, int y, int w, int h);
	~interactiveObject();
	void highlight();
	void dehighlight();

	SDL_Texture* outline;
	SDL_Texture* normal;

	bool isHighlighted;

private:

};

