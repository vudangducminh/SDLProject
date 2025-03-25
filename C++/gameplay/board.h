#ifndef BOARD_H
#define BOARD_H

#include <bits/stdc++.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "../const/data.h"
#include "../layout/piece.h"
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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_RenderFillRect(renderer, &rect);
	for (int j = 0; j < ROW + 10; j++) {
		for (int i = 0; i < COL; i++) {
			int dist = (j - 10 - currentY) * (j - 10 - currentY) + (i - currentX) * (i - currentX);
			rect = {(float) i * BLOCK_SIZE + boardCoordinateX, (float) (j - 10) * BLOCK_SIZE + boardCoordinateY, BLOCK_SIZE, BLOCK_SIZE};
			if (reverseBoardTimes & 1) {
				rect = {(float) (COL - i - 1) * BLOCK_SIZE + boardCoordinateX, (float) (ROW + 9 - j) * BLOCK_SIZE + boardCoordinateY, BLOCK_SIZE, BLOCK_SIZE};
			}
			if (state[i][j] || (!state[i][j] && j >= 10)) {
				if (gameMode & FLASHLIGHT_MODE) {
					if (dist < visualRadius * visualRadius || gameOver) {
						SDL_SetRenderDrawColor(renderer, COLOR[state[i][j]].r, COLOR[state[i][j]].g, COLOR[state[i][j]].b, COLOR[state[i][j]].a);
					} else {
						SDL_SetRenderDrawColor(renderer, COLOR[BLIND_COLOR].r, COLOR[BLIND_COLOR].g, COLOR[BLIND_COLOR].b, COLOR[BLIND_COLOR].a);
					}
				} else {
					SDL_SetRenderDrawColor(renderer, COLOR[state[i][j]].r, COLOR[state[i][j]].g, COLOR[state[i][j]].b, COLOR[state[i][j]].a);
				}
				SDL_RenderFillRect(renderer, &rect);
			}
			if (j >= 10) {
				// Render cells inside the board
				SDL_SetRenderDrawColor(renderer, 178, 178, 178, 58);
				SDL_RenderRect(renderer, &rect);
			}
		}
	}
	rect = {boardCoordinateX, boardCoordinateY, COL * BLOCK_SIZE, ROW * BLOCK_SIZE};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &rect);
}

bool addCheese(int lines) {
	removePiece(currentPiece, currentX, currentY, currentD);
	for (int j = 0; j < ROW + 10 - lines; j++) {
		for (int i = 0; i < COL; i++) {
			state[i][j] = state[i][j + lines];
		}
	}
	int nullCell = rng() % COL;
	for (int j = ROW + 10 - lines; j < ROW + 10; j++) {
		for (int i = 0; i < COL; i++) {
			if (i == nullCell) state[i][j] = 0;
			else state[i][j] = GARBAGE;
		}
	}
	if (checkPiece(currentPiece, currentX, currentY, currentD)) {
		fillPiece(currentPiece, currentX, currentY, currentD);
	} else if (checkPiece(currentPiece, currentX, currentY - 1, currentD)) {
		currentY--;
		fillPiece(currentPiece, currentX, currentY, currentD);
	} else if (checkPiece(currentPiece, currentX, currentY - 2, currentD)) {
		currentY -= 2;
		fillPiece(currentPiece, currentX, currentY, currentD);
	}
	else {
		currentY -= 3;
		fillPiece(currentPiece, currentX, currentY, currentD);
		return 0;
	}
	return 1;
}
#endif