#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../tetris.h"

void setup_tetromino(void) {
  initGame();
  Tetromino *tetromino = getTetromino();
  tetromino->x = SPAWN_X;
  tetromino->y = SPAWN_Y;
  tetromino->state = 0;
}

void teardown(void) { destroyGame(); }

// START_TEST(test_spawn_tetromino_o) {
//   Tetromino *tetromino = getTetromino();
//   spawnTetromino(O);

//   ck_assert(tetromino->number_of_states == 1);
//   ck_assert(tetromino->type == O);

//   // {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}}
//   ck_assert(tetromino->coordinates[0][0].x == 0);
//   ck_assert(tetromino->coordinates[0][0].y == 0);
//   ck_assert(tetromino->coordinates[0][1].x == 0);
//   ck_assert(tetromino->coordinates[0][1].y == 1);
//   ck_assert(tetromino->coordinates[0][2].x == 1);
//   ck_assert(tetromino->coordinates[0][2].y == 0);
//   ck_assert(tetromino->coordinates[0][3].x == 1);
//   ck_assert(tetromino->coordinates[0][3].y == 1);
// }
// END_TEST

// START_TEST(test_spawn_tetromino_i) {
//   Tetromino *tetromino = getTetromino();
//   spawnTetromino(I);

//   ck_assert(tetromino->number_of_states == 2);
//   ck_assert(tetromino->type == I);

//   // {{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}}}
//   ck_assert(tetromino->coordinates[0][0].x == -2);
//   ck_assert(tetromino->coordinates[0][0].y == 0);
//   ck_assert(tetromino->coordinates[0][1].x == -1);
//   ck_assert(tetromino->coordinates[0][1].y == 0);
//   ck_assert(tetromino->coordinates[0][2].x == 0);
//   ck_assert(tetromino->coordinates[0][2].y == 0);
//   ck_assert(tetromino->coordinates[0][3].x == 1);
//   ck_assert(tetromino->coordinates[0][3].y == 0);

//   // {{0, -2}, {0, -1}, {0, 0}, {0, 1}}}
//   ck_assert(tetromino->coordinates[1][0].x == 0);
//   ck_assert(tetromino->coordinates[1][0].y == -2);
//   ck_assert(tetromino->coordinates[1][1].x == 0);
//   ck_assert(tetromino->coordinates[1][1].y == -1);
//   ck_assert(tetromino->coordinates[1][2].x == 0);
//   ck_assert(tetromino->coordinates[1][2].y == 0);
//   ck_assert(tetromino->coordinates[1][3].x == 0);
//   ck_assert(tetromino->coordinates[1][3].y == 1);
// }
// END_TEST

// START_TEST(test_spawn_tetromino_s) {
//   Tetromino *tetromino = getTetromino();
//   spawnTetromino(S);

//   ck_assert(tetromino->number_of_states == 2);
//   ck_assert(tetromino->type == S);

//   //   {{0, 0}, {1, 0}, {0, 1}, {-1, 1}},

//   ck_assert(tetromino->coordinates[0][0].x == 0);
//   ck_assert(tetromino->coordinates[0][0].y == 0);
//   ck_assert(tetromino->coordinates[0][1].x == 1);
//   ck_assert(tetromino->coordinates[0][1].y == 0);
//   ck_assert(tetromino->coordinates[0][2].x == 0);
//   ck_assert(tetromino->coordinates[0][2].y == 1);
//   ck_assert(tetromino->coordinates[0][3].x == -1);
//   ck_assert(tetromino->coordinates[0][3].y == 1);

//   //         {{0, 0}, {0, -1}, {1, 0}, {1, 1}}

//   ck_assert(tetromino->coordinates[1][0].x == 0);
//   ck_assert(tetromino->coordinates[1][0].y == 0);
//   ck_assert(tetromino->coordinates[1][1].x == 0);
//   ck_assert(tetromino->coordinates[1][1].y == -1);
//   ck_assert(tetromino->coordinates[1][2].x == 1);
//   ck_assert(tetromino->coordinates[1][2].y == 0);
//   ck_assert(tetromino->coordinates[1][3].x == 1);
//   ck_assert(tetromino->coordinates[1][3].y == 1);
// }
// END_TEST

