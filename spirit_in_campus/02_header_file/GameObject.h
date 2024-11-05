#pragma once
#include "Game.h"

class interactiveObject;

class GameObject
{
public:
	GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y, int w, int h);
	~GameObject();

	void Update();
	void Render();
	// 键盘控制玩家移动，可能后面会新建子类？
	void Move(int direction);
	// 控制附身
	void Possess(interactiveObject* obj);

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

	SDL_Texture* objTexture;

private:

	int xpos;
	int ypos;

	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};

