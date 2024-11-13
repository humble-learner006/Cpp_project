/*
    This Button.h implement two classes, Button and Label.
    Button class is for interaction with mouse click:
    1. Button render
    2, Check whether the button is clicked
    Label class is for showing dialog box:
    1. Label render
    2. User can immediately get full texts and close the dialog box
*/
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
    Label(const std::string& text, int windowWidth, int windowHeight, int h, SDL_Renderer* renderer);
    ~Label();
    void Update(Uint32 currentTime);
    void SkipToNextSegment();
    void HandleEvent(const SDL_Event& event);

    void Render();
    void SetText(const std::string& newText);

private:
    SDL_Rect rect;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    std::string text;

    bool complete = false;
    int textureWidth;
    int textureHeight;
    int lastUpdateTime = 0;
    int updateInterval = 50;
    int currentIndex = 0;
    std::string displayText = "";

    SDL_Texture* CreateTextTexture(const std::string& text, SDL_Renderer* renderer);
};

#endif // BUTTON_H
