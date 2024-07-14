#include "frontend.h"

#include <ncurses.h>
#include <stdbool.h>

void printStartingScreen() {
  clear();
  printRectangle(0, FIELD_N, 0, FIELD_M);
  MVPRINTW(2, 8, "TETRIS");
  MVPRINTW(4, 5, "Press 'Enter'");
  MVPRINTW(5, 7, "to start");
  refresh();
}

void printField() {
  clear();
  printRectangle(0, FIELD_N, 0, FIELD_M);
  GameInfo_t *GameState = getGameInfo();
  // Tetromino *tetromino = getTetromino();
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      int state = getByte(StateByte, GameState->field[i][j]);
      int color = getByte(ColorByte, GameState->field[i][j]);
      if (has_colors() == TRUE && state != Empty) {
        attron(COLOR_PAIR(color));
        MVADDCH(i + 1, j * 2 + 1, ' ' | A_REVERSE);
        MVADDCH(i + 1, j * 2 + 2, ' ' | A_REVERSE);
        attroff(COLOR_PAIR(color));
      } else if (has_colors() == FALSE && state != Empty) {
        MVADDCH(i + 1, j * 2 + 1, '[');
        MVADDCH(i + 1, j * 2 + 2, ']');
      } else {
        MVADDCH(i + 1, j * 2 + 1, ' ');
        MVADDCH(i + 1, j * 2 + 2, ' ');
      }
    }
  }
  printSideBar();
  refresh();
}

void printNextTetromino() {
  GameInfo_t *GameState = getGameInfo();

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int state = getByte(StateByte, GameState->next[i][j]);
      int color = getByte(ColorByte, GameState->next[i][j]);
      if (has_colors() == TRUE && state != Empty) {
        // MVPRINTW(i + 10, SIDEBAR_X + j, "1");
        attron(COLOR_PAIR(color));
        MVADDCH(i + 10, SIDEBAR_X + j * 2 + 1, ' ' | A_REVERSE);
        MVADDCH(i + 10, SIDEBAR_X + j * 2 + 2, ' ' | A_REVERSE);
        attroff(COLOR_PAIR(color));
      } else if (has_colors() == FALSE && state != Empty) {
        MVADDCH(i + 10, SIDEBAR_X + j * 2 + 1, '[');
        MVADDCH(i + 10, SIDEBAR_X + j * 2 + 2, ']');
      } else {
        // MVPRINTW(i + 10, SIDEBAR_X + j, "0");
        MVADDCH(i + 10, SIDEBAR_X + j * 2 + 1, ' ');
        MVADDCH(i + 10, SIDEBAR_X + j * 2 + 2, ' ');
      }
    }
  }
}

void printSideBar() {
  GameInfo_t *GameState = getGameInfo();
  printRectangle(0, FIELD_N, FIELD_M + 2, FIELD_M + 16);
  MVPRINTW(1, SIDEBAR_X, "Level: %d", GameState->level);

  MVPRINTW(3, SIDEBAR_X, "Score:");
  MVPRINTW(4, SIDEBAR_X, "%6d", GameState->score);

  MVPRINTW(6, SIDEBAR_X, "High Score:");
  MVPRINTW(7, SIDEBAR_X, "%6d", GameState->high_score);

  MVPRINTW(9, SIDEBAR_X, "Next:");
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
  if (has_colors() == TRUE) {
    start_color();

    // TetrominoColor TETROMINO_COLORS[NUM_TETROMINOS] = {Yellow, Cyan, Green,
    // Red, Orange, Blue, Purple};
    // orange = 9
    // init_color(9, 255, 165, 0);

    init_pair(Yellow, COLOR_YELLOW, COLOR_BLACK);
    init_pair(Cyan, COLOR_CYAN, COLOR_BLACK);
    init_pair(Green, COLOR_GREEN, COLOR_BLACK);
    init_pair(Red, COLOR_RED, COLOR_BLACK);
    if (COLORS >= 255) {
      init_pair(Orange, COLOR_ORANGE, COLOR_BLACK);
    } else {
      init_color(7, 255, 165, 0);
      init_pair(Orange, 7, COLOR_BLACK);
    }
    init_pair(Blue, COLOR_BLUE, COLOR_BLACK);
    init_pair(Purple, COLOR_MAGENTA, COLOR_BLACK);
  }
}