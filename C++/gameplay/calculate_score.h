#ifndef CALCULATE_SCORE_H
#define CALCULATE_SCORE_H

#include<bits/stdc++.h>
#include "../const/data.h"
using namespace std;

int calculateScore(int lines) {
    int score = 0;
    double coefficient = pow(2, pow(currentLevel, 0.42)) - 1;
    if (lines == 0) {
        score = 0;
        return score;
    }
    if (lines == 1) {
        // If spin then increase the score (not implement yet)
        score += 40 * coefficient;
    }
    if (lines == 2) {
        // If spin then increase the score (not implement yet)
        score += 100 * coefficient;
    }
    if (lines == 3) {
        // If spin then increase the score (not implement yet)
        score += 170 * coefficient;
    }
    if (lines == 4) {
        // If spin then increase the score (not implement yet)
        score += 250 * coefficient;
    }
    return score;
}

#endif