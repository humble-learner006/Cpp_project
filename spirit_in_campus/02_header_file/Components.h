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

// class VelocityComponent : public Component //�洢ʵ����ƶ��ٶȡ�
	

// class RenderComponent : public Component//�洢��Ⱦ��Ϣ�����顢�����ȣ���

	
// class ControlComponent : public Component//�洢���������Ϣ��


// class CollisionComponent : public Component //�洢��ײ����Ϣ��


// class HealthComponent public Component// �洢����ֵ��Ϣ��