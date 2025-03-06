#ifndef PIECE_H
#define PIECE_H

#include<bits/stdc++.h>
#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include "../gameplay/board.h"
#include "../const/data.h"
using namespace std;

int currentPiece = -1, currentX = 4, currentY = -1, currentD = 0;

void initializeColor() {
    COLOR[0] = {0, 0, 0, 255}; 
    COLOR[PIECE_T] = {128, 0, 128, 255}; 
    COLOR[PIECE_O] = {255, 255, 0, 255}; 
    COLOR[PIECE_J] = {0, 0, 255, 255}; 
    COLOR[PIECE_L] = {255, 140, 0, 255};
    COLOR[PIECE_S] = {0, 255, 0, 255};
    COLOR[PIECE_Z] = {255, 0, 0, 255};
    COLOR[PIECE_I] = {0, 255, 255, 255};
    COLOR[SHADOW_PIECE] = {178, 178, 178, 58}; 
}


void initializeChaosColor() {
    COLOR[0] = {0, 0, 0, 255}; 
    COLOR[PIECE_T] = {(int) rng() % 256, (int) rng() % 256, (int) rng() % 256, 255}; 
    COLOR[PIECE_O] = {(int) rng() % 256, (int) rng() % 256, (int) rng() % 256, 255}; 
    COLOR[PIECE_J] = {(int) rng() % 256, (int) rng() % 256, (int) rng() % 256, 255}; 
    COLOR[PIECE_L] = {(int) rng() % 256, (int) rng() % 256, (int) rng() % 256, 255}; 
    COLOR[PIECE_S] = {(int) rng() % 256, (int) rng() % 256, (int) rng() % 256, 255}; 
    COLOR[PIECE_Z] = {(int) rng() % 256, (int) rng() % 256, (int) rng() % 256, 255}; 
    COLOR[PIECE_I] = {(int) rng() % 256, (int) rng() % 256, (int) rng() % 256, 255}; 
    COLOR[SHADOW_PIECE] = {178, 178, 178, 58}; 
}

bool isOccupied(int x, int y) {
    return state[x][y] > 0 && state[x][y] < 8;
}


bool checkT(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        if (x <= 0 || x >= COL - 1 || y <= -2 || y >= ROW) return false;
        return (isOccupied(x, y + 10) + isOccupied(x - 1, y + 10) + isOccupied(x + 1, y + 10) + isOccupied(x, y + 9)) == 0;
    }
    
    else if (direction == DEGREE_90) {
        if (x < 0 || x >= COL - 1 || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 9) + isOccupied(x, y + 11) + isOccupied(x, y + 10) + isOccupied(x + 1, y + 10)) == 0;
    }
    
    else if (direction == DEGREE_180) {
        if (x <= 0 || x >= COL - 1 || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 10) + isOccupied(x - 1, y + 10) + isOccupied(x + 1, y + 10) + isOccupied(x, y + 11)) == 0;
    }
    
    else {
        if (x <= 0 || x >= COL || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 9) + isOccupied(x, y + 11) + isOccupied(x, y + 10) + isOccupied(x - 1, y + 10)) == 0;
    }
    return true;
}

void fillT(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x][y + 9] = PIECE_T;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x + 1][y + 10] = PIECE_T;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x][y + 11] = PIECE_T;
    }
    else {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x - 1][y + 10] = PIECE_T;
    }
}

void fillShadowT(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x][y + 9] = SHADOW_PIECE;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x + 1][y + 10] = SHADOW_PIECE;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x][y + 11] = SHADOW_PIECE;
    }
    else {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x - 1][y + 10] = SHADOW_PIECE;
    }
}

void removeT(int x, int y, int direction) {
    if (checkT(x, y, direction)) return;
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x][y + 9] = 0;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x + 1][y + 10] = 0;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x][y + 11] = 0;
    }
    else {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x - 1][y + 10] = 0;
    }
}

bool checkO(int x, int y, int direction) {
    if (x < 0 || x >= COL - 1 || y >= ROW || y <= -2) return false;
    return (isOccupied(x, y + 10) + isOccupied(x + 1, y + 10) + isOccupied(x, y + 9) + state[x + 1][y + 9]) == 0;
}

void fillO(int x, int y, int direction) {
    state[x][y + 10] = state[x + 1][y + 10] = state[x][y + 9] = state[x + 1][y + 9] = PIECE_O;
}

