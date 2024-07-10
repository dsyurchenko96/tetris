#include "../../tetris.h"

#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

#define BOARDS_BEGIN 2

#define FIELD_PADDING 1
#define FIELD_N (FIELD_HEIGHT + FIELD_PADDING)
#define FIELD_M (FIELD_WIDTH * 2 + FIELD_PADDING)

#define SIDEBAR_PADDING 1
#define SIDEBAR_WIDTH 16
#define SIDEBAR_X (FIELD_WIDTH) * 2 + FIELD_PADDING + 4

#define COLOR_ORANGE 202