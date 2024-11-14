// SceneManager.h
#pragma once
#include "ResourceManager.h"
#include <memory>

class SceneManager {
public:
    static void changeScene(std::unique_ptr<Scene> newScene, SDL_Renderer* renderer) {
        if (currentScene) {
            currentScene->unloadResources();
        }
        currentScene = std::move(newScene);
        currentScene->loadResources(renderer);
    }

    static void handleEvents(SDL_Event& event) {
        if (currentScene) currentScene->handleEvents(event);
    }

    static void update() {
        if (currentScene) currentScene->update();
    }

    static void render() {
        if (currentScene) currentScene->render();
    }

private:
    static std::unique_ptr<Scene> currentScene;
};
std::unique_ptr<Scene> SceneManager::currentScene = nullptr;
