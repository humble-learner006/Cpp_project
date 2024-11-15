#pragma once
#include <vector>
#include "Game.h"


// 前向声明
class GameObject;

class Arrow {
public:
    Arrow(const char* texturesheet, int x, int y, int w, int h,int d);
    ~Arrow();

    void Update();
    void Render();
    int GetX() const;
    int GetY() const;
	bool getShoten() const { return shoten; }
    void setShoten();
    SDL_Texture* objTexture;


private:
    int xpos, ypos, width, height,direction;
    int speed;
	bool shoten = false;
    const char* texture;
    SDL_Rect srcRect, destRect;

};

class ArrowEnemy {
public:
    ArrowEnemy(const char* texturesheet, int x, int y, int w, int h, GameObject* player);
    ~ArrowEnemy();

    void Update();
    void Render();
	void Shoot(int);
    SDL_Texture* objTexture;

private:
    std::vector<Arrow*> arrows;
    int xpos, ypos, width, height;
    int shootCooldown=1000;
    int lastMoveTime=0;
	int lastShootTime = 0;
	int crurentTime ;
	int timeDiffernece ;
	int status;
    int attackRange=50;
	int eye_sight = 500;
    int moveSpeed=80;
    const char* texture;

    bool isanimated = false;
    int frame = 0;
    int speed = 100;
    GameObject* player; // 添加对 player 对象的引用
    SDL_Rect srcRect, destRect;
};