// START_TEST(test_spawn_tetromino_z) {
//   Tetromino *tetromino = getTetromino();
//   spawnTetromino(Z);

//   ck_assert(tetromino->number_of_states == 2);
//   ck_assert(tetromino->type == Z);

//   //   {{0, 0}, {-1, 0}, {0, 1}, {1, 1}},
//   ck_assert(tetromino->coordinates[0][0].x == 0);
//   ck_assert(tetromino->coordinates[0][0].y == 0);
//   ck_assert(tetromino->coordinates[0][1].x == -1);
//   ck_assert(tetromino->coordinates[0][1].y == 0);
//   ck_assert(tetromino->coordinates[0][2].x == 0);
//   ck_assert(tetromino->coordinates[0][2].y == 1);
//   ck_assert(tetromino->coordinates[0][3].x == 1);
//   ck_assert(tetromino->coordinates[0][3].y == 1);

//   //         {{0, 0}, {0, 1}, {1, 0}, {1, -1}}

//   ck_assert(tetromino->coordinates[1][0].x == 0);
//   ck_assert(tetromino->coordinates[1][0].y == 0);
//   ck_assert(tetromino->coordinates[1][1].x == 0);
//   ck_assert(tetromino->coordinates[1][1].y == 1);
//   ck_assert(tetromino->coordinates[1][2].x == 1);
//   ck_assert(tetromino->coordinates[1][2].y == 0);
//   ck_assert(tetromino->coordinates[1][3].x == 1);
//   ck_assert(tetromino->coordinates[1][3].y == -1);
// }
// END_TEST

// START_TEST(test_spawn_tetromino_l) {
//   Tetromino *tetromino = getTetromino();
//   spawnTetromino(L);

//   ck_assert(tetromino->number_of_states == 4);
//   ck_assert(tetromino->type == L);

//   //   {{0, 0}, {-1, 0}, {1, 0}, {1, -1}},
//   ck_assert(tetromino->coordinates[0][0].x == 0);
//   ck_assert(tetromino->coordinates[0][0].y == 0);
//   ck_assert(tetromino->coordinates[0][1].x == -1);
//   ck_assert(tetromino->coordinates[0][1].y == 0);
//   ck_assert(tetromino->coordinates[0][2].x == 1);
//   ck_assert(tetromino->coordinates[0][2].y == 0);
//   ck_assert(tetromino->coordinates[0][3].x == 1);
//   ck_assert(tetromino->coordinates[0][3].y == -1);

//   //         {{0, 0}, {0, -1}, {0, 1}, {1, 1}},
//   ck_assert(tetromino->coordinates[1][0].x == 0);
//   ck_assert(tetromino->coordinates[1][0].y == 0);
//   ck_assert(tetromino->coordinates[1][1].x == 0);
//   ck_assert(tetromino->coordinates[1][1].y == -1);
//   ck_assert(tetromino->coordinates[1][2].x == 0);
//   ck_assert(tetromino->coordinates[1][2].y == 1);
//   ck_assert(tetromino->coordinates[1][3].x == 1);
//   ck_assert(tetromino->coordinates[1][3].y == 1);

//   //         {{0, 0}, {-1, 0}, {1, 0}, {-1, 1}},
//   ck_assert(tetromino->coordinates[2][0].x == 0);
//   ck_assert(tetromino->coordinates[2][0].y == 0);
//   ck_assert(tetromino->coordinates[2][1].x == -1);
//   ck_assert(tetromino->coordinates[2][1].y == 0);
//   ck_assert(tetromino->coordinates[2][2].x == 1);
//   ck_assert(tetromino->coordinates[2][2].y == 0);
//   ck_assert(tetromino->coordinates[2][3].x == -1);
//   ck_assert(tetromino->coordinates[2][3].y == 1);

//   //         {{0, 0}, {0, 1}, {0, -1}, {-1, -1}},
//   ck_assert(tetromino->coordinates[3][0].x == 0);
//   ck_assert(tetromino->coordinates[3][0].y == 0);
//   ck_assert(tetromino->coordinates[3][1].x == 0);
//   ck_assert(tetromino->coordinates[3][1].y == 1);
//   ck_assert(tetromino->coordinates[3][2].x == 0);
//   ck_assert(tetromino->coordinates[3][2].y == -1);
//   ck_assert(tetromino->coordinates[3][3].x == -1);
//   ck_assert(tetromino->coordinates[3][3].y == -1);
// }
// END_TEST

