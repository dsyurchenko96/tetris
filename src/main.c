#include <ncurses.h>

#include "tetris.h"

int main() {
  // GameInfo_t *gameInfo = getGameInfo();
  GameState *gameState = getGameState();
  Tetromino *tetromino = getTetromino();
  tetromino->next_type = generateRandomTetromino();

  initCurses();
  initGame();
  // initTetromino(INIT);

  printStartingScreen();

  int tick_count = 0;

  while (*gameState != Terminated) {
    processInput();
    
    gameState = getGameState();
    mvprintw(0, 0, "gameState: %d", *gameState);
    refresh();
    if (*gameState > Started) {
      printField();
      GameInfo_t gameInfo = updateCurrentState();
      if (!gameInfo.pause) {
        gameInfo.speed = INITIAL_SPEED / gameInfo.level;
        if (tick_count >= gameInfo.speed) {
          Tetromino *tetromino = getTetromino();
          *gameState = checkFallingCollision(tetromino);
          tick_count = 0;
        }
        if (*gameState > Idle) {
          printField();
        }
        
        tick_count += TICK;
      }
      
    }
    napms(TICK);
  } 
  // while (*gameState != Terminated) {
  //   gameState = getGameState();
  //   gameInfo->speed = INITIAL_SPEED / gameInfo->level;
  //   if (fall_count >= gameInfo->speed) {
  //     Tetromino *tetromino = getTetromino();
  //     int collision = checkCollision(tetromino, 0, 1);
  //     if (collision == NoCollision) {
  //       moveTetromino(tetromino, 0, 1);
  //     } else if (collision == LockingCollision) {
  //       clearTetromino(tetromino);
  //       lockTetromino(tetromino);
  //       LineClearInfo lines = checkLineClear();
  //       if (lines.num_cleared > 0) {
  //         clearLines(lines);
  //       }
  //       clearGameInfoNextTetromino();
  //       if (initTetromino(generateRandomTetromino()) == HorizontalCollision)
  //       {
  //         *gameState = Terminated;
  //       }
  //     }
  //     fall_count = 0;
  //   }
  //   processInput();
  //   // flushinp();
  //   updateCurrentState();
  //   printField();
  //   napms(TICK);
  //   fall_count += TICK;
  // }
  destroyGame();
  endwin();
}