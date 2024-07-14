#include <ncurses.h>

#include "tetris.h"

int main() {
  initCurses();
  initGame();
  GameInfo_t *gameState = getGameInfo();
  initTetromino(INIT);

  int fall_count = 0;
  while (gameState->terminate == false) {
    gameState->speed = INITIAL_SPEED / gameState->level;
    if (fall_count >= gameState->speed) {
      Tetromino *tetromino = getTetromino();
      int collision = checkCollision(tetromino, 0, 1);
      if (collision == NoCollision) {
        moveTetromino(tetromino, 0, 1);
      } else if (collision == LockingCollision) {
        clearTetromino(tetromino);
        lockTetromino(tetromino);
        LineClearInfo lines = checkLineClear();
        if (lines.num_cleared > 0) {
          clearLines(lines);
        }
        clearGameInfoNextTetromino();
        if (initTetromino(generateRandomTetromino()) == HorizontalCollision) {
          gameState->terminate = true;
        }
      }
      fall_count = 0;
    }
    processInput();
    // flushinp();
    updateCurrentState();
    printField();
    napms(TICK);
    fall_count += TICK;
  }
  destroyGame();
  endwin();
}