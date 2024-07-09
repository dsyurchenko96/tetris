#include <ncurses.h>

#include "tetris.h"

int main() {
  initCurses();
  initGame();
  GameInfo_t *gameState = getGameInfo();
  initTetromino();
  while (gameState->terminate == false) {
    processInput();
    updateCurrentState();
    printField();
    napms(50);
  }
  destroyGame();
  endwin();
}