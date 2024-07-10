#include <ncurses.h>

#include "tetris.h"

int main() {
  initCurses();
  initGame();
  GameInfo_t *gameState = getGameInfo();
  initTetromino();
  int tick = 50;
  int fall_count = 0;
  while (gameState->terminate == false) {
	int fall_speed = 1000 / gameState->speed;
	if (fall_count >= fall_speed) {
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
			initTetromino();
		}
		fall_count = 0;
	}
    processInput();
	// flushinp();
    updateCurrentState();
    printField();
    napms(tick);
	fall_count += tick;
  }
  destroyGame();
  endwin();
}