void fillShadowO(int x, int y, int direction) {
    state[x][y + 10] = state[x + 1][y + 10] = state[x][y + 9] = state[x + 1][y + 9] = SHADOW_PIECE;
}

void removeO(int x, int y, int direction) {
    state[x][y + 10] = state[x + 1][y + 10] = state[x][y + 9] = state[x + 1][y + 9] = 0;
}

bool checkJ(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        if (x <= 0 || x >= COL - 1 || y <= -2 || y >= ROW) return false;
        return (isOccupied(x, y + 10) + isOccupied(x - 1, y + 10) + isOccupied(x + 1, y + 10) + isOccupied(x - 1, y + 9)) == 0;
    }
    
    else if (direction == DEGREE_90) {
        if (x < 0 || x >= COL - 1 || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 9) + isOccupied(x, y + 11) + isOccupied(x, y + 10) + isOccupied(x + 1, y + 9)) == 0;
    }
    
    else if (direction == DEGREE_180) {
        if (x <= 0 || x >= COL - 1 || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 10) + isOccupied(x - 1, y + 10) + isOccupied(x + 1, y + 10) + isOccupied(x + 1, y + 11)) == 0;
    }
    
    else {
        if (x <= 0 || x >= COL || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 9) + isOccupied(x, y + 11) + isOccupied(x, y + 10) + isOccupied(x - 1, y + 11)) == 0;
    }
    return true;
}

void fillJ(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x - 1][y + 9] = PIECE_J;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x + 1][y + 9] = PIECE_J;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x + 1][y + 11] = PIECE_J;
    }
    else {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x - 1][y + 11] = PIECE_J;
    }
}

void fillShadowJ(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x - 1][y + 9] = SHADOW_PIECE;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x + 1][y + 9] = SHADOW_PIECE;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x + 1][y + 11] = SHADOW_PIECE;
    }
    else {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x - 1][y + 11] = SHADOW_PIECE;
    }
}

void removeJ(int x, int y, int direction) {
    if (checkJ(x, y, direction)) return;
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x - 1][y + 9] = 0;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x + 1][y + 9] = 0;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x + 1][y + 11] = 0;
    }
    else {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x - 1][y + 11] = 0;
    }
}


bool checkL(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        if (x <= 0 || x >= COL - 1 || y <= -2 || y >= ROW) return false;
        return (isOccupied(x, y + 10) + isOccupied(x - 1, y + 10) + isOccupied(x + 1, y + 10) + isOccupied(x + 1, y + 9)) == 0;
    }
    
    else if (direction == DEGREE_90) {
        if (x < 0 || x >= COL - 1 || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 9) + isOccupied(x, y + 11) + isOccupied(x, y + 10) + isOccupied(x + 1, y + 11)) == 0;
    }
    
    else if (direction == DEGREE_180) {
        if (x <= 0 || x >= COL - 1 || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 10) + isOccupied(x - 1, y + 10) + isOccupied(x + 1, y + 10) + isOccupied(x - 1, y + 11)) == 0;
    }
    
    else {
        if (x <= 0 || x >= COL || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 9) + isOccupied(x, y + 11) + isOccupied(x, y + 10) + isOccupied(x - 1, y + 9)) == 0;
    }
    return true;
}

void fillL(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x + 1][y + 9] = PIECE_L;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x + 1][y + 11] = PIECE_L;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x - 1][y + 11] = PIECE_L;
    }
    else {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x - 1][y + 9] = PIECE_L;
    }
}

void fillShadowL(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x + 1][y + 9] = SHADOW_PIECE;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x + 1][y + 11] = SHADOW_PIECE;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x - 1][y + 11] = SHADOW_PIECE;
    }
    else {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x - 1][y + 9] = SHADOW_PIECE;
    }
}

void removeL(int x, int y, int direction) {
    if (checkL(x, y, direction)) return;
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x + 1][y + 9] = 0;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x + 1][y + 11] = 0;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x - 1][y + 11] = 0;
    }
    else {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x - 1][y + 9] = 0;
    }
}

