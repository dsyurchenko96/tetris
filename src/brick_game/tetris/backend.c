#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define _POSIX_C_SOURCE 199309L
// #define _DEFAULT_SOURCE

#include "../../tetris.h"

GameInfo_t *getGameInfo() {
  static GameInfo_t gameState;
  return &gameState;
}

Tetromino *getTetromino() {
  static Tetromino tetromino;
  return &tetromino;
}

GameInfo_t updateCurrentState() {
  GameInfo_t *gameState = getGameInfo();
  // Tetromino *tetromino = getTetromino();

  return *gameState;
}

void initGame() {
  GameInfo_t *GameState = getGameInfo();
  GameState->level = START_LEVEL;
  GameState->score = 0;
  GameState->high_score = 0;
  GameState->pause = 0;
  GameState->speed = 0;

  GameState->next = NULL;
  GameState->field = calloc(FIELD_HEIGHT, sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    GameState->field[i] = calloc(FIELD_WIDTH, sizeof(int));
  }

  srandom(time(NULL));
}

void destroyGame() {
  GameInfo_t *GameState = getGameInfo();
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    free(GameState->field[i]);
  }
  free(GameState->field);
}

void processInput() {
  UserAction_t action;
  int c = getch();
  switch (c) {
    case KEY_UP:
      action = Up;
      break;

    case KEY_DOWN:
      action = Down;
      break;

    case KEY_LEFT:
      action = Left;
      break;

    case KEY_RIGHT:
      action = Right;
      break;

    case ' ':
      action = Action;
      break;

    case 'p':
      action = Pause;
      break;

    case 'q':
      action = Terminate;
      break;

    default:
      action = None;
      break;
  }
  userInput(action, false);
}

int checkCollision(Tetromino *tetromino, int x, int y) {
  GameInfo_t *GameState = getGameInfo();
  int collision = NoCollision;
  for (int coordinate = 0; collision == NoCollision && coordinate < NUM_BLOCKS;
       coordinate++) {
    int next_x = tetromino->x + x +
                 tetromino->coordinates[tetromino->state][coordinate].x;
    int next_y = tetromino->y + y +
                 tetromino->coordinates[tetromino->state][coordinate].y;

    if (next_x < 0 || next_x >= FIELD_WIDTH || next_y < 0 ||
        (!x && !y && (next_y >= FIELD_HEIGHT)) ||
        (!y &&
         getByte(StateByte, GameState->field[next_y][next_x]) == Locked)) {
      // GameState->field[next_y][next_x] == Locked
      collision = HorizontalCollision;

    } else if ((y && next_y >= FIELD_HEIGHT) ||
               (!x && y &&
                getByte(StateByte, GameState->field[next_y][next_x]) ==
                    Locked)) {
      // GameState->field[next_y][next_x] == Locked
      collision = LockingCollision;
    }
  }

  return collision;
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
  GameInfo_t *GameState = getGameInfo();
  LineClearInfo lines = initLineInfo();
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    lines.to_clear_current = true;
    for (int x = 0; lines.to_clear_current && x < FIELD_WIDTH; x++) {
      if (getByte(StateByte, GameState->field[y][x]) != Locked) {
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
  GameInfo_t *GameState = getGameInfo();
  for (int i = 0; i < lines.num_cleared; i++) {
    for (int y = lines.indeces[i]; y > 0; y--) {
      for (int x = 0; x < FIELD_WIDTH; x++) {
        if (getByte(StateByte, GameState->field[y - 1][x]) != Locked) {
          GameState->field[y][x] = GameState->field[y - 1][x];
        }
      }
    }
  }

  switch (lines.num_cleared) {
    case 1:
      GameState->score += 100;
      break;
    case 2:
      GameState->score += 300;
      break;
    case 3:
      GameState->score += 700;
      break;
    case 4:
      GameState->score += 1500;
      break;
    default:
      break;
  }

  if (GameState->level < 10 && GameState->level * 600 < GameState->score) {
    GameState->level++;
  }
}

void userInput(UserAction_t action, __attribute__((unused)) bool hold) {
  GameInfo_t *GameState = getGameInfo();
  Tetromino *tetromino = getTetromino();
  int collision;
  switch (action) {
    case Left:
      if (!checkCollision(tetromino, -1, 0)) {
        moveTetromino(tetromino, -1, 0);
      }
      break;
    case Right:
      if (!checkCollision(tetromino, 1, 0)) {
        moveTetromino(tetromino, 1, 0);
      }
      break;
    case Down:
      collision = checkCollision(tetromino, 0, 1);
      if (collision == NoCollision) {
        moveTetromino(tetromino, 0, 1);
      } else if (collision == LockingCollision) {
        clearTetromino(tetromino);
        lockTetromino(tetromino);
        LineClearInfo lines = checkLineClear();
        if (lines.num_cleared > 0) {
          clearLines(lines);
        }
        initTetromino();
      }
      break;
    case Up:
      if (!checkCollision(tetromino, 0, -1)) {
        moveTetromino(tetromino, 0, -1);
      }

      break;
    case Action:
      rotateTetromino(tetromino);
      break;
    case Pause:
      GameState->pause = !GameState->pause;
      break;
    case Terminate:
      GameState->terminate = true;
      break;
    case None:
      break;
    default:
      break;
  }
}
