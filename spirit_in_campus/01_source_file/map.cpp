#include "map.h"
#include "TextureManager.h"

// 初始化的地图，默认为0，可以用其他的数字来表示其他物品在地图上的位置
int scene1[32][48] = {0};

map::map() {
	background = TextureManager::LoadTexture("../00_Asset/scene1_music.png");

	LoadMap(scene1);

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	dest.x = dest.y = 0;
}

void map::LoadMap(int arr[32][48]) {
	for (int row = 0; row < 32; row++) {
		for (int col = 0; col < 48; col++) {
			Map[row][col] = arr[row][col];
		}
	}
}

void map::DrawMap() {
	int type = 0;

	for (int row = 0; row < 32; row++) {
		for (int col = 0; col < 48; col++) {
			type = Map[row][col];

			dest.x = col * 32;
			dest.y = row * 32;

			switch (type)
			{
			case 0:
				TextureManager::Draw(background, src, dest);
				break;
			default:
				break;
			}

		}
	}
}