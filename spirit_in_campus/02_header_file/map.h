
#include "Game.h"

class map {
public:

	map();
	~map();

	void LoadMap(int arr[1][1]);
	void DrawMap();

private:

	SDL_Rect src, dest;

	// more map element
	SDL_Texture* background;
	SDL_Texture* bg2;
	//SDL_Texture* door;

	// 自定义宽高？
	int Map[1][1];

};