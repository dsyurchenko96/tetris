#include <ncurses.h>

#include "inc/backend.h"
#include "inc/frontend.h"
#include "inc/states.h"
#include "inc/tetris.h"

int main() {
  initCurses();
  initGame();
  getGameInfo()->high_score = readHighScore();
  printStartingScreen();
  GameState *gameState = getGameState();
  while (*gameState != Terminated) {
    int input = getch();
    processInput(input);

    if (*gameState > Started) {
      GameInfo_t gameInfo = updateCurrentState();
      printFrontend(gameInfo);
      if (!gameInfo.pause) {
        updateFallTimer();
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