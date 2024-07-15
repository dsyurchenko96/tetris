#include <ncurses.h>

#include "tetris.h"

int main() {
  initCurses();
  initGame();
  getGameInfo()->high_score = readHighScore();
  printStartingScreen();

  int tick_count = 0;
  GameState *gameState = getGameState();
  while (*gameState != Terminated) {
    int input = getch();
    processInput(input);

    if (*gameState > Started) {
      printFrontend();
      GameInfo_t gameInfo = updateCurrentState();
      if (!gameInfo.pause) {
        gameInfo.speed = INITIAL_SPEED / gameInfo.level;
        if (tick_count >= gameInfo.speed) {
          const Tetromino *tetromino = getTetromino();
          *gameState = checkFallingCollision(tetromino);
          tick_count = 0;
        }
        // if (*gameState > Idle) {
        //   printField();
        // }

        tick_count += TICK;
      } else {
        printPauseScreen();
      }
    }

    napms(TICK);
  }
  writeHighScore();
  destroyGame();
  endwin();
}