/**
 * @file states.h
 * @brief This header file contains the prototypes of state-related
 * functionalities for the Tetris game.
 */

#ifndef STATES_H
#define STATES_H

#include "tetris.h"

/**
 * @brief Handles user input actions.
 * @param action The action performed by the user.
 * @param hold Indicates whether the action is a hold action.
 */
void userInput(UserAction_t action, __attribute__((unused)) bool hold);

/**
 * @brief Updates the current state of the game.
 * @return The updated GameInfo_t structure.
 */
GameInfo_t updateCurrentState();

/**
 * @brief Updates the fall timer and handles the falling state.
 */
void updateFallTimer();

#endif