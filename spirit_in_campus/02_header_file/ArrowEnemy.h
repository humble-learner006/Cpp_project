#pragma once
#include <vector>
#include "Game.h"


// ǰ������
class GameObject;

class Arrow {
public:
    Arrow(const char* texturesheet, int x, int y, int w, int h);
    ~Arrow();

    void Update();
    void Render();
    int GetX() const;
    int GetY() const;
    SDL_Texture* objTexture;


private:
    int xpos, ypos, width, height;
    int speed;
    const char* texture;
    SDL_Rect srcRect, destRect;

};

class ArrowEnemy {
public:
    ArrowEnemy(const char* texturesheet, int x, int y, int w, int h, GameObject* player);
    ~ArrowEnemy();

    void Update();
    void Render();
    void Shoot();
	void animation(bool isani, int nframe, int mspeed);
    SDL_Texture* objTexture;

private:
    std::vector<Arrow*> arrows;
    int xpos, ypos, width, height;
    int shootCooldown;
    int lastShootTime;
    int attackRange;
    int moveSpeed=60;
    const char* texture;

    bool isanimated = false;
    int frame = 0;
    int speed = 100;
    GameObject* player; // ��Ӷ� player ���������
    SDL_Rect srcRect, destRect;
};
