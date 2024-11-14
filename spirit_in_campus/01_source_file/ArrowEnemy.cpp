#include "ArrowEnemy.h"
#include "TextureManager.h"
#include "GameObject.h" // 包含 GameObject.h
#include <SDL.h>
#include <algorithm>
#include <cmath>

Arrow::Arrow(const char* texturesheet, int x, int y, int w, int h)
    : texture(texturesheet), xpos(x), ypos(y), width(w), height(h), speed(10) {
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

Arrow::~Arrow() {
}

void Arrow::Update() {
    xpos += speed; // 箭向右移动
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

ArrowEnemy::ArrowEnemy(const char* texturesheet, int x, int y, int w, int h, GameObject* player)
    : texture(texturesheet), xpos(x), ypos(y), width(w), height(h), shootCooldown(1000), lastShootTime(0), attackRange(200), moveSpeed(), player(player) {
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

void ArrowEnemy::animation(bool isani, int nframe, int mspeed) {
    bool isanimated = isani;
    int frame = nframe;
    int speed = mspeed;
}


void ArrowEnemy::Update() {
    // 更新箭的状态
    //for (auto arrow : arrows) {
    //    arrow->Update();
    //}

    //// 移除超出屏幕的箭
    //arrows.erase(std::remove_if(arrows.begin(), arrows.end(), [](Arrow* arrow) {
    //    if (arrow->GetX() > 800 || arrow->GetX() < 0 || arrow->GetY() > 600 || arrow->GetY() < 0) {
    //        delete arrow;
    //        return true;
    //    }
    //    return false;
    //    }), arrows.end());

    if (isanimated) {
        srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
    }

    // 获取 player 的位置
    //int playerX = player->GetX();
    //int playerY = player->GetY();

    //// 移动到玩家附近
    //int distanceX = playerX - xpos;
    //int distanceY = playerY - ypos;
    //int distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

    //if (distance > attackRange) {
    //    xpos += (distanceX / distance) * moveSpeed;
    //    ypos += (distanceY / distance) * moveSpeed;
    //}
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
    /*for (auto arrow : arrows) {
        arrow->Render();
    }*/
}

void ArrowEnemy::Shoot() {
    // 创建一个新的箭并添加到箭的列表中
    Arrow* newArrow = new Arrow("arrow_texture.png", xpos, ypos, 32, 32);
    arrows.push_back(newArrow);
}
