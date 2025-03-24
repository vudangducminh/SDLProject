#ifndef QUEUE_H
#define QUEUE_H

#include<bits/stdc++.h>
#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include "../const/data.h"
#include "../layout/piece.h"
#include "board.h"
using namespace std;

void reloadBatch() {
	if (currentQueue.size() > QUEUE_SIZE) return;
	newBatch.clear();
	for (int i = maxPieceID + 1; i <= maxPieceID + 7; i++) newBatch.push_back(i);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < i; j++) {
			if (rng() & 1) swap(newBatch[i], newBatch[j]);
		}
	}
	for (auto i: newBatch) {
		maxPieceID++;
		if (gameMode & CHAOS_MODE) {
			COLOR[maxPieceID] = {(int) rng() % 256, (int) rng() % 256, (int) rng() % 256, 255}; 
			// Avoid dark colors because it's hard to distinguish the board and pieces  
			while (COLOR[maxPieceID].r < 10 && COLOR[maxPieceID].g < 10 && COLOR[maxPieceID].b < 10) {
				COLOR[maxPieceID] = {(int) rng() % 256, (int) rng() % 256, (int) rng() % 256, 255}; 
			}
			currentQueue.push_back(i);
		} else {
			if (i % 7 == 0) currentQueue.push_back(7);
			else currentQueue.push_back(i % 7);
		}
	}
}

void repaintQueue() {
	if (gameMode & HIDDEN_MODE || gameMode & CLASSIC_MODE) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
		SDL_FRect rect = {boardCoordinateX + (COL + 1) * BLOCK_SIZE, boardCoordinateY, NORMAL_BLOCK_SIZE * 4, NORMAL_BLOCK_SIZE * 3 * QUEUE_SIZE + 30};
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderRect(renderer, &rect);
		return;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_FRect rect = {boardCoordinateX + (COL + 1) * BLOCK_SIZE, boardCoordinateY, NORMAL_BLOCK_SIZE * 4, NORMAL_BLOCK_SIZE * 3 * QUEUE_SIZE + 30};
	SDL_RenderFillRect(renderer, &rect);

	vector<int> tmp;
	for (int i = 1; i <= 5; i++) {
		int piece = currentQueue.front(); 
		currentQueue.pop_front();
		tmp.push_back(piece);
		int x = (NORMAL_BLOCK_SIZE - MINI_BLOCK_SIZE) * 2 + boardCoordinateX + (COL + 1) * BLOCK_SIZE;
		int y = boardCoordinateY + (i - 1) * 3 * NORMAL_BLOCK_SIZE;
		paintPiece(piece, x, y, MINI_BLOCK_SIZE);

	}

	while (tmp.size()) {
		currentQueue.push_front(tmp.back());
		tmp.pop_back();
	}

	rect = {boardCoordinateX + (COL + 1) * BLOCK_SIZE, boardCoordinateY, NORMAL_BLOCK_SIZE * 4, NORMAL_BLOCK_SIZE * 3 * QUEUE_SIZE + 30};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &rect);
}

#endif