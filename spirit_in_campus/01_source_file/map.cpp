#include "map.h"
#include "TextureManager.h"

// 初始化的地图，默认为0，可以用其他的数字来表示其他物品在地图上的位置
int scene1[1][1] = {0};

map::map() {
	background = TextureManager::LoadTexture("../00_Asset/scene1_music.png");

	src.x = src.y = 0;
	src.w = dest.w = 1536;
	src.h = dest.h = 1024;

	dest.x = dest.y = 0;
}

void map::LoadMap(int arr[1][1]) {
	for (int row = 0; row < 1; row++) {
		for (int col = 0; col < 1; col++) {
			Map[row][col] = arr[row][col];
		}
	}
}

void map::DrawMap() {
	TextureManager::Draw(background, src, dest);
}