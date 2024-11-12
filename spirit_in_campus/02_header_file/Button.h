#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

// Enum for button status
enum UIButtonStatus {
    UI_CLICKED,
    UI_RELEASED
};

// Button class
class Button {
public:
    Button(const std::string& text, int x, int y, int w, int h, SDL_Renderer* renderer);
    ~Button();

    void Render();
    bool IsClicked(const SDL_Event& event);

private:
    SDL_Rect rect;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    std::string text;
    UIButtonStatus status;

    SDL_Texture* CreateTextTexture(const std::string& text, SDL_Renderer* renderer);
};

// Label class
class Label {
public:
    Label(const std::string& text, int x, int y, int w, int h, SDL_Renderer* renderer);
    ~Label();

    void Render();
    void SetText(const std::string& newText, SDL_Color textColor);

private:
    SDL_Rect rect;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    std::string text;
    int textureWidth;
    int textureHeight;

    SDL_Texture* CreateTextTexture(const std::string& text, SDL_Renderer* renderer);
};

#endif // BUTTON_H
