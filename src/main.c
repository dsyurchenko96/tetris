#include <ncurses.h>

#include "tetris.h"

int main() {
  initCurses();
  initGame();
  initTetromino();
  while (true) {
    processInput();
    updateCurrentState();
    printField();
    napms(50);
  }
  // processInput();
  // printField();
  // napms(1000);

  destroyGame();
  endwin();
}