/**
 * @file backend.h
 * @brief Header file containing the prototypes of the backend functionalities
 * for the Tetris game.
 */

#ifndef BACKEND_H
#define BACKEND_H

#include "tetris.h"

/**
 * @brief Retrieves the game information.
 * @return A pointer to the static GameInfo_t structure.
 */
GameInfo_t *getGameInfo();

/**
 * @brief Retrieves the current game state.
 * @return A pointer to the static GameState structure.
 */
GameState *getGameState();

/**
 * @brief Retrieves the current tetromino.
 * @return A pointer to the static Tetromino structure.
 */
Tetromino *getTetromino();

/**
 * @brief Retrieves the game timer.
 * @return A pointer to the static timer integer.
 */
int *getTimer();

/**
 * @brief Initializes the game, setting up the game info, state, and tetromino.
 */
void initGame();

/**
 * @brief Destroys the game, freeing allocated memory.
 */
void destroyGame();

/**
 * @brief Initializes the line clear information.
 * @return A LineClearInfo structure.
 */
LineClearInfo initLineInfo(void);

/**
 * @brief Checks for lines to be cleared.
 * @return A LineClearInfo structure indicating the lines to be cleared.
 */
LineClearInfo checkLineClear(void);

/**
 * @brief Clears the lines specified in the LineClearInfo structure.
 * @param lines The LineClearInfo structure containing lines to be cleared.
 */
void clearLines(LineClearInfo lines);

/**
 * @brief Updates the score and level based on the lines cleared.
 * @param lines The LineClearInfo structure containing lines cleared
 * information.
 */
void updateScoreLevel(LineClearInfo lines);

/**
 * @brief Reads the high score from a file.
 * @return The high score value.
 */
int readHighScore(void);

/**
 * @brief Writes the high score to a file.
 */
void writeHighScore();

/**
 * @brief Sets a byte value at a specific index within an integer.
 * @param value The byte value to set.
 * @param index The index at which to set the byte.
 * @param num The integer in which to set the byte.
 */
void setByte(int value, int index, int *num);

/**
 * @brief Gets a byte value from a specific index within an integer.
 * @param index The index from which to get the byte.
 * @param num The integer from which to get the byte.
 * @return The byte value.
 */
int getByte(int index, int num);

/**
 * @brief Sets the cell information for a specific cell.
 * @param cell The cell to set.
 * @param state The state to set.
 * @param color The color to set.
 */
void setCellInfo(int *cell, int state, int color);

#endif