// START_TEST(test_spawn_tetromino_j) {
//   Tetromino *tetromino = getTetromino();
//   spawnTetromino(J);

//   ck_assert(tetromino->number_of_states == 4);

//   //   {{0, 0}, {1, 0}, {-1, 0}, {-1, -1}},
//   ck_assert(tetromino->coordinates[0][0].x == 0);
//   ck_assert(tetromino->coordinates[0][0].y == 0);
//   ck_assert(tetromino->coordinates[0][1].x == 1);
//   ck_assert(tetromino->coordinates[0][1].y == 0);
//   ck_assert(tetromino->coordinates[0][2].x == -1);
//   ck_assert(tetromino->coordinates[0][2].y == 0);
//   ck_assert(tetromino->coordinates[0][3].x == -1);
//   ck_assert(tetromino->coordinates[0][3].y == -1);

//   //       {{0, 0}, {0, 1}, {0, -1}, {1, -1}},
//   ck_assert(tetromino->coordinates[1][0].x == 0);
//   ck_assert(tetromino->coordinates[1][0].y == 0);
//   ck_assert(tetromino->coordinates[1][1].x == 0);
//   ck_assert(tetromino->coordinates[1][1].y == 1);
//   ck_assert(tetromino->coordinates[1][2].x == 0);
//   ck_assert(tetromino->coordinates[1][2].y == -1);
//   ck_assert(tetromino->coordinates[1][3].x == 1);
//   ck_assert(tetromino->coordinates[1][3].y == -1);

//   //       {{0, 0}, {-1, 0}, {1, 0}, {1, 1}},
//   ck_assert(tetromino->coordinates[2][0].x == 0);
//   ck_assert(tetromino->coordinates[2][0].y == 0);
//   ck_assert(tetromino->coordinates[2][1].x == -1);
//   ck_assert(tetromino->coordinates[2][1].y == 0);
//   ck_assert(tetromino->coordinates[2][2].x == 1);
//   ck_assert(tetromino->coordinates[2][2].y == 0);
//   ck_assert(tetromino->coordinates[2][3].x == 1);
//   ck_assert(tetromino->coordinates[2][3].y == 1);

//   //       {{0, 0}, {0, -1}, {0, 1}, {-1, 1}}
//   ck_assert(tetromino->coordinates[3][0].x == 0);
//   ck_assert(tetromino->coordinates[3][0].y == 0);
//   ck_assert(tetromino->coordinates[3][1].x == 0);
//   ck_assert(tetromino->coordinates[3][1].y == -1);
//   ck_assert(tetromino->coordinates[3][2].x == 0);
//   ck_assert(tetromino->coordinates[3][2].y == 1);
//   ck_assert(tetromino->coordinates[3][3].x == -1);
//   ck_assert(tetromino->coordinates[3][3].y == 1);
// }
// END_TEST

// START_TEST(test_spawn_tetromino_t) {
//   Tetromino *tetromino = getTetromino();
//   spawnTetromino(T);
//   ck_assert(tetromino->number_of_states == 4);
//   //   {{0, 0}, {-1, 0}, {1, 0}, {0, -1}},
//   ck_assert(tetromino->coordinates[0][0].x == 0);
//   ck_assert(tetromino->coordinates[0][0].y == 0);
//   ck_assert(tetromino->coordinates[0][1].x == -1);
//   ck_assert(tetromino->coordinates[0][1].y == 0);
//   ck_assert(tetromino->coordinates[0][2].x == 1);
//   ck_assert(tetromino->coordinates[0][2].y == 0);
//   ck_assert(tetromino->coordinates[0][3].x == 0);
//   ck_assert(tetromino->coordinates[0][3].y == -1);
//   //       {{0, 0}, {0, 1}, {0, -1}, {1, 0}},
//   ck_assert(tetromino->coordinates[1][0].x == 0);
//   ck_assert(tetromino->coordinates[1][0].y == 0);
//   ck_assert(tetromino->coordinates[1][1].x == 0);
//   ck_assert(tetromino->coordinates[1][1].y == 1);
//   ck_assert(tetromino->coordinates[1][2].x == 0);
//   ck_assert(tetromino->coordinates[1][2].y == -1);
//   ck_assert(tetromino->coordinates[1][3].x == 1);
//   ck_assert(tetromino->coordinates[1][3].y == 0);

