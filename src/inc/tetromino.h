/**
 * @file tetromino.h
 * @brief This header file contains the prototypes of tetromino-related
 * functionalities for the Tetris game.
 */

#ifndef TETROMINO_H
#define TETROMINO_H

#include "tetris.h"

/**
 * @brief Clears the current tetromino from the game field.
 * @param tetromino The tetromino to clear.
 */
void clearTetromino(const Tetromino *tetromino);

/**
 * @brief Locks the current tetromino into the game field.
 * @param tetromino The tetromino to lock.
 */
void lockTetromino(Tetromino *tetromino);

/**
 * @brief Initializes a new tetromino.
 * @param next_type The type of the next tetromino.
 * @return Collision status after initializing the tetromino.
 */
int initTetromino(TetrominoType next_type);

/**
 * @brief Sets the next tetromino in the game info structure.
 * @param tetromino The tetromino to set as next.
 */
void setGameInfoNextTetromino(Tetromino *tetromino);

/**
 * @brief Clears the next tetromino information in the game info structure.
 */
void clearGameInfoNextTetromino();

/**
 * @brief Generates a random tetromino type.
 * @return The generated TetrominoType.
 */
TetrominoType generateRandomTetromino();

/**
 * @brief Spawns a new tetromino into the game field.
 * @param tetromino The tetromino to spawn.
 * @return Collision status after spawning the tetromino.
 */
int spawnTetromino(Tetromino *tetromino);

/**
 * @brief Moves the current tetromino by a specified offset.
 * @param tetromino The tetromino to move.
 * @param x The x offset to move.
 * @param y The y offset to move.
 */
void moveTetromino(Tetromino *tetromino, int x, int y);

/**
 * @brief Rotates the current tetromino.
 * @param tetromino The tetromino to rotate.
 */
void rotateTetromino(Tetromino *tetromino);

/**
 * @brief Checks for collisions when moving or rotating a tetromino.
 * @param tetromino The tetromino to check.
 * @param x The x offset to check.
 * @param y The y offset to check.
 * @return The collision status.
 */
int checkCollision(const Tetromino *tetromino, int x, int y);

/**
 * @brief Checks for falling collisions and updates the game state accordingly.
 * @param tetromino The tetromino to check.
 * @return The updated game state after checking for collisions.
 */
GameState checkFallingCollision(const Tetromino *tetromino);

#endif