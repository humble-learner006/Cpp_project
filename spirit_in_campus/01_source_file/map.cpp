#include "map.h"
#include "TextureManager.h"

map::map(const char* path, int x, int y, int w, int h) {
	tex = TextureManager::LoadTexture(path);

	src.x = x;
	src.y = y;
	src.w = dest.w = w;
	src.h = dest.h = h;

	dest.x = dest.y = 0;
}

void map::setBond(int ml, int mr, int mu, int md)
{
	l = ml;
	r = mr;
	u = mu;
	d = md;
}

void map::DrawMap() {
	TextureManager::Draw(tex, src, dest);
}