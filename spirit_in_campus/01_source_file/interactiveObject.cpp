#include "interactiveObject.h"
#include "TextureManager.h"

// 调用父类的构造函数
interactiveObject::interactiveObject(const char* texturesheet, const char* outlineTexture, SDL_Renderer* ren, int x, int y, int w, int h) :GameObject(texturesheet, ren, x, y, w, h) {
	isHighlighted = false;
	normal = GameObject::objTexture;
	outline = TextureManager::LoadTexture(outlineTexture, ren);
}
interactiveObject::~interactiveObject() {
	SDL_DestroyTexture(outline);
}

void interactiveObject::highlight() {
	if (!isHighlighted) {
		objTexture = outline;
		isHighlighted = true;
	}
}

void interactiveObject::dehighlight() {
	if (isHighlighted) {
		objTexture = normal;
		isHighlighted = false;
	}
}