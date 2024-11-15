#include "ArrowEnemy.h"
#include "TextureManager.h"
#include "GameObject.h" // 包含 GameObject.h
#include <SDL.h>
#include <algorithm>
#include <cmath>
#include <iostream>

class GameObject;

Arrow::Arrow(const char* texturesheet, int x, int y, int w, int h,int d)
    : texture(texturesheet), xpos(x), ypos(y), width(w), height(h), speed(10) {
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
    width = w;
    height = h;
    direction = d;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = height;
    srcRect.w = width;

}

Arrow::~Arrow() {
}

void Arrow::Update() {
	if (direction > 0 ){
		xpos += speed;
	}
	else {
		xpos -= speed;
	}
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void Arrow::Render() {
    TextureManager::Draw(objTexture, srcRect, destRect);
}

int Arrow::GetX() const {
    return xpos;
}

int Arrow::GetY() const {
    return ypos;
}


void Arrow::setShoten() {
	shoten = not shoten;
}

ArrowEnemy::ArrowEnemy(const char* texturesheet, int x, int y, int w, int h, GameObject* player)
    : texture(texturesheet), xpos(x), ypos(y), width(w), height(h), shootCooldown(1000),    player(player) {
	objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
    width = w;
    height = h;
    


    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = height;
    srcRect.w = width;
}

ArrowEnemy::~ArrowEnemy() {
    for (auto arrow : arrows) {
        delete arrow;
    }
    arrows.clear();
}

//void ArrowEnemy::animation(bool isani, int nframe, int mspeed) {
//    bool isanimated = isani;
//    int frame = nframe;
//    int speed = mspeed;
//}


void ArrowEnemy::Update() {
    // 更新箭的状态
    for (auto arrow : arrows) {
        arrow->Update();

    }

    //// 移除超出屏幕的箭
    //arrows.erase(std::remove_if(arrows.begin(), arrows.end(), [](Arrow* arrow) {
    //    if (arrow->GetX() > 800 || arrow->GetX() < 0 || arrow->GetY() > 600 || arrow->GetY() < 0) {
    //        delete arrow;
    //        return true;
    //    }
    //    return false;
    //    }), arrows.end());

    /*if (isanimated) {
        srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
    }*/

    //控制移动时间
	crurentTime = SDL_GetTicks();
	timeDiffernece = crurentTime - lastMoveTime;

    // 获取 player 的位置
    int playerX = player->GetX();
    int playerY = player->GetY();

    //// 移动到玩家附近
    int distanceX = playerX - xpos;
    int distanceY = playerY - ypos;
    int distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);


	// 如果玩家在敌人的攻击范围外但在视野内，敌人向玩家移动
   

	//如果敌人在攻击范围内，射箭
	if (abs(distanceY+50) <= attackRange and crurentTime - lastShootTime > shootCooldown) {
		Shoot(distanceX);
		lastShootTime = crurentTime;
	}
    else if (distance > attackRange and distance < eye_sight and timeDiffernece>250) {
        lastMoveTime = crurentTime;
        if (abs(distanceX) > abs(distanceY)) {
            if (distanceX > 0) {
                xpos += moveSpeed;
            }
            else {
                xpos -= moveSpeed;
            }
        }
        else {
            if (distanceY > 0) {
                ypos += moveSpeed;
            }
            else {
                ypos -= moveSpeed;
            }
        }
    }




	destRect.x = xpos;
	destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;

    // 射箭逻辑
    /*int currentTime = SDL_GetTicks();
    if (distance <= attackRange && currentTime - lastShootTime > shootCooldown) {
        Shoot();
        lastShootTime = currentTime;
    }*/
}

void ArrowEnemy::Render() {
    // 渲染敌人
    TextureManager::Draw(objTexture, srcRect, destRect);

    // 渲染箭
    for (auto arrow : arrows) {
        arrow->Render();
    }
}

void ArrowEnemy::Shoot(int d) {
    // 创建一个新的箭并添加到箭的列表中
    Arrow* newArrow = new Arrow("../00_Asset/arrow.png", xpos, ypos+height/2, 32, 32,d);
	arrows.push_back(newArrow);
}