bool checkS(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        if (x <= 0 || x >= COL - 1 || y <= -2 || y >= ROW) return false;
        return (isOccupied(x, y + 10) + isOccupied(x - 1, y + 10) + isOccupied(x + 1, y + 9) + isOccupied(x, y + 9)) == 0;
    }
    
    else if (direction == DEGREE_90) {
        if (x < 0 || x >= COL - 1 || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 9) + isOccupied(x + 1, y + 11) + isOccupied(x, y + 10) + isOccupied(x + 1, y + 10)) == 0;
    }
    
    else if (direction == DEGREE_180) {
        if (x <= 0 || x >= COL - 1 || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 10) + isOccupied(x - 1, y + 11) + isOccupied(x + 1, y + 10) + isOccupied(x, y + 11)) == 0;
    }
    
    else {
        if (x <= 0 || x >= COL || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x - 1, y + 9) + isOccupied(x, y + 11) + isOccupied(x, y + 10) + isOccupied(x - 1, y + 10)) == 0;
    }
    return true;
}

void fillS(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 9] = state[x][y + 9] = PIECE_S;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x + 1][y + 11] = state[x][y + 10] = state[x + 1][y + 10] = PIECE_S;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 11] = state[x + 1][y + 10] = state[x][y + 11] = PIECE_S;
    }
    else {
        state[x - 1][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x - 1][y + 10] = PIECE_S;
    }
}

void fillShadowS(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 9] = state[x][y + 9] = SHADOW_PIECE;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x + 1][y + 11] = state[x][y + 10] = state[x + 1][y + 10] = SHADOW_PIECE;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 11] = state[x + 1][y + 10] = state[x][y + 11] = SHADOW_PIECE;
    }
    else {
        state[x - 1][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x - 1][y + 10] = SHADOW_PIECE;
    }
}

void removeS(int x, int y, int direction) {
    if (checkS(x, y, direction)) return;
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 9] = state[x][y + 9] = 0;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x + 1][y + 11] = state[x][y + 10] = state[x + 1][y + 10] = 0;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 11] = state[x + 1][y + 10] = state[x][y + 11] = 0;
    }
    else {
        state[x - 1][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x - 1][y + 10] = 0;
    }
}

bool checkZ(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        if (x <= 0 || x >= COL - 1 || y <= -2 || y >= ROW) return false;
        return (isOccupied(x, y + 10) + isOccupied(x - 1, y + 9) + isOccupied(x + 1, y + 10) + isOccupied(x, y + 9)) == 0;
    }
    
    else if (direction == DEGREE_90) {
        if (x < 0 || x >= COL - 1 || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 10) + isOccupied(x, y + 11) + isOccupied(x + 1, y + 9) + isOccupied(x + 1, y + 10)) == 0;
    }
    
    else if (direction == DEGREE_180) {
        if (x <= 0 || x >= COL - 1 || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 10) + isOccupied(x - 1, y + 10) + isOccupied(x, y + 11) + isOccupied(x + 1, y + 11)) == 0;
    }
    
    else {
        if (x <= 0 || x >= COL || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 10) + isOccupied(x, y + 9) + isOccupied(x - 1, y + 10) + isOccupied(x - 1, y + 11)) == 0;
    }
    return true;
}

void fillZ(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 9] = state[x + 1][y + 10] = state[x][y + 9] = PIECE_Z;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 10] = state[x][y + 11] = state[x + 1][y + 9] = state[x + 1][y + 10] = PIECE_Z;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 11] = state[x][y + 11] = PIECE_Z;
    }
    else {
        state[x - 1][y + 10] = state[x - 1][y + 11] = state[x][y + 9] = state[x][y + 10] = PIECE_Z;
    }
}

void fillShadowZ(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 9] = state[x + 1][y + 10] = state[x][y + 9] = SHADOW_PIECE;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 10] = state[x][y + 11] = state[x + 1][y + 9] = state[x + 1][y + 10] = SHADOW_PIECE;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 11] = state[x][y + 11] = SHADOW_PIECE;
    }
    else {
        state[x - 1][y + 10] = state[x - 1][y + 11] = state[x][y + 9] = state[x][y + 10] = SHADOW_PIECE;
    }
}

void removeZ(int x, int y, int direction) {
    if (checkZ(x, y, direction)) return;
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 9] = state[x + 1][y + 10] = state[x][y + 9] = 0;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 10] = state[x][y + 11] = state[x + 1][y + 9] = state[x + 1][y + 10] = 0;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 11] = state[x][y + 11] = 0;
    }
    else {
        state[x - 1][y + 10] = state[x - 1][y + 11] = state[x][y + 9] = state[x][y + 10] = 0;
    }
}

