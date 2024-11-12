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
Label::Label(const std::string& text, int windowWidth, int windowHeight, int h, SDL_Renderer* renderer)
    : renderer(renderer), text(text) {

    // 设置对话框的尺寸和位置
    rect = { 100, windowHeight - h - 30, windowWidth - 200, h }; // x=10, y底部上移10像素, w=窗口宽度-20, h=固定高度

    // 初始化空白显示内容
    texture = CreateTextTexture(text, renderer); // 开始时为空
}

Label::~Label() {
    SDL_DestroyTexture(texture);
}

void Label::Render() {
    // 渲染对话框背景
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // 白色背景
    SDL_RenderFillRect(renderer, &rect);

    // 绘制对话框边框
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 黑色边框
    SDL_RenderDrawRect(renderer, &rect);

    // 渲染当前文字内容
    SDL_Rect dstRect = { rect.x + 20, rect.y + 10, textureWidth, textureHeight }; // 左侧留白20，顶部留白10
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

void Label::Update(Uint32 currentTime) {
    // 每隔 `updateInterval` 时间增加一个字符
    if (currentTime - lastUpdateTime >= updateInterval) {
        if (currentIndex < text.size()) {
            // 逐字增加显示文本
            displayText += text[currentIndex++];
            SetText(displayText); // 更新当前显示的文本纹理
            lastUpdateTime = currentTime;
        }
    }
}

void Label::SkipToNextSegment() {
    // 空格跳过，立即显示完整文本
    if (currentIndex < text.size()) {
        displayText = text;
        SetText(displayText);
        currentIndex = text.size(); // 标记为显示完毕
    }
}

void Label::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
        SkipToNextSegment();
    }
}

void Label::SetText(const std::string& newText) {
    // 更新显示的文字内容并重建纹理
    displayText = newText;

    if (texture) {
        SDL_DestroyTexture(texture);
    }
    texture = CreateTextTexture(displayText, renderer);
}

SDL_Texture* Label::CreateTextTexture(const std::string& text, SDL_Renderer* renderer) {
    // 创建文字纹理
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("../00_Asset/arial.ttf", 40);
    SDL_Color color = { 0, 0, 0, 255 }; // 黑色文字
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    textureWidth = surface->w;
    textureHeight = surface->h;
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();
    return texture;
}