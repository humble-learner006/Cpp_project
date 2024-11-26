#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:

	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);

	}
	// change the texture picture, can substitute highlight and dehighlight function
	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.h = srcRect.w = 100;
		destRect.h = destRect.w = 200;
		 
	}

	void update() override {
		destRect.x = transform->x();
		destRect.y = transform->y();
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}
};