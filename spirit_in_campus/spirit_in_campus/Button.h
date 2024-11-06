#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <string>

class Button {
public:
    Button(const std::string& text, int x, int y, int w, int h, SDL_Renderer* renderer);
    ~Button();
    void Render();
    bool IsClicked(int mouseX, int mouseY);

private:
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Renderer* renderer;

    SDL_Texture* CreateTextTexture(const std::string& text, SDL_Renderer* renderer);
};

#endif // BUTTON_H

