#include "interactiveObject.h"
#include "TextureManager.h"

// ���ø���Ĺ��캯��
interactiveObject::interactiveObject(const char* texturesheet, const char* outlineTexture, int x, int y, int w, int h) :GameObject(texturesheet, x, y, w, h) {
	isHighlighted = false;
	normal = GameObject::objTexture;
	outline = TextureManager::LoadTexture(outlineTexture);
}
interactiveObject::~interactiveObject() {

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