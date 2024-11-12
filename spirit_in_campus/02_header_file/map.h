
#include "Game.h"

class map {
public:

	map();
	~map();

	void LoadMap(int arr[32][48]);
	void DrawMap();

private:

	SDL_Rect src, dest;

	// more map element
	SDL_Texture* background;
	//SDL_Texture* door;

	// 自定义宽高？
	int Map[32][48];

};