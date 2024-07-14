#include <stdlib.h>

#include "../../tetris.h"

void clearTetromino(Tetromino *tetromino) {
  GameInfo_t *GameState = getGameInfo();
  for (int coordinate = 0; coordinate < NUM_BLOCKS; coordinate++) {
    GameState->field
        [tetromino->y +
         COORDINATES[tetromino->type][tetromino->previous_state][coordinate].y]
        [tetromino->x +
         COORDINATES[tetromino->type][tetromino->previous_state][coordinate]
             .x] = Empty;
    // GameState->field[tetromino->y +
    //                  tetromino->coordinates[tetromino->previous_state][coordinate].y]
    //                 [tetromino->x +
    //                  tetromino->coordinates[tetromino->previous_state][coordinate].x]
    //                  =
    //     Empty;
  }
}

void lockTetromino(Tetromino *tetromino) {
  GameInfo_t *GameState = getGameInfo();
  for (int coordinate = 0; coordinate < NUM_BLOCKS; coordinate++) {
    setCellInfo(
        &GameState->field
             [tetromino->y +
              COORDINATES[tetromino->type][tetromino->state][coordinate].y]
             [tetromino->x +
              COORDINATES[tetromino->type][tetromino->state][coordinate].x],
        Locked, tetromino->color);
    // setCellInfo(tetromino->x +
    // tetromino->coordinates[tetromino->state][coordinate].x,
    //               tetromino->y +
    //               tetromino->coordinates[tetromino->state][coordinate].y,
    //               Locked, tetromino->color);
    // GameState->field[tetromino->y +
    //                  tetromino->coordinates[tetromino->state][coordinate].y]
    //                 [tetromino->x +
    //                  tetromino->coordinates[tetromino->state][coordinate].x]
    //                  =
    //     Locked;
  }
}

int initTetromino(TetrominoType next_type) {
  Tetromino *tetromino = getTetromino();
  tetromino->x = SPAWN_X;
  tetromino->y = SPAWN_Y;
  tetromino->previous_state = 0;
  tetromino->state = 0;

  if (next_type == INIT) {
    tetromino->type = generateRandomTetromino();
    tetromino->next_type = generateRandomTetromino();
  } else {
    tetromino->type = tetromino->next_type;
    tetromino->next_type = next_type;
  }
  // tetromino->type = type;
  tetromino->color = TETROMINO_COLORS[tetromino->type + 1];
  tetromino->number_of_states = STATES_COUNT[tetromino->type];

  // for (int state = 0; state < tetromino->number_of_states; state++) {
  //   for (int coordinate = 0; coordinate < 4; coordinate++) {
  //     tetromino->coordinates[state][coordinate] =
  //         COORDINATES[tetromino->type][state][coordinate];
  //   }
  // }

  setGameInfoNextTetromino(tetromino);
  return spawnTetromino(tetromino);
}

void setGameInfoNextTetromino(Tetromino *tetromino) {
  GameInfo_t *GameState = getGameInfo();

  for (int coordinate = 0; coordinate < NUM_BLOCKS; coordinate++) {
    setCellInfo(
        &GameState->next[COORDINATES[tetromino->next_type][0][coordinate].y + 2]
                        [COORDINATES[tetromino->next_type][0][coordinate].x] +
            2,
        Locked, TETROMINO_COLORS[tetromino->next_type + 1]);
  }
  // GameState->next = calloc(NUM_BLOCKS, sizeof(int*));

  // for (int i = 0; i < NUM_BLOCKS; i++) {
  //   GameState->next[i] = calloc(NUM_BLOCKS, sizeof(int));
  // }
}

void clearGameInfoNextTetromino() {
  GameInfo_t *GameState = getGameInfo();
  for (int i = 0; i < NUM_BLOCKS; i++) {
    for (int j = 0; j < NUM_BLOCKS; j++) {
      GameState->next[i][j] = 0;
    }
  }
}

TetrominoType generateRandomTetromino() {
  TetrominoType tetrominoArray[] = {O, I, S, Z, L, J, T};
  int index = (int)((double)random() / ((double)RAND_MAX + 1) * NUM_TETROMINOS);
  return tetrominoArray[index];
}

int spawnTetromino(Tetromino *tetromino) {
  int collision = checkCollision(tetromino, 0, 0);
  if (collision == NoCollision) {
    // put tetromino into the game field
    GameInfo_t *GameState = getGameInfo();
    for (int coordinate = 0; coordinate < 4; coordinate++) {
      setCellInfo(
          &GameState->field
               [tetromino->y +
                COORDINATES[tetromino->type][tetromino->state][coordinate].y]
               [tetromino->x +
                COORDINATES[tetromino->type][tetromino->state][coordinate].x],
          Moving, tetromino->color);
      // setCellInfo(tetromino->x +
      // tetromino->coordinates[tetromino->state][i].x,
      //             tetromino->y +
      //             tetromino->coordinates[tetromino->state][i].y, Moving,
      //             tetromino->color);
      // GameState
      //     ->field[tetromino->y +
      //     tetromino->coordinates[tetromino->state][i].y]
      //            [tetromino->x +
      //             tetromino->coordinates[tetromino->state][i].x] = Moving;
    }
  }

  return collision;
}

void moveTetromino(Tetromino *tetromino, int x, int y) {
  clearTetromino(tetromino);

  tetromino->x += x;
  tetromino->y += y;

  GameInfo_t *GameState = getGameInfo();
  for (int coordinate = 0; coordinate < 4; coordinate++) {
    setCellInfo(
        &GameState->field
             [tetromino->y +
              COORDINATES[tetromino->type][tetromino->state][coordinate].y]
             [tetromino->x +
              COORDINATES[tetromino->type][tetromino->state][coordinate].x],
        Moving, tetromino->color);
    // setCellInfo(tetromino->x + tetromino->coordinates[tetromino->state][i].x,
    //               tetromino->y +
    //               tetromino->coordinates[tetromino->state][i].y, Moving,
    //               tetromino->color);
    // GameState
    //     ->field[tetromino->y + tetromino->coordinates[tetromino->state][i].y]
    //            [tetromino->x + tetromino->coordinates[tetromino->state][i].x]
    //            =
    //     Moving;
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