#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <bits/stdc++.h>
#include "text.h"
#include "../const/data.h"
#include "../const/UI.h"

using namespace std;

struct Button {
    SDL_FRect rect;
    SDL_Color textColor;
    SDL_Color bgColor;
    SDL_Color hoverColor;
    SDL_Texture* texture;
    SDL_Surface* textSurface;
    char* text;
    bool isHovered;
};

// Function to create a button
Button* createButton(SDL_Renderer* renderer, int x, int y, int w, int h,
                    const char* text, SDL_Color textColor, SDL_Color bgColor, SDL_Color hoverColor,
                    TTF_Font* font) {
    Button* button = new Button();
    button->rect.x = (float)x;
    button->rect.y = (float)y;
    button->rect.w = (float)w;
    button->rect.h = (float)h;

    button->textColor = textColor;
    button->bgColor = bgColor;
    button->hoverColor = hoverColor;

    button->text = SDL_strdup(text); 
    if (font != nullptr) button->textSurface = TTF_RenderText_Solid(font, text, strlen(text), textColor);

    if (!button->textSurface) {
        std::cerr << "TTF_RenderText_Blended Error: " << SDL_GetError() << std::endl;
        delete button;
        return nullptr;
    }

    button->texture = SDL_CreateTextureFromSurface(renderer, button->textSurface);
    if (!button->texture) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_DestroySurface(button->textSurface);
        delete button;
        return nullptr;
    }

    button->isHovered = false;
    return button;
}

void handleClickedEvent(Button* button) {
    if ((string) button->text == "Classic") {
        gameMode ^= CLASSIC_MODE;
        if (gameMode & HIDDEN_MODE) gameMode ^= HIDDEN_MODE;
    }
    if ((string) button->text == "Chaos") {
        gameMode ^= CHAOS_MODE;
    }
    if ((string) button->text == "Hidden") {
        gameMode ^= HIDDEN_MODE;
        if (gameMode & CLASSIC_MODE) gameMode ^= CLASSIC_MODE;
    }
    
    if ((string) button->text == "Hard-rock") {
        gameMode ^= HARD_ROCK_MODE;
    }
    if ((string) button->text == "Double time") {
        gameMode ^= DOUBLE_TIME_MODE;
    }
    if ((string) button->text == "Flashlight") {
        gameMode ^= FLASHLIGHT_MODE;
    }
    if ((string) button->text == "Cheese") {
        gameMode ^= CHEESE_MODE;
    }
    if ((string) button->text == "Mirror") {
        gameMode ^= MIRROR_MODE;
    }
    if ((string) button->text == "Play!") {
        isPlaying = true;
    }
}

void handleButtonEvent(Button* button, SDL_Event* event) {
    if (event->type == SDL_EVENT_MOUSE_MOTION || event->type == SDL_EVENT_MOUSE_BUTTON_DOWN || event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        float mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (mouseX >= button->rect.x && mouseX < button->rect.x + button->rect.w &&
            mouseY >= button->rect.y && mouseY < button->rect.y + button->rect.h) {
            button->isHovered = true;
            if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                handleClickedEvent(button);
            }
        } else {
            button->isHovered = false;
        }
    }
}

void renderButton(SDL_Renderer* renderer, Button* button) {
    if ((string) button->text == "Classic") {
        if (gameMode & CLASSIC_MODE) button->bgColor = SELECTED_COLOR;
        else button->bgColor = DESELECTED_COLOR;
    }
    if ((string) button->text == "Chaos") {
        if (gameMode & CHAOS_MODE) button->bgColor = SELECTED_COLOR;
        else button->bgColor = DESELECTED_COLOR;
    }
    if ((string) button->text == "Hidden") {
        if (gameMode & HIDDEN_MODE) button->bgColor = SELECTED_COLOR;
        else button->bgColor = DESELECTED_COLOR;
    }
    if ((string) button->text == "Hard-rock") {
        if (gameMode & HARD_ROCK_MODE) button->bgColor = SELECTED_COLOR;
        else button->bgColor = DESELECTED_COLOR;
    }
    if ((string) button->text == "Double time") {
        if (gameMode & DOUBLE_TIME_MODE) button->bgColor = SELECTED_COLOR;
        else button->bgColor = DESELECTED_COLOR;
    }
    if ((string) button->text == "Flashlight") {
        if (gameMode & FLASHLIGHT_MODE) button->bgColor = SELECTED_COLOR;
        else button->bgColor = DESELECTED_COLOR;
    }
    if ((string) button->text == "Cheese") {
        if (gameMode & CHEESE_MODE) button->bgColor = SELECTED_COLOR;
        else button->bgColor = DESELECTED_COLOR;
    }
    if ((string) button->text == "Mirror") {
        if (gameMode & MIRROR_MODE) button->bgColor = SELECTED_COLOR;
        else button->bgColor = DESELECTED_COLOR;
    }
    SDL_Color currentColor = button->isHovered ? button->hoverColor : button->bgColor;
    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
    SDL_RenderFillRect(renderer, &button->rect);

    float textWidth, textHeight;
    SDL_GetTextureSize(button->texture, &textWidth, &textHeight);

    SDL_FRect textRect;
    textRect.x = button->rect.x + (button->rect.w - textWidth) / 2;
    textRect.y = button->rect.y + (button->rect.h - textHeight) / 2;
    textRect.w = (float)textWidth;
    textRect.h = (float)textHeight;

    SDL_RenderTexture(renderer, button->texture, NULL, &textRect);
}

void destroyButton(Button* button) {
    SDL_DestroyTexture(button->texture);
    SDL_DestroySurface(button->textSurface);
    SDL_free(button->text);
    delete button;
}

#endif
