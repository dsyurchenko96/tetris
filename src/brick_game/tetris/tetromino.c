#include "../../inc/tetromino.h"

#include <stdlib.h>

#include "../../inc/backend.h"
#include "../../inc/tetris.h"

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

  tetromino->type = tetromino->next_type;
  tetromino->next_type = next_type;

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
                       [COORDINATES[tetromino->next_type][0][coordinate].x + 2],
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
  tetromino->previous_state = tetromino->state;
  tetromino->state = (tetromino->state + 1) % tetromino->number_of_states;
  if (checkCollision(tetromino, 0, 0) != NoCollision) {
    tetromino->state = tetromino->previous_state;
  } else {
    moveTetromino(tetromino, 0, 0);
    tetromino->previous_state = tetromino->state;
  }
}

int checkCollision(const Tetromino *tetromino, int x, int y) {
  const GameInfo_t *gameInfo = getGameInfo();
  int collision = NoCollision;
  for (int coordinate = 0; collision == NoCollision && coordinate < NUM_BLOCKS;
       coordinate++) {
    int next_x = tetromino->x + x +
                 COORDINATES[tetromino->type][tetromino->state][coordinate].x;
    int next_y = tetromino->y + y +
                 COORDINATES[tetromino->type][tetromino->state][coordinate].y;

    if (next_x < 0 || next_x >= FIELD_WIDTH || next_y < 0 ||
        (!x && !y && (next_y >= FIELD_HEIGHT)) ||
        (!y && getByte(StateByte, gameInfo->field[next_y][next_x]) == Locked)) {
      collision = HorizontalCollision;

    } else if ((y && next_y >= FIELD_HEIGHT) ||
               (!x && y &&
                getByte(StateByte, gameInfo->field[next_y][next_x]) ==
                    Locked)) {
      collision = LockingCollision;
    }
  }

  return collision;
}

GameState checkFallingCollision(const Tetromino *tetromino) {
  GameState gameState = Falling;
  int collision = checkCollision(tetromino, 0, 1);
  if (collision == LockingCollision) {
    gameState = Locking;
  }
  return gameState;
}