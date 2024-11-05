#include "GameObject.h"
#include "interactiveObject.h"
#include "TextureManager.h"
#include <iostream>

bool isPossessing = false;
interactiveObject* currentObj = NULL;

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y, int w, int h) {

	renderer = ren;
	objTexture = TextureManager::LoadTexture(texturesheet, ren);

	xpos = x;
	ypos = y;
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

void GameObject::Update() {

	if (!isPossessing) {
		srcRect.x = 0;
		srcRect.y = 0;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = srcRect.w;
		destRect.h = srcRect.h;
	}
	else {
		if (currentObj) {
			destRect.x = currentObj->GetX();  // 获取当前物体的坐标
			destRect.y = currentObj->GetY();
			destRect.w = currentObj->GetWidth();  // 获取物体的宽度
			destRect.h = currentObj->GetHeight();
		}
		else
		{
			std::cout << "Error : can't get current object" << std::endl;
		}
	}


}
// 人物移动测试中
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

void GameObject::Possess(interactiveObject* obj) {
	if (obj) {
		isPossessing = !isPossessing;
		currentObj = isPossessing ? obj : NULL;
	}
}

void GameObject::Render() {
	if (!isPossessing) {
		SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
	}
}

GameObject::~GameObject() {

}