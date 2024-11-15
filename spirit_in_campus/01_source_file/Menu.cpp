#include "Menu.h"
#include "Button.h"

Menu::Menu(int x, int y, int w, int h, SDL_Renderer* renderer)
    : rect{ x, y, w, h }, renderer(renderer) {
    // Initialize texture or other resources here if needed
}

Menu::~Menu() {
    // Clean up resources here if needed
}

void Menu::Render() {
    // Render the menu background
    SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255); 
    SDL_RenderFillRect(renderer, &rect);

    // Render each button
    for (auto& button : buttons) {
        button.Render();
    }
}

bool Menu::HandleEvent(const SDL_Event& event) {
    // Handle events for each button
    for (auto& button : buttons) {
		return button.IsClicked(event);
    }
}

void Menu::AddButton(const std::string& text, int x, int y, int w, int h) {
    buttons.emplace_back(text, x, y, w, h, renderer);
}

void Menu::CreatePanelWithButtons(int buttonCount, const std::vector<std::string>& buttonNames) {
    int buttonWidth = 80;
    int buttonHeight = 30;
    int padding = 10;
    int startX = rect.x + padding;
    int startY = rect.y + padding;

    for (int i = 0; i < buttonCount; ++i) {
        int x = startX;
        int y = startY + i * (buttonHeight + padding);
        AddButton(buttonNames[i], x, y, buttonWidth, buttonHeight);
    }
}

std::vector<Button>& Menu::GetButtons() {
    return buttons;
}
