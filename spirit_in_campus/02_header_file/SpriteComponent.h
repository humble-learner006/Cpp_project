#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component {
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:

	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		texture = TextureManager::LoadTexture(path);

	}

	void init() override {

		position = &entity->getComponent<PositionComponent>();

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.h = srcRect.w = 100;
		destRect.h = destRect.w = 200;

	}

	void update() override {
		destRect.x = position->x();
		destRect.y = position->y();


	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);

	}
};