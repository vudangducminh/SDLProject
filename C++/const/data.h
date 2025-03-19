#ifndef DATA_H
#define DATA_H

#include<bits/stdc++.h>
#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>

using namespace std;
mt19937_64 rng;

// Piece color
struct rgba {
    int r;
    int g;
    int b;
    int a;
};
rgba COLOR[1 << 20];

// Selected & deselected color
SDL_Color DESELECTED_COLOR = {255, 0, 0, 255};
SDL_Color SELECTED_COLOR = {0, 255, 0, 255};

// Default board size
int ROW = 20;
int COL = 10;
int QUEUE_SIZE = 5;

// Settings
const int FPS = 60;
const int MAX_SCREEN_WIDTH = 1440;
const int MAX_SCREEN_HEIGHT = 864;
const float BLOCK_SIZE = 36;
const float MINI_BLOCK_SIZE = 30;
const int MAX_ROW = 20;
const int MAX_COL = 10;
const int DEGREE_0 = 0;
const int DEGREE_90 = 1;
const int DEGREE_180 = 2;
const int DEGREE_270 = 3;
const int SHADOW_PIECE = (1 << 20) - 1;
const int PIECE_T = 7;
const int PIECE_I = 6;
const int PIECE_O = 5;
const int PIECE_Z = 4;
const int PIECE_S = 3;
const int PIECE_L = 2;
const int PIECE_J = 1;
const int DEFAULT_MAX_DROP_DELAY = FPS * 5;
const int MOVING_DETECTION_BY_FRAME = FPS / 2;
const int DEFAULT_DROPPING_SPEED = FPS;

// Wall Kick Data
const pair<int, int> wallKickOthers[][5] = {
    {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}, 
    {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
    {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
    {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},
    {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
    {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
    {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
    {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}}
}, wallKickI[][5] = {
    {{1, 0}, {-1, 0}, {2, 0}, {-1, 1}, {2, -2}},
    {{-1, 0}, {-1, 0}, {-2, 0}, {1, -1}, {-2, 2}},
    {{0, 1}, {-1, 1}, {2, 1}, {-1, -1}, {2, 2}},
    {{0, -1}, {1, -1}, {-2, -1}, {1, 1}, {-2, -2}},
    {{-1, 0}, {1, 0}, {-2, 0}, {1, -1}, {-2, 2}},
    {{1, 0}, {-1, 0}, {2, 0}, {-1, 1}, {2, -2}},
    {{0, -1}, {1, -1}, {-2, -1}, {1, 1}, {-2, -2}},
    {{0, 1}, {-1, 1}, {2, 1}, {-1, -1}, {2, 2}}
};


// Inputs
const int moveLeftKey = SDL_SCANCODE_COMMA;
const int moveRightKey = SDL_SCANCODE_SLASH;
const int rotateClockwiseKey = SDL_SCANCODE_X;
const int rotateCounterClockwiseKey = SDL_SCANCODE_Z;
const int rotate_180_key = SDL_SCANCODE_A;
const int holdPieceKey = SDL_SCANCODE_C;
const int softDropKey = SDL_SCANCODE_PERIOD;
const int hardDropKey = SDL_SCANCODE_SPACE;

// Mods
const int CLASSIC_MODE = 1;
const int CHAOS_MODE = 2;
const int HIDDEN_MODE = 4;
const int HARD_ROCK_MODE = 8;
const int DOUBLE_TIME_MODE = 16;

int droppingSpeed[31], maxDropDelay[31];

void initializeDroppingSpeed() {
    droppingSpeed[0] = DEFAULT_DROPPING_SPEED + 1;
    maxDropDelay[0] = DEFAULT_DROPPING_SPEED + 1;
    for (int i = 1; i <= 5; i++) droppingSpeed[i] = droppingSpeed[i - 1] - 3;
    for (int i = 6; i <= 25; i++) droppingSpeed[i] = droppingSpeed[i - 1] - 2;
    for (int i = 26; i <= 30; i++) droppingSpeed[i] = droppingSpeed[i - 1] - 1;
    for (int i = 1; i <= 30; i++) maxDropDelay[i] = max(FPS, min(droppingSpeed[i] * 30, DEFAULT_MAX_DROP_DELAY));
}
// Game state
int state[40][40];
int gameMode = 0;
float boardCoordinateX, boardCoordinateY;
bool gameOver = false;
int currentLeftFrame = 0, currentRightFrame = 0, currentClockwiseFrame = 0, currentCounterClockwiseFrame = 0, currentRotate180Frame = 0;
int currentDroppingFrame = 0, cap = DEFAULT_MAX_DROP_DELAY;
int isMoved = MOVING_DETECTION_BY_FRAME;
int spawnTime = FPS / 10;
int holdingPiece = 0;
int numberOfPiece = 0, maxPieceID = 0;
int totalLinesCleared = 0, linesCleared = 0;
int currentScore = 0, currentLevel = 1;
bool isHardDropping = false, firstLeftMovement = false, firstRightMovement = false, isHoldingPieceAccessible = true, isInitialized = false, isPlaying = false;
double curGameTime = 0, startGameTime = 0;
#endif
