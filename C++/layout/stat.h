#ifndef STAT_H
#define STAT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <bits/stdc++.h>
#include "../algorithm.h"
#include "../const/data.h"
#include "../const/UI.h"
#include "text.h"

using namespace std;

void renderLevel() {
    char* levelToText = "";
	int tmp = currentLevel;
	while (tmp) {
		char* ch = char_to_char_ptr((char) (tmp % 10 + 48));
		levelToText = concatenate_strings(ch, levelToText);
		tmp /= 10;
	}
	int len = strlen(levelToText);
	if (!len) {
		levelToText = "0";
		len = 1;
	}
    int x = boardCoordinateX - 100;
    int y = boardCoordinateY + ROW * BLOCK_SIZE - 255;
    Text* level = createText(renderer, x, y, 100, 30, "LEVEL", statTextColor, fontBold22);
	levelText = createText(renderer, x, y + 30, 80, 30, levelToText, statTextColor, fontBold28);
	renderTextCenter(renderer, level);
	renderTextRight(renderer, levelText);
	destroyText(level);
	destroyText(levelText);
}

void renderLinesCleared() {
    char* linesClearedToText = "";
	
	int linesNeed = linesPerLevel[currentLevel + levelOffset];
	while (linesNeed) {
		char* ch = char_to_char_ptr((char) (linesNeed % 10 + 48));
		linesClearedToText = concatenate_strings(ch, linesClearedToText);
		linesNeed /= 10;
	}

	linesClearedToText = concatenate_strings(" / ", linesClearedToText);

	int tmp = totalLinesCleared;
	if (!tmp) {
		linesClearedToText = concatenate_strings("0", linesClearedToText);
	} else {
		while (tmp) {
			char* ch = char_to_char_ptr((char) (tmp % 10 + 48));
			linesClearedToText = concatenate_strings(ch, linesClearedToText);
			tmp /= 10;
		}
	}

    int x = boardCoordinateX - 100;
    int y = boardCoordinateY + ROW * BLOCK_SIZE - 155;
    Text* lines = createText(renderer, x, y, 100, 30, "LINES", statTextColor, fontBold22);
	linesClearedText = createText(renderer, x, y + 30, 80, 30, linesClearedToText, statTextColor, fontBold28);
	renderTextCenter(renderer, lines);
	renderTextRight(renderer, linesClearedText);
	destroyText(lines);
	destroyText(linesClearedText);
}

void renderTime() {
	int sec = (curGameTime - startGameTime) / 1000;
	int min = sec / 60;
	sec %= 60;
    char* timeToText = "";
	bool isSecOneDigit = false;
	if (sec < 10) isSecOneDigit = true;
	if (sec == 0) {
		timeToText = concatenate_strings("00", timeToText);
	} else {
		while (sec) {
			char* ch = char_to_char_ptr((char) (sec % 10 + 48));
			timeToText = concatenate_strings(ch, timeToText);
			sec /= 10;
		}
		if (isSecOneDigit) timeToText = concatenate_strings(char_to_char_ptr('0'), timeToText);
	}
	timeToText = concatenate_strings(char_to_char_ptr(':'), timeToText);
	if (min == 0) {
		timeToText = concatenate_strings("0", timeToText);
	} else {
		while (min) {
			char* ch = char_to_char_ptr((char) (min % 10 + 48));
			timeToText = concatenate_strings(ch, timeToText);
			min /= 10;
		}
	}

	int x = boardCoordinateX - 100;
    int y = boardCoordinateY + ROW * BLOCK_SIZE - 55;
    Text* tm = createText(renderer, x, y, 100, 30, "TIME", statTextColor, fontBold22);
	timeText = createText(renderer, x, y + 30, 80, 30, timeToText, statTextColor, fontBold28);
	renderTextCenter(renderer, tm);
	renderTextRight(renderer, timeText);
	destroyText(tm);
	destroyText(timeText);
}

void renderScore() {
    char* scoreToText = "";
	int tmp = currentScore;
	while (tmp) {
		char* ch = char_to_char_ptr((char) (tmp % 10 + 48));
		scoreToText = concatenate_strings(ch, scoreToText);
		tmp /= 10;
	}
	int len = strlen(scoreToText);
	if (!len) {
		scoreToText = "0";
		len = 1;
	}
	scoreToText = concatenate_strings("SCORE: ", scoreToText);
    int x = (MAX_SCREEN_WIDTH - 240) / 2;
    int y = boardCoordinateY + ROW * BLOCK_SIZE;
	scoreText = createText(renderer, x, y, 240, 40, scoreToText, statTextColor, fontBold22);
	renderTextCenter(renderer, scoreText);
	destroyText(scoreText);
}

void renderGameOver() {
	if (!gameOver) return;
	gameOverText = createText(renderer, 0, 0, MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGHT, "GAME OVER", gameOverTextColor, fontBold120);
	renderTextCenter(renderer, gameOverText);
	destroyText(gameOverText);
}

#endif
