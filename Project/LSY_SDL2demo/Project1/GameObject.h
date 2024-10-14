#pragma once
#include "Game.h"

class GameObject
{
public:
	GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
	~GameObject();

	void Update();
	void Render();
	// 键盘控制玩家移动，可能后面会新建子类？
	void Move(int direction);

private:
	
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};

