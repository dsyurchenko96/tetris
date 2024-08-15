#include "../../inc/backend.h"
#include "../../inc/tetris.h"
#include "../../inc/tetromino.h"

void userInput(UserAction_t action, __attribute__((unused)) bool hold) {
  const GameInfo_t *gameInfo = getGameInfo();
  Tetromino *tetromino = getTetromino();
  GameState *gameState = getGameState();
  switch (action) {
    case Left:
      if (!gameInfo->pause && *gameState >= Idle &&
          !checkCollision(tetromino, -1, 0)) {
        moveTetromino(tetromino, -1, 0);
        *gameState = Shifting;
      }
      break;
    case Right:
      if (!gameInfo->pause && *gameState >= Idle &&
          !checkCollision(tetromino, 1, 0)) {
        moveTetromino(tetromino, 1, 0);
        *gameState = Shifting;
      }
      break;
    case Down:
      if (!gameInfo->pause && *gameState >= Idle) {
        *gameState = checkFallingCollision(tetromino);
      }
      break;
    case Up:
      break;
    case Start:
      if (*gameState == Started) {
        *gameState = Spawning;
      }
      break;
    case Action:
      if (!gameInfo->pause && *gameState >= Idle) {
        *gameState = Rotating;
      }
      break;
    case Pause:
      if (*gameState > Started) {
        *gameState = Paused;
      }
      break;
    case Terminate:
      *gameState = Terminated;
      break;
    default:
      break;
  }
}

GameInfo_t updateCurrentState() {
  GameInfo_t *gameInfo = getGameInfo();
  GameState *gameState = getGameState();
  Tetromino *tetromino = getTetromino();

  switch (*gameState) {
    case Locking:
      clearTetromino(tetromino);
      lockTetromino(tetromino);
      clearGameInfoNextTetromino();
      LineClearInfo lines = checkLineClear();
      if (lines.num_cleared > 0) {
        clearLines(lines);
        updateScoreLevel(lines);
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
    default:
      break;
  }
  gameInfo->speed = INITIAL_SPEED / gameInfo->level;
  return *gameInfo;
}

void updateFallTimer() {
  int *timer = getTimer();
  (*timer) += TICK;
  const GameInfo_t *gameInfo = getGameInfo();
  if (*timer >= gameInfo->speed) {
    GameState *gameState = getGameState();
    if (*gameState != Spawning) {
      const Tetromino *tetromino = getTetromino();
      *gameState = checkFallingCollision(tetromino);
    }
    *timer = 0;
  }
}