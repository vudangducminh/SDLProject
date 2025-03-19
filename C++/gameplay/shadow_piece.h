#ifndef SHADOW_PIECE_H
#define SHADOW_PIECE_H

#include<bits/stdc++.h>
#include "../layout/piece.h"
using namespace std;

int currentShadowRow = -1;
void updateShadowPiece(int piece, int &x, int &y, int &d) {
    int cnt = 0;
    for (int j = y; j < ROW; j++) {
        // if (cnt == 4) break;
        for (int i = 0; i < COL; i++) {
            // if (cnt == 4) break;
            if (state[i][j + 10] == SHADOW_PIECE) {
                state[i][j + 10] = 0;
                cnt++;
            }
        }
    }
    removePiece(piece, x, y, d);
    int id = y;
    for (int j = id + 1; j < ROW; j++) {
        if (checkPiece(piece, x, j, d)) id = j;
        else break;
    }
    fillShadowPiece(piece, x, id, d);
    fillPiece(piece, x, y, d);
    currentShadowRow = id;
}

#endif