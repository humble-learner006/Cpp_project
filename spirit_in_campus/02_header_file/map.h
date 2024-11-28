/*
	This is for generating the map
*/
#pragma once
#include "Game.h"
#include <string>

class map {
public:

	map(const char* path, int x, int y, int w, int h);
	~map();

	void setBond(int ml, int mr, int mu, int md);
	void DrawMap();

	//1128 º”‘ÿµÿÕº
	static void LoadMap(std::string path, int sizeX, int sizeY);
	//int l, r, u, d;


private:
//1128
//	SDL_Rect src, dest;

//	// more map element
//	SDL_Texture* tex;
//	//SDL_Texture* door;


};