#ifndef BOARD_H
#define BOARD_H

#include <bits/stdc++.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "../const/data.h"
// #include "piece.h"
using namespace std;

void initializeBoard(int row, int col, int queueSize) {
    ROW = row;
    COL = col;
    QUEUE_SIZE = queueSize;
    gameOver = false;
    boardCoordinateX = (MAX_SCREEN_WIDTH - col * BLOCK_SIZE) / 2;
    boardCoordinateY = (MAX_SCREEN_HEIGHT - row * BLOCK_SIZE) / 2;
    for (int i = 0; i < ROW + 10; i++) {
        for (int j = 0; j < COL; j++) {
            state[j][i] = 0;
        }
    }
}


void repaintBoard() {
	SDL_FRect rect = {0, 0, MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGHT};
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_RenderFillRect(renderer, &rect);
	for (int j = 0; j < ROW + 10; j++) {
		for (int i = 0; i < COL; i++) {
			rect = {(float) i * BLOCK_SIZE + boardCoordinateX, (float) (j - 10) * BLOCK_SIZE + boardCoordinateY, BLOCK_SIZE, BLOCK_SIZE};
			if (state[i][j] || (!state[i][j] && j >= 10)) {
				SDL_SetRenderDrawColor(renderer, COLOR[state[i][j]].r, COLOR[state[i][j]].g, COLOR[state[i][j]].b, COLOR[state[i][j]].a);
				SDL_RenderFillRect(renderer, &rect);
			}
			if (j >= 10) {
				SDL_SetRenderDrawColor(renderer, 178, 178, 178, 58);
				SDL_RenderRect(renderer, &rect);
			}
		}
	}
	rect = {boardCoordinateX, boardCoordinateY, COL * BLOCK_SIZE, ROW * BLOCK_SIZE};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &rect);
}

#endif