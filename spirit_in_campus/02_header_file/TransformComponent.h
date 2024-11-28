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
		position.Zero();
	}

	TransformComponent(float x, float y) {
		position.Zero();
	}

	/*void init() override
	{
		xpos = 0;
		ypos = 0;
	}*/
	void init() override{
		velocity.Zero();
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