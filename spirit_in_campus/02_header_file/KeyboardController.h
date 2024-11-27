#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;

	void init() override
	{
		transform = &entity->getComponent <TransformComponent>();
	}

	void update() override
	{
		// update the movement situation i.e. whether you press the keybutton
		if (Game::event.type == SDL_KEYDOWN)
		{
			// origin from left up, arrow to down and right, we have 1 and -1 for velocity update
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transfrom->velocity.y = -1;
				// what is transfrom - Like pass to Ryth
				break;
			case SDLK_a:
				transfrom->velocity.x = -1;
				break;
			case SDLK_d:
				transfrom->velocity.x = 1;
				break;
			case SDLK_s:
				transfrom->velocity.y = 1;
				break;

			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
			// if you are not pressing the key, then do not update the velocity
			// acceleration a = 0
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transfrom->velocity.y = 0;
				break;
			case SDLK_a:
				transfrom->velocity.x = 0;
				break;
			case SDLK_d:
				transfrom->velocity.x = 0;
				break;
			case SDLK_s:
				transfrom->velocity.y = 0;
				break;
			}
		}
	}