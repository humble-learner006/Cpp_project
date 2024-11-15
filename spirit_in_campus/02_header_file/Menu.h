/*
	Use Button and Label to implement a small
	interface on the screen
*/
#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <vector>
#include <string>
#include "Button.h"

class Menu {
public:
    Menu(int x, int y, int w, int h, SDL_Renderer* renderer);
    ~Menu();

    void Render();
    bool HandleEvent(const SDL_Event& event);
    void AddButton(const std::string& text, int x, int y, int w, int h);
	void CreatePanelWithButtons(int buttonCount, const std::vector<std::string>& buttonNames);
    std::vector<Button>& GetButtons();

private:
    SDL_Rect rect;
    SDL_Renderer* renderer;
    std::vector<Button> buttons;
};

#endif // MENU_H