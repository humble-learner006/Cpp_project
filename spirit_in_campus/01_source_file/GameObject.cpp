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

int GameObject::GetDistance(GameObject *a, GameObject *b) {
    int dx = a->xpos - b->xpos;
    int dy = a->ypos - b->ypos;
    return static_cast<int>(SDL_sqrt(dx * dx + dy * dy));
}

void GameObject::animation(bool isani, int nframe, int mspeed) {
	isanimated = isani;
	frame = nframe;
	speed = mspeed;
}

// Update player's position (rectangle)
void GameObject::Update() {

	if (isanimated) { 
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frame); 
	}

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

}

// Player's moving operation
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
	TextureManager::Draw(objTexture, srcRect, destRect);
}

GameObject::~GameObject() {

}