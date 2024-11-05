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
	// ���̿�������ƶ������ܺ�����½����ࣿ
	void Move(int direction);
	// ���Ƹ���
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

