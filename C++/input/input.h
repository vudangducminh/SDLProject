#ifndef INPUT_H
#define INPUT_H

#include<bits/stdc++.h>
#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include "../const/data.h"
#include "../layout/piece.h"
#include "../gameplay/board.h"
#include "../gameplay/shadow_piece.h"
#include "../gameplay/queue.h"
#define fi first
#define se second
using namespace std;

void keyboardStateUpdate() {
    if (spawnTime) spawnTime--;
    if (isMoved) isMoved--;
    if (currentLeftFrame) currentLeftFrame--;
    if (currentRightFrame) currentRightFrame--;
    const _Bool *keyboardStateUpdate = SDL_GetKeyboardState(NULL);

    if (keyboardStateUpdate[retryKey]) {
        if (!currentRetryFrame && isPlaying) {
            resetAllGameState();
            currentRetryFrame = 1;
        }
    } 
    else currentRetryFrame = 0;

    if (keyboardStateUpdate[escapeKey]) {
        if (!currentEscapeFrame && isPlaying) {
            resetAll();
            currentEscapeFrame = 1;
        }
    } 
    else currentEscapeFrame = 0;

    if (gameOver) {
        return;
    }

    if (keyboardStateUpdate[moveLeftKey]) {
        isMoved = MOVING_DETECTION_BY_FRAME;
        if (!currentLeftFrame) {
            if (!firstLeftMovement) {
                currentLeftFrame = FPS / 8;
                firstLeftMovement = true;
            }
            else currentLeftFrame = MOVING_SPEED;
            removePiece(currentPiece, currentX, currentY, currentD);
            if (checkPiece(currentPiece, currentX - 1, currentY, currentD)) {
                currentX--;
            }
            fillPiece(currentPiece, currentX, currentY, currentD);
        }
    }
    else currentLeftFrame = 0, firstLeftMovement = false;

    if (keyboardStateUpdate[moveRightKey]) {
        isMoved = MOVING_DETECTION_BY_FRAME;
        if (!currentRightFrame)  {
            if (!firstRightMovement) {
                currentRightFrame = FPS / 8;   
                firstRightMovement = true;
            }
            else currentRightFrame = MOVING_SPEED;
            removePiece(currentPiece, currentX, currentY, currentD);
            if (checkPiece(currentPiece, currentX + 1, currentY, currentD)) {
                currentX++;
            }
            fillPiece(currentPiece, currentX, currentY, currentD);
        }
    }
    else currentRightFrame = 0, firstRightMovement = false;

    if (keyboardStateUpdate[rotateClockwiseKey]) {
        isMoved = MOVING_DETECTION_BY_FRAME;
        if (!currentClockwiseFrame) {
            removePiece(currentPiece, currentX, currentY, currentD);
            int id = -1;
            if (!currentD) id = 0;
            else if (currentD == 1) id = 2;
            else if (currentD == 2) id = 4;
            else id = 6; 
            if (currentPiece == PIECE_I) {
                for (int i = 0; i < 5; i++) {
                    if (checkPiece(currentPiece, currentX + wallKickI[id][i].fi, currentY + wallKickI[id][i].se, (currentD + 1) % 4)) {
                        currentD = (currentD + 1) % 4;
                        currentX += wallKickI[id][i].fi;
                        currentY += wallKickI[id][i].se;
                        currentClockwiseFrame = 1;
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < 5; i++) {
                    if (checkPiece(currentPiece, currentX + wallKickOthers[id][i].fi, currentY + wallKickOthers[id][i].se, (currentD + 1) % 4)) {
                        currentD = (currentD + 1) % 4;
                        currentX += wallKickOthers[id][i].fi;
                        currentY += wallKickOthers[id][i].se;
                        currentClockwiseFrame = 1;
                        break;
                    }
                }
            }
            fillPiece(currentPiece, currentX, currentY, currentD);
        }
    }
    else currentClockwiseFrame = 0;

    if (keyboardStateUpdate[rotateCounterClockwiseKey]) {
        isMoved = MOVING_DETECTION_BY_FRAME;
        if (!currentCounterClockwiseFrame) {
            removePiece(currentPiece, currentX, currentY, currentD);
            int id = -1;
            if (!currentD) id = 7;
            else if (currentD == 1) id = 1;
            else if (currentD == 2) id = 3;
            else id = 5; 
            
            if (currentPiece == PIECE_I) {
                for (int i = 0; i < 5; i++) {
                    if (checkPiece(currentPiece, currentX + wallKickI[id][i].fi, currentY + wallKickI[id][i].se, (currentD + 3) % 4)) {
                        currentD = (currentD + 3) % 4;
                        currentX += wallKickI[id][i].fi;
                        currentY += wallKickI[id][i].se;
                        currentCounterClockwiseFrame = 1;
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < 5; i++) {
                    if (checkPiece(currentPiece, currentX + wallKickOthers[id][i].fi, currentY + wallKickOthers[id][i].se, (currentD + 3) % 4)) {
                        currentD = (currentD + 3) % 4;
                        currentX += wallKickOthers[id][i].fi;
                        currentY += wallKickOthers[id][i].se;
                        currentCounterClockwiseFrame = 1;
                        break;
                    }
                }
            }
            fillPiece(currentPiece, currentX, currentY, currentD);
        }
    }
    else currentCounterClockwiseFrame = 0;
    if (keyboardStateUpdate[rotate_180_key]) {
        isMoved = MOVING_DETECTION_BY_FRAME;
        if (!currentRotate180Frame) {
            removePiece(currentPiece, currentX, currentY, currentD);
            if (checkPiece(currentPiece, currentX, currentY, (currentD + 2) % 4)) {
                currentD = (currentD + 2) % 4;
                currentRotate180Frame = 1;
            }
            fillPiece(currentPiece, currentX, currentY, currentD);
        }
    }
    else currentRotate180Frame = 0;
    if (keyboardStateUpdate[softDropKey]) {
        if (!spawnTime) {
            isMoved = MOVING_DETECTION_BY_FRAME;
            updateShadowPiece(currentPiece, currentX, currentY, currentD);
            removePiece(currentPiece, currentX, currentY, currentD);
            currentY = currentShadowRow;
            fillPiece(currentPiece, currentX, currentY, currentD);
        }
    }

    if (keyboardStateUpdate[hardDropKey]) {
        if (!spawnTime && !isHardDropping) {
            isHardDropping = true;
            updateShadowPiece(currentPiece, currentX, currentY, currentD);
            removePiece(currentPiece, currentX, currentY, currentD);
            currentY = currentShadowRow;
            fillPiece(currentPiece, currentX, currentY, currentD);
            cap = maxDropDelay[currentLevel];
            currentDroppingFrame = cap - 1;
        }
    }
    else isHardDropping = false;

    if (keyboardStateUpdate[holdPieceKey] && !(gameMode & CLASSIC_MODE)) {
        if (isHoldingPieceAccessible) {
            isHoldingPieceAccessible = false;
            removePiece(currentPiece, currentX, currentY, currentD);
            currentX = 4, currentY = -1, currentD = 0; 
            isMoved = MOVING_DETECTION_BY_FRAME; spawnTime = FPS / 10;
            if (!holdingPiece) {
                holdingPiece = currentPiece;
                currentPiece = currentQueue.front(); currentQueue.pop_front();
            }
            else swap(holdingPiece, currentPiece);

            if (!checkPiece(currentPiece, currentX, currentY, currentD)) {
                gameOver = true;
                return;
            }
            fillPiece(currentPiece, currentX, currentY, currentD);
            currentShadowRow = -1;
        }
    }
    updateShadowPiece(currentPiece, currentX, currentY, currentD);
}

#endif