bool checkI(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        if (x <= 0 || x >= COL - 2 || y <= -2 || y >= ROW) return false;
        return (isOccupied(x, y + 10) + isOccupied(x - 1, y + 10) + isOccupied(x + 1, y + 10) + isOccupied(x + 2, y + 10)) == 0;
    }
    
    else if (direction == DEGREE_90) {
        if (x < 0 || x >= COL || y <= -2 || y >= ROW - 2) return false;
        return (isOccupied(x, y + 10) + isOccupied(x, y + 11) + isOccupied(x, y + 12) + isOccupied(x, y + 9)) == 0;
    }
    
    else if (direction == DEGREE_180) {
        if (x <= 1 || x >= COL - 1 || y <= -2 || y >= ROW) return false;
        return (isOccupied(x - 2, y + 10) + isOccupied(x - 1, y + 10) + isOccupied(x, y + 10) + isOccupied(x + 1, y + 10)) == 0;
    }
    
    else {
        if (x < 0 || x >= COL || y <= -2 || y >= ROW - 1) return false;
        return (isOccupied(x, y + 10) + isOccupied(x, y + 11) + isOccupied(x, y + 8) + isOccupied(x, y + 9)) == 0;
    }
    return true;
}

void fillI(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x + 2][y + 10] = PIECE_I;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x][y + 12] = PIECE_I;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x - 2][y + 10] = PIECE_I;
    }
    else {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x][y + 8] = PIECE_I;
    }
}

void fillShadowI(int x, int y, int direction) {
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x + 2][y + 10] = SHADOW_PIECE;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x][y + 12] = SHADOW_PIECE;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x - 2][y + 10] = SHADOW_PIECE;
    }
    else {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x][y + 8] = SHADOW_PIECE;
    }
}

void removeI(int x, int y, int direction) {
    if (checkI(x, y, direction)) return;
    if (direction == DEGREE_0) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x + 2][y + 10] = 0;
    }
    else if (direction == DEGREE_90) {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x][y + 12] = 0;
    }
    else if (direction == DEGREE_180) {
        state[x][y + 10] = state[x - 1][y + 10] = state[x + 1][y + 10] = state[x - 2][y + 10] = 0;
    }
    else {
        state[x][y + 9] = state[x][y + 11] = state[x][y + 10] = state[x][y + 8] = 0;
    }
}


void fillPiece(int piece, int x, int y, int direction) {
    if (piece == PIECE_T) fillT(x, y, direction);
    if (piece == PIECE_O) fillO(x, y, direction);
    if (piece == PIECE_J) fillJ(x, y, direction);
    if (piece == PIECE_L) fillL(x, y, direction);
    if (piece == PIECE_S) fillS(x, y, direction);
    if (piece == PIECE_Z) fillZ(x, y, direction);
    if (piece == PIECE_I) fillI(x, y, direction);
}


void fillShadowPiece(int piece, int x, int y, int direction) {
    if (piece == PIECE_T) fillShadowT(x, y, direction);
    if (piece == PIECE_O) fillShadowO(x, y, direction);
    if (piece == PIECE_J) fillShadowJ(x, y, direction);
    if (piece == PIECE_L) fillShadowL(x, y, direction);
    if (piece == PIECE_S) fillShadowS(x, y, direction);
    if (piece == PIECE_Z) fillShadowZ(x, y, direction);
    if (piece == PIECE_I) fillShadowI(x, y, direction);
}

void removePiece(int piece, int x, int y, int direction) {
    if (piece == PIECE_T) removeT(x, y, direction);
    if (piece == PIECE_O) removeO(x, y, direction);
    if (piece == PIECE_J) removeJ(x, y, direction);
    if (piece == PIECE_L) removeL(x, y, direction);
    if (piece == PIECE_S) removeS(x, y, direction);
    if (piece == PIECE_Z) removeZ(x, y, direction);
    if (piece == PIECE_I) removeI(x, y, direction);
}

