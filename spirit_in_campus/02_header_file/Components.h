#pragma once
#include "ECS.h"

class PositionComponent : public Component
{
private:
	int xpos;
	int ypos;

public:

	int x() { return xpos; }
	int y() { return ypos; }

	void init() override
	{
		xpos = 0;
		ypos = 0;
	}

	void update() override
	{
		xpos++;
		ypos++;
	}

	void setPos(int x, int y)
	{
		xpos = x;
		ypos = y;
	}
};

// class VelocityComponent : public Component //存储实体的移动速度。
	

// class RenderComponent : public Component//存储渲染信息（精灵、动画等）。

	
// class ControlComponent : public Component//存储输入控制信息。


// class CollisionComponent : public Component //存储碰撞盒信息。


// class HealthComponent public Component// 存储生命值信息。