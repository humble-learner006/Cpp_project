#include "Button.h"
#include <SDL_ttf.h>

// Helper function to set SDL_Rect
void SetRect(SDL_Rect* r, int x, int y, int w, int h) {
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
}

// Draw a rect that looks like 3D bumped
void DrawBumpRect(SDL_Renderer* rdr, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 thick, Uint8 dark, Uint8 bright) {
    for (Sint16 k = 0; k < thick; k++) {
        SDL_SetRenderDrawColor(rdr, dark, dark, dark, 0xFF);
        SDL_RenderDrawLine(rdr, x1 + k, y1 + k, x2 - k, y1 + k);
        SDL_RenderDrawLine(rdr, x1 + k, y1 + k, x1 + k, y2 - k);

        SDL_SetRenderDrawColor(rdr, bright, bright, bright, 0xFF);
        SDL_RenderDrawLine(rdr, x1 + k, y2 - k, x2 - k, y2 - k);
        SDL_RenderDrawLine(rdr, x2 - k, y1 + k, x2 - k, y2 - k);
    }
}

// Button class
Button::Button(const std::string& text, int x, int y, int w, int h, SDL_Renderer* renderer)
    : rect{ x, y, w, h }, renderer(renderer), text(text), status(UI_RELEASED) {
    texture = CreateTextTexture(text, renderer);
}

Button::~Button() {
    SDL_DestroyTexture(texture);
}

void Button::Render() {
    int bright = 200, dark = 100, grey = (bright + dark) / 2;
    int thick = rect.h / 10;

    SDL_SetRenderDrawColor(renderer, grey, grey, grey, 0xFF);
    SDL_RenderFillRect(renderer, &rect);

    if (status == UI_CLICKED) {
        DrawBumpRect(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, thick, dark, bright);
    }
    else if (status == UI_RELEASED) {
        DrawBumpRect(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, thick, bright, dark);
    }

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

bool Button::IsClicked(const SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
            mouseY >= rect.y && mouseY <= rect.y + rect.h) {
            status = UI_CLICKED;
            return true;
        }
    }
    return false;
}

SDL_Texture* Button::CreateTextTexture(const std::string& text, SDL_Renderer* renderer) {
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("../00_Asset/arial.ttf", 24);
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();
    return texture;
}

// Label class
Label::Label(const std::string& text, int x, int y, int w, int h, SDL_Renderer* renderer)
    : rect{ x, y, w, h }, renderer(renderer), text(text) {
    texture = CreateTextTexture(text, renderer);
}

Label::~Label() {
    SDL_DestroyTexture(texture);
}

void Label::Render() {
    int cx = rect.x + rect.w / 2 - textureWidth / 2;
    int cy = rect.y + rect.h / 2 - textureHeight / 2;
    SDL_Rect dstRect = { cx, cy, textureWidth, textureHeight };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

void Label::SetText(const std::string& newText, SDL_Color textColor) {
    text = newText;
    SDL_DestroyTexture(texture);
    texture = CreateTextTexture(text, renderer);
}

SDL_Texture* Label::CreateTextTexture(const std::string& text, SDL_Renderer* renderer) {
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("../00_Asset/arial.ttf", 24);
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    textureWidth = surface->w;
    textureHeight = surface->h;
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();
    return texture;
}
