#include "GameObject.h"
#include "interactiveObject.h"
#include "TextureManager.h"
#include <iostream>


GameObject::GameObject(const char* texturesheet, int x, int y, int w, int h) {

	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = h;
	srcRect.w = w;
}

int GameObject::GetX() {
	return xpos;
}

int GameObject::GetY() {
	return ypos;
}

int GameObject::GetWidth() {
	return srcRect.w;
}

int GameObject::GetHeight() {
	return srcRect.h;
}

void GameObject::animation(bool isani, int nframe, int mspeed) {
	isanimated = isani;
	frame = nframe;
	speed = mspeed;
}

void GameObject::Update() {

	if (isanimated) { //如果是动画
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frame); //动画帧数控制
	}

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

}

void GameObject::Move(int direction) {
	int speed = 10;

	switch (direction)
	{
	case 1:
		xpos += speed;
		break;
	case 2:
		xpos -= speed;
		break;
	case 3:
		ypos -= speed;
		break;
	case 4:
		ypos += speed;
		break;
	default:
		break;
	}
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

GameObject::~GameObject() {

}