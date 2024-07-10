#include <ncurses.h>
#include <stdbool.h>

#include "../../tetris.h"

void printField() {
    clear();
    printRectangle(0, FIELD_HEIGHT + FIELD_PADDING, 0, (FIELD_WIDTH) * 2 + FIELD_PADDING);
    GameInfo_t *GameState = getGameInfo();
    // Tetromino *tetromino = getTetromino();
    for (int i = 0; i < FIELD_HEIGHT; i++) {
      for (int j = 0; j < FIELD_WIDTH; j++) {
        if (GameState->field[i][j] != Empty) {
          MVADDCH(i + 1, j * 2 + 1, '[');
          MVADDCH(i + 1, j * 2 + 2, ']');
        } else {
          MVADDCH(i + 1, j * 2 + 1, ' ');
          MVADDCH(i + 1, j * 2 + 2, ' ');
        }
      }
      // printw("\n");
    }
    printSideBar();
    refresh();
}

// void printNextTetromino() {
//     // GameInfo_t *GameState = getGameInfo();

// }

void printSideBar() {
    GameInfo_t *GameState = getGameInfo();
    printRectangle(0, FIELD_HEIGHT + FIELD_PADDING, (FIELD_WIDTH) * 2 + FIELD_PADDING + 2, FIELD_WIDTH * 2 + FIELD_PADDING + 16);
    MVPRINTW(1, (FIELD_WIDTH) * 2 + FIELD_PADDING + 5, "Level: %d", GameState->level);

    MVPRINTW(3, (FIELD_WIDTH) * 2 + FIELD_PADDING + 5, "Score:");
    MVPRINTW(4, (FIELD_WIDTH) * 2 + FIELD_PADDING + 5, "%6d", GameState->score);

    MVPRINTW(6, (FIELD_WIDTH) * 2 + FIELD_PADDING + 5, "High Score:");
    MVPRINTW(7, (FIELD_WIDTH) * 2 + FIELD_PADDING + 5, "%6d", GameState->high_score);

    MVPRINTW(9, (FIELD_WIDTH) * 2 + FIELD_PADDING + 5, "Next:");
    printNextTetromino();

    
    // if (GameState->pause) {
    //     MVPRINTW(9, (FIELD_WIDTH) * 2 + FIELD_PADDING + 5, "Paused");
    // }


    
}

void printRectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);
  MVADDCH(bottom_y, left_x, ACS_LLCORNER);

  int i = left_x + 1;
  while (i < right_x) {
    MVADDCH(top_y, i, ACS_HLINE);
    MVADDCH(bottom_y, i, ACS_HLINE);
    i++;
  }
  MVADDCH(top_y, i, ACS_URCORNER);
  MVADDCH(bottom_y, i, ACS_LRCORNER);

  i = top_y + 1;
  while (i < bottom_y) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
    i++;
  }
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
}

/* 

0, 0, 0
0, 1, 1
0, 0, 0
0, 0, 0

------
--[][]
------
------

[0][0] = -
[0][1] = -
[0][2] = -
[0][3] = -
[0][4] = -
[0][5] = -

[1][0] = -
[1][1] = -
[1][2] = [
[1][3] = ]
[1][4] = [
[1][5] = ]

*/