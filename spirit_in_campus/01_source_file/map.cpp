#include "map.h"
#include "TextureManager.h"

map::map(const char* path, int x, int y, int w, int h) {
	tex = TextureManager::LoadTexture(path);

	src.x = x;
	src.y = y;
	src.w = dest.w = w;
	src.h = dest.h = h;

	dest.x = src.x;
	dest.y = src.y;
}

// Set bond of the map
void map::setBond(int ml, int mr, int mu, int md)
{
	l = ml;
	r = mr;
	u = mu;
	d = md;
}
// Draw the map
void map::DrawMap() {
	TextureManager::Draw(tex, src, dest);
}