#ifndef HOLDER_H
#define HOLDER_H

#include<bits/stdc++.h>
#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include "../const/data.h"
#include "../layout/piece.h"
#include "board.h"

void repaintHolder() {
    if (gameMode & CLASSIC_MODE) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
		SDL_FRect rect = {boardCoordinateX - NORMAL_BLOCK_SIZE * 7, boardCoordinateY, NORMAL_BLOCK_SIZE * 6, NORMAL_BLOCK_SIZE * 4};
        SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderRect(renderer, &rect);
		return;
	}
	SDL_FRect rect = {boardCoordinateX - NORMAL_BLOCK_SIZE * 7, boardCoordinateY, NORMAL_BLOCK_SIZE * 6, NORMAL_BLOCK_SIZE * 4};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderFillRect(renderer, &rect);
    if (holdingPiece) {
        int x = boardCoordinateX - NORMAL_BLOCK_SIZE * 6;
        int y = boardCoordinateY;
        if (isHoldingPieceAccessible) paintPiece(holdingPiece, x, y, NORMAL_BLOCK_SIZE);
        else paintPieceGray(holdingPiece, x, y, NORMAL_BLOCK_SIZE);
    }
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &rect);
}


#endif