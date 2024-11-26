#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component {
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
// motionless picture
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}
// override in animation form
	SpriteComponent(const char* path, int nFrames, int mSpeed) {
		animated = true;
		frames = nFrames;
		speed = mSpeed;
		setTex(path);
	}
// clean up
	~SpriteComponent(){
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path){
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {

		position = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.h = srcRect.w = 320;
		destRect.h = destRect.w = 200;

	}

	void update() override {

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks()/speed)%frames);
		}
		destRect.x = position->x();
		destRect.y = position->y();


	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);

	}
};