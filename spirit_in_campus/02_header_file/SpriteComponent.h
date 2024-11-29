#pragma once
#include "Components.h"
#include "SDL.h"
#include"TextureManager.h"
#include"Animation.h"
#include<map>

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::map<const char * , Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

// motionless picture
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}
// override in animation form
	SpriteComponent(const char* path, bool isAnimated) {
		animated = isAnimated;

		Aniamtion idle = Animation(0, 3 , 100)
		Animation walk = Animation (1, 8, 100)

		animations. emplace ("Idle", idel);
		animations. emplace ("Walk",walk);

		Play("Idle");


		// frames = nFrames;
		// speed = mSpeed; update and deleted
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

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.h = srcRect.w = 320;
		destRect.h = destRect.w = 200;
		 
	}

	void update() override {

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks()/speed)%frames);
		}

		srcRect.y = animIndex * transform -> height;

		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char * animName)
	{
		frames = animations[animName].frames;  
		animIndex = animations[animName].index;
		speed = animiations[animName].speed;
	}
};