#define SDL_MAIN_USE_CALLBACKS
#include<bits/stdc++.h>
#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<SDL3_image/SDL_image.h>
#include <unistd.h>
#include "algorithm.h"
#include "const/data.h"
#include "const/UI.h"
#include "layout/piece.h"
#include "layout/stat.h"
#include "gameplay/dropping.h"
#include "gameplay/shadow_piece.h"
#include "gameplay/clear_lines.h"
#include "gameplay/calculate_score.h"
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
	curGameTime = curPaintTime;
	if (!isInitialized) {
		isInitialized = true;
		currentLevel = 1;
		if (gameMode & HARD_ROCK_MODE) {
			currentLevel += 4;
			levelOffset -= 2;
			COL = 12;
		}
		if (gameMode & DOUBLE_TIME_MODE) {
			currentLevel += 20;
			levelOffset -= 6;
			ROW = 10;
			BLOCK_SIZE = 60;
		}
		initializeBoard(ROW, COL, QUEUE_SIZE);
		cap = droppingSpeed[currentLevel];
		startGameTime = curPaintTime;
	}
	
	reloadBatch();
	if (currentPiece == -1) {
		currentPiece = currentQueue.front(); currentQueue.pop_front();
		currentX = 4, currentY = -1, currentD = 0; 
		isMoved = 30; spawnTime = FPS / 10;
	}
	keyboardStateUpdate();
	if (gameOver) {
		// Lose
		return;
	}
	if (!dropping(currentPiece, currentX, currentY, currentD)) {
		linesCleared = clearLines();
		updateClearLinesText(linesCleared);
		totalLinesCleared += linesCleared;
		// New level
		if (totalLinesCleared >= linesPerLevel[currentLevel + levelOffset]) {
			currentLevel++;
		}
		if (gameMode & FLASHLIGHT_MODE) {
			if (totalLinesCleared >= 50) visualRadius = 4;
			if (totalLinesCleared >= 100) visualRadius = 3;
			if (totalLinesCleared >= 150) visualRadius = 2;
		}
		currentScore += calculateScore(linesCleared);
		numberOfPiece++;
		currentPiece = currentQueue.front(); currentQueue.pop_front();
		currentX = 4, currentY = -1, currentD = 0;
		isMoved = 30; spawnTime = FPS / 10; isHoldingPieceAccessible = true;
		if (!checkPiece(currentPiece, currentX, currentY, currentD)) {
			gameOver = true;
			return;
		}
		currentShadowRow = -1;
	}

	// Add cheese
	if (gameMode & CHEESE_MODE) {
		currentCheeseLines++;
		if (currentCheeseLines == nextCheeseLines) {
			int randNum = rng() % 100 + 1;
			int numLines = randNum > 80 ? 2 : 1;
			if (addCheese(numLines)) {
				currentCheeseLines = 0;
				nextCheeseLines = max(FPS / 3, nextCheeseLines - 1);
			} else {
				gameOver = true;
			}
		}
	}

	// Reverse board
	if (gameMode & MIRROR_MODE) {
		currentMirrorFrame++;
		if (currentMirrorFrame == nextMirrorTime) {
			currentMirrorFrame = 0;
			nextMirrorTime = max(300ull, rng() % 720 + 1);
			reverseBoardTimes++;
		}
	}

	// Update clear-lines text
	if (currentClearLinesTextFrame < clearLinesTextDuration) currentClearLinesTextFrame++; 
}

void repaint() {
	if (!isPlaying) {
		// Set home screen (button & stuff)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderButton(renderer, classicModeButton);
        renderButton(renderer, chaosButton);
        renderButton(renderer, hiddenButton);
        renderButton(renderer, hardRockButton);
        renderButton(renderer, doubleTimeButton);
        renderButton(renderer, flashlightButton);
        renderButton(renderer, cheeseButton);
        renderButton(renderer, mirrorButton);
        renderButton(renderer, playButton);
        SDL_RenderPresent(renderer);
		return;
	}
	
	repaintBoard();
	repaintQueue();
	repaintHolder();
	// Render stats
	renderScore();
	renderLinesCleared();
	renderLevel();
	renderClearLinesText(linesCleared);
    SDL_RenderPresent(renderer); 
}

SDL_AppResult SDL_AppEvent(void *appState, SDL_Event *event) {
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}
            
	handleButtonEvent(classicModeButton, event);
	handleButtonEvent(chaosButton, event);
	handleButtonEvent(hiddenButton, event);
	handleButtonEvent(hardRockButton, event);
	handleButtonEvent(doubleTimeButton, event);
	handleButtonEvent(flashlightButton, event);
	handleButtonEvent(cheeseButton, event);
	handleButtonEvent(mirrorButton, event);
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

	fontRegular40 = TTF_OpenFont("C++/Fonts/Commissioner-Regular.ttf", 40);
	if (!fontRegular40) {
		SDL_Log("Error loading font: %s", SDL_GetError());
		return SDL_APP_FAILURE;
    }

	fontBold28 = TTF_OpenFont("C++/Fonts/Commissioner-Bold.ttf", 28);
	if (!fontBold28) {
		SDL_Log("Error loading font: %s", SDL_GetError());
		return SDL_APP_FAILURE;
    }
	fontBold22 = TTF_OpenFont("C++/Fonts/Commissioner-Bold.ttf", 22);
	if (!fontBold22) {
		SDL_Log("Error loading font: %s", SDL_GetError());
		return SDL_APP_FAILURE;
    }

	// Enable alpha 
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 
	
	// Pre-load fixed data
	initializeDroppingSpeed();
	initializeColor();

	classicModeButton = createButton(renderer, 128, 170, 200, 50, "Classic", textColor, DESELECTED_COLOR, hoverColor, fontBold28);
	chaosButton = createButton(renderer, 456, 170, 200, 50, "Chaos", textColor, DESELECTED_COLOR, hoverColor, fontBold28);
	hiddenButton = createButton(renderer, 784, 170, 200, 50, "Hidden", textColor, DESELECTED_COLOR, hoverColor, fontBold28);
	hardRockButton = createButton(renderer, 1112, 170, 200, 50, "Hard-rock", textColor, DESELECTED_COLOR, hoverColor, fontBold28);
	doubleTimeButton = createButton(renderer, 128, 250, 200, 50, "Double time", textColor, DESELECTED_COLOR, hoverColor, fontBold28);
	flashlightButton = createButton(renderer, 456, 250, 200, 50, "Flashlight", textColor, DESELECTED_COLOR, hoverColor, fontBold28);
	cheeseButton = createButton(renderer, 784, 250, 200, 50, "Cheese", textColor, DESELECTED_COLOR, hoverColor, fontBold28);
	mirrorButton = createButton(renderer, 1112, 250, 200, 50, "Mirror", textColor, DESELECTED_COLOR, hoverColor, fontBold28);
	playButton = createButton(renderer, 620, 570, 200, 50, "Play!", textColor, normalColor, hoverColor, fontBold28);
	return SDL_APP_CONTINUE;
}
