/*
* used to load each scene
* and record the player progress
*/
#pragma once
#include "GameObject.h"
#include "TextureManager.h"
#include "Button.h"
#include "map.h"

#include <vector>

class Scene {
public:
	virtual void loadResources(SDL_Renderer* renderer) = 0;
	virtual void unloadResources() = 0;
	virtual void handleEvents(SDL_Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

class Scene1:public Scene
{
public:
    void loadResources(SDL_Renderer* renderer) override;

    void unloadResources() override;

    void handleEvents(SDL_Event& event) override;

    void update() override;

	void render() override;

private:
	int state;
	Button* startButton;
	Button* settingsButton;
	Button* quitButton;
	GameObject* player;
	GameObject* tmp;
	GameObject* instrument1;
	GameObject* plant;
	map* scene_music;
	Label* label;

	
};