bool checkPiece(int piece, int x, int y, int direction) {
    bool fillable; 
    if (piece == PIECE_T) {
        fillable = checkT(x, y, direction);
        return fillable;
    }
    if (piece == PIECE_O) {
        fillable = checkO(x, y, direction);
        return fillable;
    }
    if (piece == PIECE_J) {
        fillable = checkJ(x, y, direction);
        return fillable;
    }
    if (piece == PIECE_L) {
        fillable = checkL(x, y, direction);
        return fillable;
    }
    if (piece == PIECE_S) {
        fillable = checkS(x, y, direction);
        return fillable;
    }
    if (piece == PIECE_Z) {
        fillable = checkZ(x, y, direction);
        return fillable;
    }
    if (piece == PIECE_I) {
        fillable = checkI(x, y, direction);
        return fillable;
    }
    return false;
}

void paintT(int x, int y, float blockSize) {
	SDL_FRect rect = {x + blockSize / 2.0F, y + blockSize * 2.0F, blockSize * 3.0F, blockSize};
	SDL_RenderFillRect(renderer, &rect);
    rect = {x + blockSize * 3.0F / 2.0F, y + blockSize, blockSize, blockSize};
	SDL_RenderFillRect(renderer, &rect);
}

void paintO(int x, int y, float blockSize) {
	SDL_FRect rect = {x + blockSize, y + blockSize, blockSize * 2.0F, blockSize * 2.0F};
	SDL_RenderFillRect(renderer, &rect);
}

void paintJ(int x, int y, float blockSize) {
	SDL_FRect rect = {x + blockSize / 2.0F, y + blockSize * 2.0F, blockSize * 3.0F, blockSize};
	SDL_RenderFillRect(renderer, &rect);
    rect = {x + blockSize * 1.0F / 2.0F, y + blockSize, blockSize, blockSize};
	SDL_RenderFillRect(renderer, &rect);
}

void paintL(int x, int y, float blockSize) {
	SDL_FRect rect = {x + blockSize / 2.0F, y + blockSize * 2.0F, blockSize * 3.0F, blockSize};
	SDL_RenderFillRect(renderer, &rect);
    rect = {x + blockSize * 5.0F / 2.0F, y + blockSize, blockSize, blockSize};
	SDL_RenderFillRect(renderer, &rect);
}

void paintZ(int x, int y, float blockSize) {
	SDL_FRect rect = {x + blockSize / 2.0F, y + blockSize, blockSize * 2.0F, blockSize};
	SDL_RenderFillRect(renderer, &rect);
    rect = {x + blockSize * 3.0F / 2.0F, y + blockSize * 2.0F, blockSize * 2.0F, blockSize};
	SDL_RenderFillRect(renderer, &rect);
}

void paintS(int x, int y, float blockSize) {
	SDL_FRect rect = {x + blockSize * 3.0F / 2.0F, y + blockSize, blockSize * 2.0F, blockSize};
	SDL_RenderFillRect(renderer, &rect);
    rect = {x + blockSize / 2.0F, y + blockSize * 2.0F, blockSize * 2.0F, blockSize};
	SDL_RenderFillRect(renderer, &rect);
}

void paintI(int x, int y, float blockSize) {
	SDL_FRect rect = {(float) x, y + blockSize * 3.0F / 2.0F, blockSize * 4.0F, blockSize};
	SDL_RenderFillRect(renderer, &rect);
}

void paintPiece(int piece, int x, int y, float blockSize) {
    SDL_SetRenderDrawColor(renderer, COLOR[piece].r, COLOR[piece].g, COLOR[piece].b, COLOR[piece].a);
    if (piece == PIECE_T) paintT(x, y, blockSize);
    if (piece == PIECE_O) paintO(x, y, blockSize);
    if (piece == PIECE_J) paintJ(x, y, blockSize);
    if (piece == PIECE_L) paintL(x, y, blockSize);
    if (piece == PIECE_S) paintS(x, y, blockSize);
    if (piece == PIECE_Z) paintZ(x, y, blockSize);
    if (piece == PIECE_I) paintI(x, y, blockSize);
}

void paintPieceGray(int piece, int x, int y, float blockSize) {
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    if (piece == PIECE_T) paintT(x, y, blockSize);
    if (piece == PIECE_O) paintO(x, y, blockSize);
    if (piece == PIECE_J) paintJ(x, y, blockSize);
    if (piece == PIECE_L) paintL(x, y, blockSize);
    if (piece == PIECE_S) paintS(x, y, blockSize);
    if (piece == PIECE_Z) paintZ(x, y, blockSize);
    if (piece == PIECE_I) paintI(x, y, blockSize);
}

#endif