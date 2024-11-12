#pragma once
#include "Game.h"
#include "map.h"

class interactiveObject;

class GameObject
{
public:
	GameObject(const char* texturesheet, int x, int y, int w, int h);
	~GameObject();

	void animation(bool isani, int nframe, int mspeed);

	void Update();
	void Render();
	// ���̿�������ƶ������ܺ�����½����ࣿ
	void Move(int speeds, int speedy, const map* gameMap);

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

	SDL_Texture* objTexture;

private:

	bool isanimated = false;
	int frame = 0;
	int speed = 100;

	int xpos;
	int ypos;
	
	int width;
	int height;

	SDL_Rect srcRect, destRect;

};

