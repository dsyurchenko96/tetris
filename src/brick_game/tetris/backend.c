#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define _POSIX_C_SOURCE 199309L
// #define _DEFAULT_SOURCE

#include "../../tetris.h"

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

void initGame() {
  Tetromino *tetromino = getTetromino();
  tetromino->next_type = generateRandomTetromino();

  GameState *gameState = getGameState();
  *gameState = Started;

  GameInfo_t *gameInfo = getGameInfo();
  gameInfo->level = START_LEVEL;
  gameInfo->score = 0;
  gameInfo->high_score = 0;
  gameInfo->pause = 0;
  gameInfo->speed = 0;

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

void processInput() {
  int c = getch();
  switch (c) {
    case KEY_UP:
      userInput(Up, false);
      break;

    case KEY_DOWN:
      userInput(Down, false);
      break;

    case KEY_LEFT:
      userInput(Left, false);
      break;

    case KEY_RIGHT:
      userInput(Right, false);
      break;

    case '\n':
      userInput(Start, false);
      break;

    case ' ':
      userInput(Action, true);
      break;

    case 'p':
      userInput(Pause, false);
      break;

    case 'q':
      userInput(Terminate, false);
      break;

    default:
      break;
  }
}

void userInput(UserAction_t action, __attribute__((unused)) bool hold) {
  GameInfo_t *gameInfo = getGameInfo();
  Tetromino *tetromino = getTetromino();
  GameState *gameState = getGameState();
  // int collision;
  switch (action) {
    case Left:
      if (!gameInfo->pause && *gameState >= Idle && !checkCollision(tetromino, -1, 0)) {
        moveTetromino(tetromino, -1, 0);
        *gameState = Shifting;
      }
      
      break;
    case Right:
      if (!gameInfo->pause && *gameState >= Idle && !checkCollision(tetromino, 1, 0)) {
        moveTetromino(tetromino, 1, 0);
        *gameState = Shifting;
      }
      
      break;
    case Down:
      if (!gameInfo->pause && *gameState >= Idle) {
        *gameState = checkFallingCollision(tetromino);
      }
      
      // collision = checkCollision(tetromino, 0, 1);
      // if (collision == NoCollision) {
      //   // moveTetromino(tetromino, 0, 1);
      //   *gameState = Falling;
      // } else if (collision == LockingCollision) {
      //   // clearTetromino(tetromino);
      //   // lockTetromino(tetromino);
      //   // clearGameInfoNextTetromino();
      //   // LineClearInfo lines = checkLineClear();
      //   // if (lines.num_cleared > 0) {
      //   //   clearLines(lines);
      //   // }
      //   // initTetromino(generateRandomTetromino());
      //   *gameState = Locking;
      // }
      break;
    case Up:
      break;
    case Start:
      if (*gameState == Started) {
        *gameState = Spawning;
      }
      
      break;
    case Action:
      // rotateTetromino(tetromino);
      if (*gameState >= Idle) {
        *gameState = Rotating;
      }
      break;
    case Pause:
      // gameInfo->pause = !gameInfo->pause;
      if (*gameState > Started) {
        *gameState = Paused;
      }
      
      break;
    case Terminate:
      *gameState = Terminated;
      break;
    default:
      // *gameState = Idle;
      break;
  }
}

GameInfo_t updateCurrentState() {
  GameInfo_t *gameInfo = getGameInfo();
  GameState *gameState = getGameState();
  Tetromino *tetromino = getTetromino();

  switch (*gameState) {
    case Idle:
      break;
    case Started:
      break;
    case Shifting:
      break;
    case Locking:
      clearTetromino(tetromino);
      lockTetromino(tetromino);
      clearGameInfoNextTetromino();
      LineClearInfo lines = checkLineClear();
      if (lines.num_cleared > 0) {
        clearLines(lines);
      }
      *gameState = Spawning;
      break;
    case Rotating:
      rotateTetromino(tetromino);
      *gameState = Idle;
      break;
    case Falling:
      moveTetromino(tetromino, 0, 1);
      *gameState = Idle;
      break;
    case Paused:
      gameInfo->pause = !gameInfo->pause;
      *gameState = Idle;
      break;
    case Spawning:
      if (initTetromino(generateRandomTetromino()) == HorizontalCollision) {
        *gameState = Terminated;
      } else {
        *gameState = Idle;
      }
      break;
    case Terminated:
      break;
    

    default:
      break;
  }

  return *gameInfo;
}

int checkCollision(Tetromino *tetromino, int x, int y) {
  GameInfo_t *gameInfo = getGameInfo();
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
      // gameInfo->field[next_y][next_x] == Locked
      collision = HorizontalCollision;

    } else if ((y && next_y >= FIELD_HEIGHT) ||
               (!x && y &&
                getByte(StateByte, gameInfo->field[next_y][next_x]) ==
                    Locked)) {
      // gameInfo->field[next_y][next_x] == Locked
      collision = LockingCollision;
    }
  }

  return collision;
}

GameState checkFallingCollision(Tetromino *tetromino) {
  GameState gameState = Falling;
  int collision = checkCollision(tetromino, 0, 1);
  if (collision == LockingCollision) {
    gameState = Locking;
  }
  return gameState;
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
  GameInfo_t *gameInfo = getGameInfo();
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

  updateScoreLevel(lines);
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
    gameInfo->level++;
  }
}
