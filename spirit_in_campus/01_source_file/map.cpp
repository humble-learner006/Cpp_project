#include "map.h"
//#include "TextureManager.h"
#include "Game.h"
#include <fstream>

//map::map(const char* path, int x, int y, int w, int h) {
	//tex = TextureManager::LoadTexture(path);

	//src.x = x;
//	src.y = y;
	//src.w = dest.w = w;
	//src.h = dest.h = h;

	//dest.x = src.x;
	//dest.y = src.y;
//}

// Set bond of the map
//void map::setBond(int ml, int mr, int mu, int md)
//{
//	l = ml;
//	r = mr;
//	u = mu;
//	d = md;
//}
// Draw the map
//void map::DrawMap() {
	//TextureManager::Draw(tex, src, dest);
//}

//1128
map::map() {
}

map::~map() {
}


void map::LoadMap(std::string path, int sizeX, int sizeY) {
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(tile);
			Game::AddTile(atoi(&tile), x * 32, y * 32);
			mapFile.ignore();
		}
	}
	mapFile.close();
}