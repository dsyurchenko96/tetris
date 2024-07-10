#include "../../tetris.h"

#include <ncurses.h>
#include <stdbool.h>

void printField() {
  clear();
  GameInfo_t *GameState = getGameInfo();
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      // if (GameState->field[i][j] == 0) {
      //   printf("  ");
      // } else {
      //   printf("██");
      // }
      printw("%d ", GameState->field[i][j]);
    }
    printw("\n");
  }

  refresh();
}

void initCurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(FALSE);
  // setlocale(LC_ALL, "");
  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    // exit(1);
  }
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_WHITE, COLOR_BLACK);
}