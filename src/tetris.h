#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>

#define FIELD_HEIGHT 20
#define FIELD_WIDTH 10

#define SPAWN_X 4
#define SPAWN_Y 1

#define NUM_TETROMINOS 7
#define NUM_BLOCKS 4

#define START_LEVEL 1  // 1 - 10
#define TICK 50

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  None
} UserAction_t;

typedef enum { O, I, S, Z, L, J, T } TetrominoType;

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
// int NCURSES_COLORS[NUM_TETROMINOS] = {COLOR_YELLOW, COLOR_CYAN, COLOR_GREEN,
// COLOR_RED, COLOR_MAGENTA, COLOR_BLUE, COLOR_MAGENTA};

typedef enum { StateByte, ColorByte } ByteIndeces;

typedef enum { Empty, Moving, Locked } FieldCellState;

typedef enum {
  NoCollision,
  HorizontalCollision,
  LockingCollision
} CollisionState;

typedef struct {
  int indeces[4];
  int num_cleared;
  bool to_clear_current;
} LineClearInfo;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int terminate;
} GameInfo_t;

typedef struct {
  int x;
  int y;
} Coordinates;

typedef struct {
  TetrominoType type;
  TetrominoType next_type;
  Coordinates coordinates[4][4];
  bool locked;
  int x;
  int y;
  int color;
  int number_of_states;
  int state;
  int previous_state;
} Tetromino;

static const Coordinates COORDINATES[NUM_TETROMINOS][4][4] = {
    // O
    {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}},
    // I
    {{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}}, {{0, -2}, {0, -1}, {0, 0}, {0, 1}}

    },
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

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

GameInfo_t *getGameInfo();
Tetromino *getTetromino();
GameInfo_t updateCurrentState();

void initGame();
void destroyGame();
void processInput();
int checkCollision(Tetromino *tetromino, int x, int y);

void clearTetromino(Tetromino *tetromino);
void lockTetromino(Tetromino *tetromino);
int initTetromino();
int spawnTetromino(TetrominoType type);
void moveTetromino(Tetromino *tetromino, int x, int y);
void rotateTetromino(Tetromino *tetromino);

void setByte(int value, int index, int *num);
int getByte(int index, int num);
void setCellInfo(int *cell, int state, int color);

LineClearInfo initLineInfo(void);
LineClearInfo checkLineClear(void);
void clearLines(LineClearInfo lines);

void userInput(UserAction_t action, bool hold);

void initCurses();
void printField();
void printRectangle(int top_y, int bottom_y, int left_x, int right_x);
void printSideBar();

#endif