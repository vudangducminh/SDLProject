#ifndef HOLDER_H
#define HOLDER_H

#include<bits/stdc++.h>
#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include "../const/data.h"
#include "../layout/piece.h"
#include "board.h"

void repaintHolder() {
	SDL_FRect rect = {boardCoordinateX - BLOCK_SIZE * 7, boardCoordinateY, BLOCK_SIZE * 6, BLOCK_SIZE * 4};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderFillRect(renderer, &rect);
    if (holdingPiece) {
        int x = boardCoordinateX - BLOCK_SIZE * 6;
        int y = boardCoordinateY;
        paintPiece(holdingPiece, x, y, BLOCK_SIZE);
    }
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &rect);
}


#endif