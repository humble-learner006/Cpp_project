/*
	This is for generating the map
*/
#pragma once
#include "Game.h"

class map {
public:

	map(const char* path, int x, int y, int w, int h);
	~map();

	void setBond(int ml, int mr, int mu, int md);
	void DrawMap();

	int l, r, u, d;

private:

	SDL_Rect src, dest;

	// more map element
	SDL_Texture* tex;
	//SDL_Texture* door;


};