#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define _POSIX_C_SOURCE 199309L
#define _DEFAULT_SOURCE

#include "../../tetris.h"

GameInfo_t *getGameInfo() {
  static GameInfo_t gameState;
  return &gameState;
}

Tetromino *getTetromino() {
  static Tetromino tetromino;
  return &tetromino;
}

GameInfo_t updateCurrentState() {
  GameInfo_t *gameState = getGameInfo();
  // Tetromino *tetromino = getTetromino();

  return *gameState;
}

void initGame() {
  GameInfo_t *GameState = getGameInfo();
  GameState->level = 1;
  GameState->score = 0;
  GameState->high_score = 0;
  GameState->pause = 0;
  GameState->speed = 1;

  GameState->next = NULL;
  GameState->field = calloc(FIELD_HEIGHT, sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    GameState->field[i] = calloc(FIELD_WIDTH, sizeof(int));
  }

  srandom(time(NULL));
}

void destroyGame() {
  GameInfo_t *GameState = getGameInfo();
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    free(GameState->field[i]);
  }
  free(GameState->field);
}

void printField() {
  clear();
  GameInfo_t *GameState = getGameInfo();
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      // if (GameState->field[i][j] == 0) {
      //   printf("  ");
      // } else {
      //   printf("██");
      // }
      printw("%d ", GameState->field[i][j]);
    }
    printw("\n");
  }

  refresh();
}

void processInput() {
  UserAction_t action;
  int c = getch();
  switch (c) {
    case KEY_UP:
      action = Up;
      break;

    case KEY_DOWN:
      action = Down;
      break;

    case KEY_LEFT:
      action = Left;
      break;

    case KEY_RIGHT:
      action = Right;
      break;

    case ' ':
      action = Action;
      break;

    case 'p':
      action = Pause;
      break;

    case 'q':
      action = Terminate;
      break;

    default:
      action = None;
      break;
  }
  userInput(action, false);
}

int checkCollision(Tetromino *tetromino, int x, int y) {
  GameInfo_t *GameState = getGameInfo();
  int collision = 0;
  for (int i = 0; collision == 0 && i < 4; i++) {
    if (x + tetromino->coordinates[tetromino->state][i].x < 0 ||
        x + tetromino->coordinates[tetromino->state][i].x >= FIELD_WIDTH ||
        y + tetromino->coordinates[tetromino->state][i].y < 0 ||
        y + tetromino->coordinates[tetromino->state][i].y >= FIELD_HEIGHT ||
        GameState->field[y + tetromino->coordinates[tetromino->state][i].y]
                        [x + tetromino->coordinates[tetromino->state][i].x] ==
            Locked) {
      collision = 1;
    }
  }

  return collision;
}

void initTetromino() {
  TetrominoType tetrominoArray[] = {O, I, S, Z, L, J, T};

  Tetromino *tetromino = getTetromino();
  tetromino->x = SPAWN_X;
  tetromino->y = SPAWN_Y;
  tetromino->color = 0;
  tetromino->state = 0;

  // int index = (int)((double)random() / ((double)RAND_MAX + 1) *
  // NUM_TETROMINOS); spawnTetromino(tetrominoArray[index]);
  spawnTetromino(tetrominoArray[I]);
}

void spawnTetromino(TetrominoType type) {
  Tetromino *tetromino = getTetromino();
  tetromino->type = type;
  // tetromino->color = random() % NUM_COLORS;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];

  for (int state = 0; state < tetromino->number_of_states; state++) {
    for (int coordinate = 0; coordinate < 4; coordinate++) {
      tetromino->coordinates[state][coordinate] =
          COORDINATES[tetromino->type][state][coordinate];
    }
  }

  // put tetromino into the game field
  GameInfo_t *GameState = getGameInfo();
  for (int i = 0; i < 4; i++) {
    GameState
        ->field[tetromino->y + tetromino->coordinates[tetromino->state][i].y]
               [tetromino->x + tetromino->coordinates[tetromino->state][i].x] =
        Moving;
  }
}

void moveTetromino(Tetromino *tetromino, int x, int y) {
  GameInfo_t *GameState = getGameInfo();
  for (int i = 0; i < 4; i++) {
    GameState
        ->field[tetromino->y + tetromino->coordinates[tetromino->state][i].y]
               [tetromino->x + tetromino->coordinates[tetromino->state][i].x] =
        Empty;
  }

  tetromino->x += x;
  tetromino->y += y;

  for (int i = 0; i < 4; i++) {
    GameState
        ->field[tetromino->y + tetromino->coordinates[tetromino->state][i].y]
               [tetromino->x + tetromino->coordinates[tetromino->state][i].x] =
        Moving;
  }
}

void rotateTetromino(Tetromino *tetromino) {
  // GameInfo_t *GameState = getGameInfo();
  int old_state = tetromino->state;
  tetromino->state = (tetromino->state + 1) % tetromino->number_of_states;
  if (checkCollision(tetromino, tetromino->x, tetromino->y)) {
    tetromino->state = old_state;
  } else {
    GameInfo_t *GameState = getGameInfo();
    for (int i = 0; i < 4; i++) {
      GameState->field[tetromino->y + tetromino->coordinates[old_state][i].y]
                      [tetromino->x + tetromino->coordinates[old_state][i].x] =
          Empty;
    }

    for (int i = 0; i < 4; i++) {
      GameState
          ->field[tetromino->y + tetromino->coordinates[tetromino->state][i].y]
                 [tetromino->x +
                  tetromino->coordinates[tetromino->state][i].x] = Moving;
    }
  }
}

void userInput(UserAction_t action, __attribute__((unused)) bool hold) {
  GameInfo_t *GameState = getGameInfo();
  Tetromino *tetromino = getTetromino();
  switch (action) {
    case Left:
      if (!checkCollision(tetromino, tetromino->x - 1, tetromino->y)) {
        moveTetromino(tetromino, -1, 0);
      }
      break;
    case Right:
      if (!checkCollision(tetromino, tetromino->x + 1, tetromino->y)) {
        moveTetromino(tetromino, 1, 0);
      }
      break;
    case Down:
      if (!checkCollision(tetromino, tetromino->x, tetromino->y + 1)) {
        moveTetromino(tetromino, 0, 1);
      }
      break;
    case Up:
      if (!checkCollision(tetromino, tetromino->x, tetromino->y - 1)) {
        moveTetromino(tetromino, 0, -1);
      }

      break;
    case Action:
      rotateTetromino(tetromino);
      break;
    case Pause:
      GameState->pause = !GameState->pause;
      break;
    case Terminate:
      // GameState->terminate = true;
      break;
    case None:
      break;
    default:
      break;
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
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_WHITE, COLOR_BLACK);
}
