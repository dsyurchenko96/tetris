#include "../../inc/backend.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../inc/tetris.h"
#include "../../inc/tetromino.h"

GameInfo_t *getGameInfo() {
  static GameInfo_t gameInfo;
  return &gameInfo;
}

GameState *getGameState() {
  static GameState gameState;
  return &gameState;
}

Tetromino *getTetromino() {
  static Tetromino tetromino;
  return &tetromino;
}

int *getTimer() {
  static int timer;
  return &timer;
}

void initGame() {
  Tetromino *tetromino = getTetromino();
  tetromino->next_type = generateRandomTetromino();

  GameState *gameState = getGameState();
  *gameState = Started;

  int *timer = getTimer();
  *timer = 0;

  GameInfo_t *gameInfo = getGameInfo();
  gameInfo->level = START_LEVEL;
  gameInfo->score = 0;
  gameInfo->high_score = 0;
  gameInfo->pause = 0;
  gameInfo->speed = INITIAL_SPEED / gameInfo->level;

  gameInfo->field = calloc(FIELD_HEIGHT, sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    gameInfo->field[i] = calloc(FIELD_WIDTH, sizeof(int));
  }

  gameInfo->next = calloc(NUM_BLOCKS, sizeof(int *));
  for (int i = 0; i < NUM_BLOCKS; i++) {
    gameInfo->next[i] = calloc(NUM_BLOCKS, sizeof(int));
  }
  srandom(time(NULL));
}

void destroyGame() {
  GameInfo_t *gameInfo = getGameInfo();

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    free(gameInfo->field[i]);
  }
  free(gameInfo->field);

  for (int i = 0; i < NUM_BLOCKS; i++) {
    free(gameInfo->next[i]);
  }
  free(gameInfo->next);
}

LineClearInfo initLineInfo(void) {
  LineClearInfo lines;
  lines.indeces[0] = 0;
  lines.indeces[1] = 0;
  lines.indeces[2] = 0;
  lines.indeces[3] = 0;
  lines.num_cleared = 0;
  lines.to_clear_current = true;
  return lines;
}

LineClearInfo checkLineClear(void) {
  const GameInfo_t *gameInfo = getGameInfo();
  LineClearInfo lines = initLineInfo();
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    lines.to_clear_current = true;
    for (int x = 0; lines.to_clear_current && x < FIELD_WIDTH; x++) {
      if (getByte(StateByte, gameInfo->field[y][x]) != Locked) {
        lines.to_clear_current = false;
      }
    }
    if (lines.to_clear_current) {
      lines.indeces[lines.num_cleared] = y;
      lines.num_cleared++;
    }
  }
  return lines;
}

void clearLines(LineClearInfo lines) {
  GameInfo_t *gameInfo = getGameInfo();
  for (int i = 0; i < lines.num_cleared; i++) {
    for (int y = lines.indeces[i]; y > 0; y--) {
      for (int x = 0; x < FIELD_WIDTH; x++) {
        if (getByte(StateByte, gameInfo->field[y - 1][x]) != Locked) {
          gameInfo->field[y][x] = gameInfo->field[y - 1][x];
        }
      }
    }
  }
}

void updateScoreLevel(LineClearInfo lines) {
  GameInfo_t *gameInfo = getGameInfo();
  switch (lines.num_cleared) {
    case 1:
      gameInfo->score += 100;
      break;
    case 2:
      gameInfo->score += 300;
      break;
    case 3:
      gameInfo->score += 700;
      break;
    case 4:
      gameInfo->score += 1500;
      break;
    default:
      break;
  }

  if (gameInfo->score > gameInfo->high_score) {
    gameInfo->high_score = gameInfo->score;
  }

  if (gameInfo->level < 10 && gameInfo->level * 600 < gameInfo->score) {
    gameInfo->level = gameInfo->score / 600 + 1;
  }
}

int readHighScore(void) {
  int high_score = 0;
  FILE *f = fopen(HIGH_SCORE_FILE, "r");
  if (f != NULL) {
    fscanf(f, "%d", &high_score);
    fclose(f);
  }

  return high_score;
}

void writeHighScore() {
  int high_score = getGameInfo()->high_score;
  FILE *f = fopen(HIGH_SCORE_FILE, "w");
  if (f != NULL) {
    fprintf(f, "%d", high_score);
    fclose(f);
  }
}

void setByte(int value, int index, int *num) { *num |= value << (index * 8); }

int getByte(int index, int num) { return (num >> (index * 8)) & 0xFF; }

void setCellInfo(int *cell, int state, int color) {
  setByte(state, StateByte, cell);
  setByte(color, ColorByte, cell);
}