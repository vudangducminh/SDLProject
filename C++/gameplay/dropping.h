#ifndef DROPPING_H
#define DROPPING_H

#include<bits/stdc++.h>
#include "../input/input.h"
#include "board.h"
using namespace std;

bool dropping(int piece, int &x, int &y, int &h) {
    currentDroppingFrame++;
    if (currentDroppingFrame == cap) {
        currentDroppingFrame = 0;
        removePiece(piece, x, y, h);
        if (checkPiece(piece, x, y + 1, h)) {
            y++;
        }
        else {
            if (cap == MAX_DROP_DELAY) {
                currentDroppingFrame = 0;
                fillPiece(piece, x, y, h);
                return false;
            }
            if (isMoved) {
                currentDroppingFrame = cap;
                cap = MAX_DROP_DELAY;
                fillPiece(piece, x, y, h);
                return true;
            }
            fillPiece(piece, x, y, h);
            return false;
        }
    }
    else if (currentDroppingFrame > droppingSpeed) {
        if (currentDroppingFrame % droppingSpeed) return true;
        removePiece(piece, x, y, h);
        if (checkPiece(piece, x, y + 1, h)) {
            y++;
            cap = droppingSpeed;
            currentDroppingFrame = 0;
        }
        else {
            if (!isMoved) {
                fillPiece(piece, x, y, h);
                cap = droppingSpeed;
                currentDroppingFrame = 0;
                return false;
            }
        }
    }
    fillPiece(piece, x, y, h);
    return true;
}


#endif