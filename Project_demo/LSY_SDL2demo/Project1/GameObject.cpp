#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y) {

	renderer = ren;
	objTexture = TextureManager::LoadTexture(texturesheet, ren);

	xpos = x;
	ypos = y;
}

void GameObject::Update() {

	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

}
// �����ƶ�������
void GameObject::Move(int direction) {
	int speed = 10;

	switch (direction)
	{
	case 1:
		xpos+= speed;
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

	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

GameObject::~GameObject() {

}