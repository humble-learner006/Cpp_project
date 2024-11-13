#include "GameObject.h"
#include "interactiveObject.h"
#include "TextureManager.h"
#include <iostream>


GameObject::GameObject(const char* texturesheet, int x, int y, int w, int h) {

	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
	width = w;
	height = h;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = height;
	srcRect.w = width;
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

	if (isanimated) { //����Ƕ���
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frame); //����֡������
	}

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

}
// �����ƶ�������
void GameObject::Move(int speedx, int speedy, const map* gameMap) {
	xpos += speedx;
	ypos += speedy;

	if (xpos < gameMap->l) {
		xpos = gameMap->l;
	}
	if (xpos > gameMap->r) {
		xpos = gameMap->r;
	}
	if (ypos < gameMap->u) {
		ypos = gameMap->u;
	}
	if (ypos > gameMap->d) {
		ypos = gameMap->d;
	}
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

GameObject::~GameObject() {

}