//   // {{0, 0}, {1, 0}, {-1, 0}, {0, 1}}
//   ck_assert(tetromino->coordinates[2][0].x == 0);
//   ck_assert(tetromino->coordinates[2][0].y == 0);
//   ck_assert(tetromino->coordinates[2][1].x == 1);
//   ck_assert(tetromino->coordinates[2][1].y == 0);
//   ck_assert(tetromino->coordinates[2][2].x == -1);
//   ck_assert(tetromino->coordinates[2][2].y == 0);
//   ck_assert(tetromino->coordinates[2][3].x == 0);
//   ck_assert(tetromino->coordinates[2][3].y == 1);

//   //       {{0, 0}, {0, -1}, {0, 1}, {-1, 0}}
//   ck_assert(tetromino->coordinates[3][0].x == 0);
//   ck_assert(tetromino->coordinates[3][0].y == 0);
//   ck_assert(tetromino->coordinates[3][1].x == 0);
//   ck_assert(tetromino->coordinates[3][1].y == -1);
//   ck_assert(tetromino->coordinates[3][2].x == 0);
//   ck_assert(tetromino->coordinates[3][2].y == 1);
//   ck_assert(tetromino->coordinates[3][3].x == -1);
//   ck_assert(tetromino->coordinates[3][3].y == 0);
// }
// END_TEST

// Suite *spawn_suite() {
//   Suite *s = suite_create("spawn_tetromino");
//   TCase *tc = tcase_create("spawn_tetromino");

//   tcase_add_checked_fixture(tc, setup_tetromino, teardown);

//   tcase_add_test(tc, test_spawn_tetromino_o);
//   tcase_add_test(tc, test_spawn_tetromino_i);
//   tcase_add_test(tc, test_spawn_tetromino_s);
//   tcase_add_test(tc, test_spawn_tetromino_z);
//   tcase_add_test(tc, test_spawn_tetromino_l);
//   tcase_add_test(tc, test_spawn_tetromino_j);
//   tcase_add_test(tc, test_spawn_tetromino_t);
//   suite_add_tcase(s, tc);
//   return s;
// }

START_TEST(test_rotate_tetromino_o) {
  GameInfo_t *GameState = getGameInfo();
  Tetromino *tetromino = getTetromino();
  tetromino->type = O;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  for (int i = 0; i < 4; i++) {
    rotateTetromino(tetromino);

    // {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}}
    ck_assert(tetromino->x == SPAWN_X);
    ck_assert(tetromino->y == SPAWN_Y);
    ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
    ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
    ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
    ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X + 1] == Moving);
  }
}
END_TEST

START_TEST(test_rotate_tetromino_i) {
  GameInfo_t *GameState = getGameInfo();
  Tetromino *tetromino = getTetromino();
  tetromino->type = I;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  ck_assert(tetromino->state == 0);
  ck_assert(tetromino->number_of_states == 2);
  // {{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}}}

  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 2] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  // {{0, -2}, {0, -1}, {0, 0}, {0, 1}}}
  ck_assert(tetromino->state == 1);
  ck_assert(GameState->field[SPAWN_Y - 2][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
}
END_TEST

START_TEST(test_rotate_tetromino_s) {
  GameInfo_t *GameState = getGameInfo();
  Tetromino *tetromino = getTetromino();
  tetromino->type = S;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  ck_assert(tetromino->state == 0);

  // {{0, 0}, {1, 0}, {0, 1}, {-1, 1}},

  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X - 1] == Moving);

  rotateTetromino(tetromino);
  ck_assert(tetromino->state == 1);
  //         {{0, 0}, {0, -1}, {1, 0}, {1, 1}}

  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  ck_assert(tetromino->state == 0);
  // {{0, 0}, {1, 0}, {0, 1}, {-1, 1}},

  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X - 1] == Moving);
}
END_TEST

