#include "Button.h"
#include <SDL_ttf.h>

// Generate Button
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

// Create texture on the button
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

// Button class
Button::Button(const std::string& text, int x, int y, int w, int h, SDL_Renderer* renderer)
    : rect{ x, y, w, h }, renderer(renderer), text(text), status(UI_RELEASED) {
    texture = CreateTextTexture(text, renderer);
}

Button::~Button() {
    SDL_DestroyTexture(texture);
}

// Get change after the user click the button
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

// Check for user's action
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

// Label class
Label::Label(const std::string& text, int windowWidth, int windowHeight, int h, SDL_Renderer* renderer)
    : renderer(renderer), text(text) {

    // Dialog label's size and position
    rect = { 100, windowHeight - h - 30, windowWidth - 200, h }; 

    // Let the initial label(background) be white
    texture = CreateTextTexture(text, renderer);
}

Label::~Label() {
    SDL_DestroyTexture(texture);
}

void Label::Render() {

    // Render back ground (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(renderer, &rect);

    // Render dialog's edges (black)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

    // Render the words in the box
    SDL_Rect dstRect = { rect.x + 20, rect.y + 10, textureWidth, textureHeight };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

// Create texture on the label
SDL_Texture* Label::CreateTextTexture(const std::string& text, SDL_Renderer* renderer) {
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("../00_Asset/arial.ttf", 40);
    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    textureWidth = surface->w;
    textureHeight = surface->h;
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();
    return texture;
}

void Label::Update(Uint32 currentTime) {
    // For every `updateInterval` time update texts
    if (currentTime - lastUpdateTime >= updateInterval) {
        if (currentIndex < text.size()) {
            displayText += text[currentIndex++];
            SetText(displayText); // Update texts
            lastUpdateTime = currentTime;
        }
    }
}

// Skip the space to display the full text
void Label::SkipToNextSegment() {
    if (currentIndex < text.size()) {
        displayText = text;
        SetText(displayText);
        currentIndex = text.size(); // Mark for complete display
    }
}

// User interaction with space bar
void Label::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
        if (!complete) {
            SkipToNextSegment();
            complete = true;
        }
        else
        {
            SDL_DestroyTexture(texture);
            rect.w = rect.h = 0;
        }
    }
}

// Update texts and reset texture
void Label::SetText(const std::string& newText) {
    displayText = newText;

    if (texture) {
        SDL_DestroyTexture(texture);
    }
    texture = CreateTextTexture(displayText, renderer);
}