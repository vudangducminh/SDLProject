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
        for (int i = max(0, x - 3); i < min(COL, x + 4); i++) {
            // if (cnt == 4) break;
            if (state[i][j + 10] == 8) {
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