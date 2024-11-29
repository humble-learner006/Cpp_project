#pragma once
#include "Components.h"
#include "Vector2D.h"
// This header file : Transform Componenet.h is used for control the move

class TransformComponent : public Component
{

public:

	Vector2D position;
	Vector2D velocity;

	int speed = 3; // test number

	
	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	/*void init() override
	{
		xpos = 0;
		ypos = 0;
	}*/

	void init() override{
		velocity.x = 0;
		velocity.y = 0;
		// initialize as don't move the player 
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

	}


	void setPos(int x, int y)
	{
		position.x = x;
		position.y = y;
	}
};