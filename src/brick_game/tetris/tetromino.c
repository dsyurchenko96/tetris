#include <stdlib.h>

#include "../../tetris.h"

void clearTetromino(const Tetromino *tetromino) {
  GameInfo_t *gameInfo = getGameInfo();
  for (int coordinate = 0; coordinate < NUM_BLOCKS; coordinate++) {
    gameInfo->field
        [tetromino->y +
         COORDINATES[tetromino->type][tetromino->previous_state][coordinate].y]
        [tetromino->x +
         COORDINATES[tetromino->type][tetromino->previous_state][coordinate]
             .x] = Empty;
  }
}

void lockTetromino(Tetromino *tetromino) {
  GameInfo_t *gameInfo = getGameInfo();
  for (int coordinate = 0; coordinate < NUM_BLOCKS; coordinate++) {
    setCellInfo(
        &gameInfo->field
             [tetromino->y +
              COORDINATES[tetromino->type][tetromino->state][coordinate].y]
             [tetromino->x +
              COORDINATES[tetromino->type][tetromino->state][coordinate].x],
        Locked, tetromino->color);
  }
}

int initTetromino(TetrominoType next_type) {
  Tetromino *tetromino = getTetromino();
  tetromino->x = SPAWN_X;
  tetromino->y = SPAWN_Y;
  tetromino->previous_state = 0;
  tetromino->state = 0;

  // if (next_type == INIT) {
  //   tetromino->type = generateRandomTetromino();
  //   tetromino->next_type = generateRandomTetromino();
  // } else {
  tetromino->type = tetromino->next_type;
  tetromino->next_type = next_type;
  // }
  tetromino->color = TETROMINO_COLORS[tetromino->type + 1];
  tetromino->number_of_states = STATES_COUNT[tetromino->type];

  setGameInfoNextTetromino(tetromino);
  return spawnTetromino(tetromino);
}

void setGameInfoNextTetromino(Tetromino *tetromino) {
  GameInfo_t *gameInfo = getGameInfo();

  for (int coordinate = 0; coordinate < NUM_BLOCKS; coordinate++) {
    setCellInfo(
        &gameInfo->next[COORDINATES[tetromino->next_type][0][coordinate].y + 2]
                       [COORDINATES[tetromino->next_type][0][coordinate].x] +
            2,
        Locked, TETROMINO_COLORS[tetromino->next_type + 1]);
  }
}

void clearGameInfoNextTetromino() {
  GameInfo_t *gameInfo = getGameInfo();
  for (int i = 0; i < NUM_BLOCKS; i++) {
    for (int j = 0; j < NUM_BLOCKS; j++) {
      gameInfo->next[i][j] = 0;
    }
  }
}

TetrominoType generateRandomTetromino() {
  const TetrominoType tetrominoArray[] = {O, I, S, Z, L, J, T};
  int index = (int)((double)random() / ((double)RAND_MAX + 1) * NUM_TETROMINOS);
  return tetrominoArray[index];
}

int spawnTetromino(Tetromino *tetromino) {
  int collision = checkCollision(tetromino, 0, 0);
  if (collision == NoCollision) {
    GameInfo_t *gameInfo = getGameInfo();
    for (int coordinate = 0; coordinate < 4; coordinate++) {
      setCellInfo(
          &gameInfo->field
               [tetromino->y +
                COORDINATES[tetromino->type][tetromino->state][coordinate].y]
               [tetromino->x +
                COORDINATES[tetromino->type][tetromino->state][coordinate].x],
          Moving, tetromino->color);
    }
  }

  return collision;
}

void moveTetromino(Tetromino *tetromino, int x, int y) {
  clearTetromino(tetromino);

  tetromino->x += x;
  tetromino->y += y;

  GameInfo_t *gameInfo = getGameInfo();
  for (int coordinate = 0; coordinate < 4; coordinate++) {
    setCellInfo(
        &gameInfo->field
             [tetromino->y +
              COORDINATES[tetromino->type][tetromino->state][coordinate].y]
             [tetromino->x +
              COORDINATES[tetromino->type][tetromino->state][coordinate].x],
        Moving, tetromino->color);
  }
}

void rotateTetromino(Tetromino *tetromino) {
  // int og_state = tetromino->state;
  // int collision = HorizontalCollision;
  // for (int i = 0; collision != NoCollision && i < tetromino->number_of_states
  // + 1; i++) {
  //   tetromino->previous_state = tetromino->state;
  //   tetromino->state = (tetromino->state + i + 1) %
  //   tetromino->number_of_states; collision = checkCollision(tetromino, 0, 0);
  // }

  // if (collision == NoCollision) {
  //   moveTetromino(tetromino, 0, 0);
  //   tetromino->previous_state = tetromino->state;
  // }

  tetromino->previous_state = tetromino->state;
  tetromino->state = (tetromino->state + 1) % tetromino->number_of_states;
  if (checkCollision(tetromino, 0, 0) != NoCollision) {
    tetromino->state = tetromino->previous_state;
  } else {
    moveTetromino(tetromino, 0, 0);
    tetromino->previous_state = tetromino->state;
  }
}

void setByte(int value, int index, int *num) { *num |= value << (index * 8); }

int getByte(int index, int num) { return (num >> (index * 8)) & 0xFF; }

void setCellInfo(int *cell, int state, int color) {
  setByte(state, StateByte, cell);
  setByte(color, ColorByte, cell);
}