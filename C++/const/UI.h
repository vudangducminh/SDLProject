#ifndef UI_H
#define UI_H

#include<bits/stdc++.h>
#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include "../layout/text.h"
#include "../layout/button.h"

using namespace std;

// Main 
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* playerTexture;
SDL_Event event;

// Button & text
Button* classicModeButton;
Button* chaosButton;
Button* hiddenButton;
Button* hardRockButton;
Button* doubleTimeButton;
Button* flashlightButton;
Button* cheeseButton;   
Button* playButton;
Text* errorText;
Text* scoreText;
Text* linesClearedText;
Text* levelText;

// Button color
SDL_Color normalColor = {200, 200, 200, 255};
SDL_Color hoverColor = {255, 255, 255, 32};
SDL_Color textColor = {0, 0, 0, 255};

// Fonts
TTF_Font* fontBold28;
TTF_Font* fontBold22;


#endif