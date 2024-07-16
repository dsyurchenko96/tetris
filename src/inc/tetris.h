/**
 * @file tetris.h
 * @brief Defines constants, enums, and structs for the Tetris game.
 */

#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>

// Game field dimensions
/**
 * @brief Height of the game field.
 */
#define FIELD_HEIGHT 20

/**
 * @brief Width of the game field.
 */
#define FIELD_WIDTH 10

// Tetromino spawn coordinates
/**
 * @brief x-coordinate for spawning tetrominos.
 */
#define SPAWN_X 5

/**
 * @brief y-coordinate for spawning tetrominos.
 */
#define SPAWN_Y 2

// Number of different tetromino types and their blocks
/**
 * @brief Number of different tetromino types.
 */
#define NUM_TETROMINOS 7

/**
 * @brief Number of blocks in a tetromino.
 */
#define NUM_BLOCKS 4

// Game settings
/**
 * @brief Starting level of the game.
 */
#define START_LEVEL 1

/**
 * @brief Initial speed of the game.
 */
#define INITIAL_SPEED 1000

/**
 * @brief Game tick duration.
 */
#define TICK 30

// High score file path
/**
 * @brief Path to the high score file.
 */
#define HIGH_SCORE_FILE "highscore.txt"

/**
 * @enum GameState
 * @brief Represents the different states the game can be in.
 */
typedef enum {
  Started,
  Paused,
  Terminated,
  Spawning,
  Locking,
  Idle,
  Shifting,
  Rotating,
  Falling,
} GameState;

/**
 * @enum UserAction_t
 * @brief Represents the different user actions.
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
} UserAction_t;

/**
 * @enum TetrominoType
 * @brief Represents the different types of tetrominos.
 */
typedef enum { O, I, S, Z, L, J, T } TetrominoType;

/**
 * @enum TetrominoColor
 * @brief Represents the different colors of tetrominos.
 */
typedef enum {
  Default,
  Yellow,
  Cyan,
  Green,
  Red,
  Orange,
  Blue,
  Purple
} TetrominoColor;

static const TetrominoColor TETROMINO_COLORS[NUM_TETROMINOS + 1] = {
    Default, Yellow, Cyan, Green, Red, Orange, Blue, Purple};

/**
 * @enum ByteIndeces
 * @brief Represents the indices for state and color bytes in the game field.
 */
typedef enum { StateByte, ColorByte } ByteIndeces;

/**
 * @enum FieldCellState
 * @brief Represents the state of a cell in the game field.
 */
typedef enum { Empty, Moving, Locked } FieldCellState;

/**
 * @enum CollisionState
 * @brief Represents the collision state of a tetromino.
 */
typedef enum {
  NoCollision,
  HorizontalCollision,
  LockingCollision
} CollisionState;

/**
 * @struct LineClearInfo
 * @brief Contains information about cleared lines.
 *
 */
typedef struct {
  int indeces[4];         //!< Array of cleared line indices
  int num_cleared;        //!< Number of cleared lines
  bool to_clear_current;  //!< Indicates if the current lines should be cleared
} LineClearInfo;

/**
 * @struct GameInfo_t
 * @brief Contains the current game state information.
 *
 */
typedef struct {
  int **field;     //!< 2D array representing the game field
  int **next;      //!< 2D array representing the next tetromino
  int score;       //!< Current score
  int high_score;  //!< High score
  int level;       //!< Current level
  int speed;       //!< Current speed
  int pause;       //!< Pause state
} GameInfo_t;

/**
 * @struct Coordinates
 * @brief Represents coordinates on the game field.
 *
 */
typedef struct {
  int x;  //!< X-coordinate
  int y;  //!< Y-coordinate
} Coordinates;

/**
 * @struct Tetromino
 * @brief Represents a tetromino piece.
 *
 */
typedef struct {
  TetrominoType type;       //!< Current tetromino type
  TetrominoType next_type;  //!< Next tetromino type
  int x;                    //!< X-coordinate of the tetromino
  int y;                    //!< Y-coordinate of the tetromino
  int color;                //!< Color of the tetromino
  int number_of_states;     //!< Number of rotation states
  int state;                //!< Current rotation state
  int previous_state;       //!< Previous rotation state
} Tetromino;

static const Coordinates COORDINATES[NUM_TETROMINOS][4][4] = {
    // O
    {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}},
    // I
    {{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}}, {{0, -2}, {0, -1}, {0, 0}, {0, 1}}},
    // S
    {{{0, 0}, {1, 0}, {0, 1}, {-1, 1}}, {{0, 0}, {0, -1}, {1, 0}, {1, 1}}},
    // Z
    {{{0, 0}, {-1, 0}, {0, 1}, {1, 1}}, {{0, 0}, {0, 1}, {1, 0}, {1, -1}}},
    // L
    {{{0, 0}, {-1, 0}, {1, 0}, {1, -1}},
     {{0, 0}, {0, -1}, {0, 1}, {1, 1}},
     {{0, 0}, {-1, 0}, {1, 0}, {-1, 1}},
     {{0, 0}, {0, 1}, {0, -1}, {-1, -1}}},
    // J
    {{{0, 0}, {1, 0}, {-1, 0}, {-1, -1}},
     {{0, 0}, {0, 1}, {0, -1}, {1, -1}},
     {{0, 0}, {-1, 0}, {1, 0}, {1, 1}},
     {{0, 0}, {0, -1}, {0, 1}, {-1, 1}}},
    // T
    {{{0, 0}, {-1, 0}, {1, 0}, {0, -1}},
     {{0, 0}, {0, 1}, {0, -1}, {1, 0}},
     {{0, 0}, {1, 0}, {-1, 0}, {0, 1}},
     {{0, 0}, {0, -1}, {0, 1}, {-1, 0}}}};

static const int STATES_COUNT[NUM_TETROMINOS] = {1, 2, 2, 2, 4, 4, 4};

#endif