START_TEST(test_rotate_tetromino_z) {
  GameInfo_t *GameState = getGameInfo();
  Tetromino *tetromino = getTetromino();
  
  tetromino->type = Z;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  // {{0, 0}, {-1, 0}, {0, 1}, {1, 1}}
  ck_assert(tetromino->state == 0);

  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  // {{0, 0}, {0, 1}, {1, 0}, {1, -1}}
  ck_assert(tetromino->state == 1);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  ck_assert(tetromino->state == 0);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X + 1] == Moving);
}
END_TEST

START_TEST(test_rotate_tetromino_l) {
  GameInfo_t *GameState = getGameInfo();
  Tetromino *tetromino = getTetromino();
  
  tetromino->type = L;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  // {{0, 0}, {-1, 0}, {1, 0}, {1, -1}}
  ck_assert(tetromino->state == 0);

  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  //   {{0, 0}, {0, -1}, {0, 1}, {1, 1}},
  ck_assert(tetromino->state == 1);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);

  //         {{0, 0}, {-1, 0}, {1, 0}, {-1, 1}},
  ck_assert(tetromino->state == 2);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X - 1] == Moving);

  rotateTetromino(tetromino);
  //         {{0, 0}, {0, 1}, {0, -1}, {-1, -1}}
  ck_assert(tetromino->state == 3);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X - 1] == Moving);

  rotateTetromino(tetromino);
  ck_assert(tetromino->state == 0);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X + 1] == Moving);
}
END_TEST

START_TEST(test_rotate_tetromino_j) {
  GameInfo_t *GameState = getGameInfo();
  Tetromino *tetromino = getTetromino();

  tetromino->type = J;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  //   {{0, 0}, {1, 0}, {-1, 0}, {-1, -1}},
  ck_assert(tetromino->state == 0);

  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X - 1] == Moving);

  rotateTetromino(tetromino);
  //       {{0, 0}, {0, 1}, {0, -1}, {1, -1}},
  ck_assert(tetromino->state == 1);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  //       {{0, 0}, {-1, 0}, {1, 0}, {1, 1}},
  ck_assert(tetromino->state == 2);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  //       {{0, 0}, {0, -1}, {0, 1}, {-1, 1}}
  ck_assert(tetromino->state == 3);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X - 1] == Moving);

  rotateTetromino(tetromino);
  ck_assert(tetromino->state == 0);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X - 1] == Moving);
}
END_TEST

START_TEST(test_rotate_tetromino_t) {
  GameInfo_t *GameState = getGameInfo();
  Tetromino *tetromino = getTetromino();

  tetromino->type = T;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  //   {{0, 0}, {-1, 0}, {1, 0}, {0, -1}},
  ck_assert(tetromino->state == 0);

  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X] == Moving);

  rotateTetromino(tetromino);
  //         {{0, 0}, {0, 1}, {0, -1}, {1, 0}},
  ck_assert(tetromino->state == 1);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  //         {{0, 0}, {1, 0}, {-1, 0}, {0, 1}},

  ck_assert(tetromino->state == 2);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);

  rotateTetromino(tetromino);
  //         {{0, 0}, {0, -1}, {0, 1}, {-1, 0}}

  ck_assert(tetromino->state == 3);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);

  rotateTetromino(tetromino);
  ck_assert(tetromino->state == 0);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(GameState->field[SPAWN_Y - 1][SPAWN_X] == Moving);
}
END_TEST

Suite *rotate_suite() {
  Suite *s = suite_create("rotate_tetromino");
  TCase *tc = tcase_create("rotate_tetromino");

  tcase_add_checked_fixture(tc, setup_tetromino, teardown);
  tcase_add_test(tc, test_rotate_tetromino_o);
  tcase_add_test(tc, test_rotate_tetromino_i);
  tcase_add_test(tc, test_rotate_tetromino_s);
  tcase_add_test(tc, test_rotate_tetromino_z);
  tcase_add_test(tc, test_rotate_tetromino_l);
  tcase_add_test(tc, test_rotate_tetromino_j);
  tcase_add_test(tc, test_rotate_tetromino_t);
  suite_add_tcase(s, tc);
  return s;
}
