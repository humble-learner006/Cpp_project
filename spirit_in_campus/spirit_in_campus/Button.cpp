#include "Button.h"
#include <SDL_ttf.h>

Button::Button(const std::string& text, int x, int y, int w, int h, SDL_Renderer* renderer)
    : rect{ x, y, w, h }, renderer(renderer) {
    // 创建按钮纹理（这里假设你有一个函数来创建纹理）
    texture = CreateTextTexture(text, renderer);
}

Button::~Button() {
    SDL_DestroyTexture(texture);
}

void Button::Render() {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

bool Button::IsClicked(int mouseX, int mouseY) {
    return mouseX > rect.x && mouseX < rect.x + rect.w && mouseY > rect.y && mouseY < rect.y + rect.h;
}

SDL_Texture* Button::CreateTextTexture(const std::string& text, SDL_Renderer* renderer) {
    // 初始化TTF
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("path/to/font.ttf", 24);
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();
    return texture;
}
