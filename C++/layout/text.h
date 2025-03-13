#ifndef TEXT_H
#define TEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <bits/stdc++.h>
using namespace std;

struct Text {
    SDL_FRect rect;
    SDL_Color textColor;
    SDL_Texture* texture;
    SDL_Surface* textSurface;
    char* text;
};

// Function to create a text
Text* createText(SDL_Renderer* renderer, int x, int y, int w, int h,
                    const char* text, SDL_Color textColor, TTF_Font* font) {
    Text* newText = new Text();
    newText->rect.x = (float)x;
    newText->rect.y = (float)y;
    newText->rect.w = (float)w;
    newText->rect.h = (float)h;

    newText->textColor = textColor;

    newText->text = SDL_strdup(text); 
    if (font != nullptr) newText->textSurface = TTF_RenderText_Solid(font, text, strlen(text), textColor);

    if (!newText->textSurface) {
        std::cerr << "TTF_RenderText_Blended Error: " << SDL_GetError() << std::endl;
        delete newText;
        return nullptr;
    }

    newText->texture = SDL_CreateTextureFromSurface(renderer, newText->textSurface);
    if (!newText->texture) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_DestroySurface(newText->textSurface);
        delete newText;
        return nullptr;
    }

    return newText;
}

void renderText(SDL_Renderer* renderer, Text* newText) {
    float textWidth, textHeight;
    SDL_GetTextureSize(newText->texture, &textWidth, &textHeight);

    SDL_FRect textRect;
    textRect.x = newText->rect.x + (newText->rect.w - textWidth) / 2;
    textRect.y = newText->rect.y + (newText->rect.h - textHeight) / 2;
    textRect.w = (float)textWidth;
    textRect.h = (float)textHeight;

    SDL_RenderTexture(renderer, newText->texture, NULL, &textRect);
}

void destroyText(Text* newText) {
    SDL_DestroyTexture(newText->texture);
    SDL_DestroySurface(newText->textSurface);
    SDL_free(newText->text);
    delete newText;
}

#endif
