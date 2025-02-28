#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>
#include <bits/stdc++.h>
using namespace std;

struct Button {
    SDL_FRect rect;
    SDL_Color normalColor;
    SDL_Color hoverColor;
    SDL_Color clickColor;
    SDL_Color currentColor;
    bool isClicked;
};

Button createButton(float x, float y, float w, float h, SDL_Color normal, SDL_Color hover, SDL_Color click) {
    Button button;
    button.rect = {x, y, w, h};
    button.normalColor = normal;
    button.hoverColor = hover;
    button.clickColor = click;
    button.currentColor = normal;
    button.isClicked = false;
    return button;
}

void handleButtonEvent(Button& button, SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_MOTION || event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        float x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        if (x < button.rect.x || x > button.rect.x + button.rect.w || y < button.rect.y || y > button.rect.y + button.rect.h) {
            inside = false;
        } ;
        if (!inside) {
            button.currentColor = button.normalColor;
            button.isClicked = false;
        } else {
            switch (event.type) {
                case SDL_EVENT_MOUSE_MOTION:
                    button.currentColor = button.hoverColor;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    button.currentColor = button.clickColor;
                    button.isClicked = true;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    if (button.isClicked) {
                        cout << "Button Clicked!" << "\n";
                    }
                    button.currentColor = button.hoverColor;
                    button.isClicked = false;
                    break;
            }
        }
    }
}

void renderButton(SDL_Renderer* renderer, const Button& button) {
    SDL_SetRenderDrawColor(renderer, button.currentColor.r, button.currentColor.g, button.currentColor.b, button.currentColor.a);
    SDL_RenderFillRect(renderer, &button.rect);
}

#endif

// int main(int argc, char* argv[]) {
//     SDL_Color normalColor = {200, 200, 200, 255}; // Gray
//     SDL_Color hoverColor = {150, 150, 150, 255};  // Darker Gray
//     SDL_Color clickColor = {100, 100, 100, 255};  // Even Darker Gray

//     Button myButton = createButton(100.0f, 100.0f, 200.0f, 50.0f, normalColor, hoverColor, clickColor);  //Using floats

//     bool quit = false;
//     SDL_Event event;

//     while (!quit) {
//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_EVENT_QUIT) { // SDL_QUIT -> SDL_EVENT_QUIT
//                 quit = true;
//             }
//             handleButtonEvent(myButton, event);  // Pass the button to the event handler
//         }
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
//         SDL_RenderClear(renderer);
//         renderButton(renderer, myButton);
//         SDL_RenderPresent(renderer);
//     }
// }