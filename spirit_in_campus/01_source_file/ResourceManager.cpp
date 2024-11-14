#pragma once
#include "ResourceManager.h"

Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::loadResources(SDL_Renderer* renderer)
{
	startButton = new Button("Begin", 100, 100, 200, 50, renderer);
	settingsButton = new Button("Settings", 100, 200, 200, 50, renderer);
	quitButton = new Button("Exit", 100, 300, 200, 50, renderer);

	player = new GameObject("../00_Asset/spirit.png", 0, 300, 320, 320);
	player->animation(true, 7, 150);
	plant = new GameObject("../00_Asset/bunny_grass.png", "../00_Asset/bunny_outline.png", 1000, 500, 200, 200);
	instrument1 = new GameObject("../00_Asset/instrument1.png", "../00_Asset/instrument1_outline.png", 500, 500, 200, 200);
	tmp = new GameObject("", 0, 300, 320, 320);

	scene_music = new map("../00_Asset/scene1_music.png", 0, 0, 1536, 1024);
	scene_music->setBond(0, 1200, 150, 700);

	label = new Label("Press space to skip the dialog and close the text block.", 1536, 1024, 300, renderer);

}

void Scene1::unloadResources()
{
	
}

void Scene1::handleEvents(SDL_Event& event)
{
}

void Scene1::update()
{
}

void Scene1::render()
{
}
