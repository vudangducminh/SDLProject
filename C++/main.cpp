#define SDL_MAIN_USE_CALLBACKS
#include<bits/stdc++.h>
#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<SDL3_image/SDL_image.h>
#include <unistd.h>
#include "const/data.h"
#include "layout/piece.h"
#include "layout/button.h"
#include "gameplay/dropping.h"
#include "gameplay/shadow_piece.h"
#include "gameplay/clear_lines.h"
#include "gameplay/queue.h"
#include "gameplay/holder.h"
#include "gameplay/board.h"
#include "input/input.h"
using namespace std;

void SDL_AppQuit(void *appState, SDL_AppResult appResult) {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

double curPaintTime, nextPaintTime;

void update() {
	curPaintTime = clock();
	if (!isPlaying) {
		return;
	}

	if (!isInitialized) {
		isInitialized = true;
		if (gameMode & CHAOS_MODE) initializeChaosColor();
		else initializeColor();
		initializeBoard(ROW, COL, QUEUE_SIZE);
	}
	
	reloadBatch();
	if (currentPiece == -1) {
		currentPiece = currentQueue.front(); currentQueue.pop_front();
		currentX = 4, currentY = -1, currentD = 0; 
		isMoved = 30; spawnTime = FPS / 10;
	}
	if (gameOver) {
		// Lose
		return;
	}
	keyboardStateUpdate();
	if (!dropping(currentPiece, currentX, currentY, currentD)) {
		clearLines();
		if (gameMode & CHAOS_MODE) initializeChaosColor();
		currentPiece = currentQueue.front(); currentQueue.pop_front();
		currentX = 4, currentY = -1, currentD = 0;
		isMoved = 30; spawnTime = FPS / 10; isHoldingPieceAccessible = true;
		if (!checkPiece(currentPiece, currentX, currentY, currentD)) {
			gameOver = true;
			return;
		}
		currentShadowRow = -1;
	}
}


Button* classicModeButton;
Button* chaosButton;
Button* playButton;

void repaint() {
	if (!isPlaying) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderButton(renderer, classicModeButton);
        renderButton(renderer, chaosButton);
        renderButton(renderer, playButton);
        SDL_RenderPresent(renderer);
		return;
	}
	repaintBoard();
	repaintQueue();
	repaintHolder();
	
    SDL_RenderPresent(renderer); 
	
}

SDL_AppResult SDL_AppEvent(void *appState, SDL_Event *event) {
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}
            
	handleButtonEvent(classicModeButton, event);
	handleButtonEvent(chaosButton, event);
	handleButtonEvent(playButton, event);
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appState) {
	update();
	repaint();
	clock_t duration = clock() - curPaintTime;
	// cout << duration << "\n";
	nextPaintTime = curPaintTime + 1000 / FPS;
	// Sleep for 1e6 / FPS microseconds
	usleep(max((double) 0, 1e6 / FPS - duration / CLOCKS_PER_SEC / CLOCKS_PER_SEC));
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void **appState, int argc, char **argv) {
	rng.seed((long long)main ^ time(0));

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Error initializing SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	window = SDL_CreateWindow(
		"Tetris",
		MAX_SCREEN_WIDTH,
		MAX_SCREEN_HEIGHT,
		NULL
	);

	if (!window) {
		SDL_Log("Error creating window: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	
	renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer) {
		SDL_Log("Error creating renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if(!TTF_Init()) {
        std::cerr << "SDL_ttf Init Failed: " << std::endl;
        SDL_Quit();
		return SDL_APP_FAILURE;
    }

	fontBold = TTF_OpenFont("C++/Fonts/Commissioner-Bold.ttf", 28);
	if (!fontBold) {
		SDL_Log("Error loading font: %s", SDL_GetError());
		return SDL_APP_FAILURE;
    }

	classicModeButton = createButton(renderer, 100, 100, 200, 50, "Classic", textColor, deselectedColor, hoverColor, fontBold);
	chaosButton = createButton(renderer, 350, 100, 200, 50, "Chaos", textColor, deselectedColor, hoverColor, fontBold);
	playButton = createButton(renderer, 600, 100, 200, 50, "Play!", textColor, normalColor, hoverColor, fontBold);

	return SDL_APP_CONTINUE;
}