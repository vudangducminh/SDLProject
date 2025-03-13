#ifndef CLEAR_LINES_H
#define CLEAR_LINES_H

#include<bits/stdc++.h>
#include "../layout/piece.h"
#include "board.h"
using namespace std;

int occupied[40];

int clearLines() {
    int lines = 0;
    for (int i = 0; i < ROW + 10; i++) occupied[i] = 0;
    for (int j = ROW + 9; j >= 0; j--) {
        for (int i = 0; i < COL; i++) {
            occupied[j] += isOccupied(i, j);
        }
        lines += (occupied[j] == COL);
    }
    for (int j = ROW + 9; j >= 0; j--) {
        if (occupied[j] && occupied[j] < COL) continue;
        for (int i = 0; i < COL; i++) state[i][j] = 0;
        occupied[j] = 0;
        for (int k = j - 1; k >= 0; k--) {
            if (!occupied[k] || occupied[k] == COL) continue;
            occupied[j] = occupied[k];
            occupied[k] = 0;
            for (int i = 0; i < COL; i++) {
                state[i][j] = state[i][k];
                state[i][k] = 0;
            }
            break;
        }
    }
    return lines;
}

#endif