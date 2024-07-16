#include "frontend.h"

#include <ncurses.h>
#include <stdbool.h>

void printFrontend() {
  clear();
  printField();
  printSideBar();
  printNextTetromino();
  printControls();
  refresh();
}

void printStartingScreen() {
  clear();
  printRectangle(0, FIELD_N, 0, FIELD_M);
  MVPRINTW(2, 8, "TETRIS");
  MVPRINTW(4, 5, "Press 'Enter'");
  MVPRINTW(5, 7, "to start");
  refresh();
}

void printField() {
  // clear();
  printRectangle(0, FIELD_N, 0, FIELD_M);
  const GameInfo_t *gameInfo = getGameInfo();

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      int state = getByte(StateByte, gameInfo->field[i][j]);
      int color = getByte(ColorByte, gameInfo->field[i][j]);
      printCell(i, j, 1, 0, state, color);
    }
  }
  // printSideBar();
  // printControls();
  // refresh();
}

void printControls() {
  MVPRINTW(1, CONTROLS_X, "Controls:");
  MVPRINTW(3, CONTROLS_X, "Left/Right - Move");
  MVPRINTW(4, CONTROLS_X, "Down - Accelerate");
  MVPRINTW(5, CONTROLS_X, "Space - Rotate");
  MVPRINTW(6, CONTROLS_X, "p - Pause");
  MVPRINTW(7, CONTROLS_X, "q - Quit");
}

void printCell(int row, int col, int row_shift, int col_shift, int state,
               int color) {
  if (has_colors() == TRUE && state != Empty) {
    attron(COLOR_PAIR(color));
    MVADDCH(row + row_shift, col_shift + col * 2 + 1, ' ' | A_REVERSE);
    MVADDCH(row + row_shift, col_shift + col * 2 + 2, ' ' | A_REVERSE);
    attroff(COLOR_PAIR(color));
  } else if (has_colors() == FALSE && state != Empty) {
    MVADDCH(row + row_shift, col_shift + col * 2 + 1, '[');
    MVADDCH(row + row_shift, col_shift + col * 2 + 2, ']');
  } else {
    MVADDCH(row + row_shift, col_shift + col * 2 + 1, ' ');
    MVADDCH(row + row_shift, col_shift + col * 2 + 2, ' ');
  }
}

void printNextTetromino() {
  const GameInfo_t *gameInfo = getGameInfo();

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int state = getByte(StateByte, gameInfo->next[i][j]);
      int color = getByte(ColorByte, gameInfo->next[i][j]);
      printCell(i, j, 10, SIDEBAR_X, state, color);
    }
  }
}

void printPauseScreen() {
  MVPRINTW(16, (FIELD_WIDTH) * 2 + FIELD_PADDING + 5, "Paused");
  refresh();
}

void printSideBar() {
  GameInfo_t *gameInfo = getGameInfo();
  printRectangle(0, FIELD_N, FIELD_M + 2, FIELD_M + 16);
  MVPRINTW(1, SIDEBAR_X, "Level: %d", gameInfo->level);

  MVPRINTW(3, SIDEBAR_X, "Score:");
  MVPRINTW(4, SIDEBAR_X, "%6d", gameInfo->score);

  MVPRINTW(6, SIDEBAR_X, "High Score:");
  MVPRINTW(7, SIDEBAR_X, "%6d", gameInfo->high_score);

  MVPRINTW(9, SIDEBAR_X, "Next:");
  // printNextTetromino();
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
  if (has_colors() == TRUE) {
    start_color();

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

void processInput(int c) {
  switch (c) {
    case KEY_UP:
      userInput(Up, false);
      break;

    case KEY_DOWN:
      userInput(Down, false);
      break;

    case KEY_LEFT:
      userInput(Left, false);
      break;

    case KEY_RIGHT:
      userInput(Right, false);
      break;

    case '\n':
      userInput(Start, false);
      break;

    case ' ':
      userInput(Action, true);
      break;

    case 'p':
    case 'P':
      userInput(Pause, false);
      break;

    case 'q':
    case 'Q':
      userInput(Terminate, false);
      break;

    default:
      break;
  }
}