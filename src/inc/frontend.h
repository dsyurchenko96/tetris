/**
 * @file frontend.h
 * @brief Header file that contains definitions and function prototypes for
 * rendering the frontend of the Tetris game using ncurses.
 */

#ifndef FRONTEND_H
#define FRONTEND_H

#include "tetris.h"

// Board start position
/**
 * @brief Defines the starting position of the board.
 */
#define BOARDS_BEGIN 2

// Macro for printing to a specific location with padding
/**
 * @brief Macro to print formatted text at a specified location.
 *
 * @param y The y-coordinate.
 * @param x The x-coordinate.
 */
#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)

// Macro for adding a character at a specific location with padding
/**
 * @brief Macro to add a character at a specified location.
 *
 * @param y The y-coordinate.
 * @param x The x-coordinate.
 * @param c The character to add.
 */
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

// Field dimensions and padding
/**
 * @brief Padding for the game field.
 */
#define FIELD_PADDING 1

/**
 * @brief Height of the game field.
 */
#define FIELD_N (FIELD_HEIGHT + FIELD_PADDING)

/**
 * @brief Width of the game field.
 */
#define FIELD_M (FIELD_WIDTH * 2 + FIELD_PADDING)

// Sidebar dimensions and padding
/**
 * @brief Padding for the sidebar.
 */
#define SIDEBAR_PADDING 1

/**
 * @brief Width of the sidebar.
 */
#define SIDEBAR_WIDTH 16

/**
 * @brief x-coordinate for the sidebar.
 */
#define SIDEBAR_X (FIELD_WIDTH) * 2 + FIELD_PADDING + 4

// Controls display position
/**
 * @brief x-coordinate for displaying controls.
 */
#define CONTROLS_X (SIDEBAR_X + 15)

// Color definition for Orange (if not supported by terminal, fallback to RGB
// definition)
/**
 * @brief Defines the color orange.
 */
#define COLOR_ORANGE 202

/**
 * @brief Prints the entire frontend including the game field, sidebar, and next
 * tetromino.
 *
 * @param gameInfo Struct containing the current game state information.
 */
void printFrontend(const GameInfo_t gameInfo);

/**
 * @brief Prints the starting screen with instructions to start the game.
 */
void printStartingScreen();

/**
 * @brief Prints the game field with the current state of all cells.
 *
 * @param gameInfo Struct containing the current game state information.
 */
void printField(const GameInfo_t gameInfo);

/**
 * @brief Prints the next tetromino in the sidebar.
 *
 * @param gameInfo Struct containing the current game state information.
 */
void printNextTetromino(const GameInfo_t gameInfo);

/**
 * @brief Prints a single cell on the game field or sidebar.
 *
 * @param row Row position of the cell.
 * @param col Column position of the cell.
 * @param row_shift Row shift for adjusting position.
 * @param col_shift Column shift for adjusting position.
 * @param state State of the cell (empty, moving, locked).
 * @param color Color of the cell.
 */
void printCell(int row, int col, int row_shift, int col_shift, int state,
               int color);

/**
 * @brief Prints the game controls on the sidebar.
 */
void printControls();

/**
 * @brief Prints the pause screen message.
 */
void printPauseScreen();

/**
 * @brief Prints the sidebar with game level, score, high score, and next
 * tetromino.
 *
 * @param gameInfo Struct containing the current game state information.
 */
void printSideBar(const GameInfo_t gameInfo);

/**
 * @brief Prints a rectangle frame on the screen.
 *
 * @param top_y Top y-coordinate of the rectangle.
 * @param bottom_y Bottom y-coordinate of the rectangle.
 * @param left_x Left x-coordinate of the rectangle.
 * @param right_x Right x-coordinate of the rectangle.
 */
void printRectangle(int top_y, int bottom_y, int left_x, int right_x);

/**
 * @brief Initializes ncurses and sets up the screen for the game.
 */
void initCurses();

/**
 * @brief Processes user input and performs corresponding actions.
 *
 * @param c The input character or key code.
 */
void processInput(int c);

#endif