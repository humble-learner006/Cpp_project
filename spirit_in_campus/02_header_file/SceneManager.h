/*
* used to load each scene
* and record the player progress
*/
#pragma once
#include "GameObject.h"
#include "TextureManager.h"
#include "Button.h"
#include "map.h"

class SourceManager {

};

class Scene1
{
public:
	Scene1();
	~Scene1();

	void load();
	void update();
	void render();

private:
	int state;

};