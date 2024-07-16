#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/backend.h"
#include "../inc/tetris.h"
#include "../inc/tetromino.h"
#include "test_suite.h"

START_TEST(test_rotate_tetromino_o) {
  const GameInfo_t *gameInfo = getGameInfo();
  Tetromino *tetromino = getTetromino();
  tetromino->type = O;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  for (int i = 0; i < 4; i++) {
    rotateTetromino(tetromino);

    // {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}}
    ck_assert(tetromino->x == SPAWN_X);
    ck_assert(tetromino->y == SPAWN_Y);
    ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
    ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
    ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
    ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X + 1] == Moving);
  }
}
END_TEST

START_TEST(test_rotate_tetromino_i) {
  const GameInfo_t *gameInfo = getGameInfo();
  Tetromino *tetromino = getTetromino();
  tetromino->type = I;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  ck_assert(tetromino->state == 0);
  ck_assert(tetromino->number_of_states == 2);
  // {{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}}}

  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 2] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  // {{0, -2}, {0, -1}, {0, 0}, {0, 1}}}
  ck_assert(tetromino->state == 1);
  ck_assert(gameInfo->field[SPAWN_Y - 2][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
}
END_TEST

START_TEST(test_rotate_tetromino_s) {
  const GameInfo_t *gameInfo = getGameInfo();
  Tetromino *tetromino = getTetromino();
  tetromino->type = S;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  ck_assert(tetromino->state == 0);

  // {{0, 0}, {1, 0}, {0, 1}, {-1, 1}},

  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X - 1] == Moving);

  rotateTetromino(tetromino);
  ck_assert(tetromino->state == 1);
  //         {{0, 0}, {0, -1}, {1, 0}, {1, 1}}

  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  ck_assert(tetromino->state == 0);
  // {{0, 0}, {1, 0}, {0, 1}, {-1, 1}},

  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X - 1] == Moving);
}
END_TEST

START_TEST(test_rotate_tetromino_z) {
  const GameInfo_t *gameInfo = getGameInfo();
  Tetromino *tetromino = getTetromino();

  tetromino->type = Z;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  // {{0, 0}, {-1, 0}, {0, 1}, {1, 1}}
  ck_assert(tetromino->state == 0);

  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  // {{0, 0}, {0, 1}, {1, 0}, {1, -1}}
  ck_assert(tetromino->state == 1);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  ck_assert(tetromino->state == 0);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X + 1] == Moving);
}
END_TEST

START_TEST(test_rotate_tetromino_l) {
  const GameInfo_t *gameInfo = getGameInfo();
  Tetromino *tetromino = getTetromino();

  tetromino->type = L;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  // {{0, 0}, {-1, 0}, {1, 0}, {1, -1}}
  ck_assert(tetromino->state == 0);

  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  //   {{0, 0}, {0, -1}, {0, 1}, {1, 1}},
  ck_assert(tetromino->state == 1);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);

  //         {{0, 0}, {-1, 0}, {1, 0}, {-1, 1}},
  ck_assert(tetromino->state == 2);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X - 1] == Moving);

  rotateTetromino(tetromino);
  //         {{0, 0}, {0, 1}, {0, -1}, {-1, -1}}
  ck_assert(tetromino->state == 3);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X - 1] == Moving);

  rotateTetromino(tetromino);
  ck_assert(tetromino->state == 0);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X + 1] == Moving);
}
END_TEST

START_TEST(test_rotate_tetromino_j) {
  const GameInfo_t *gameInfo = getGameInfo();
  Tetromino *tetromino = getTetromino();

  tetromino->type = J;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  //   {{0, 0}, {1, 0}, {-1, 0}, {-1, -1}},
  ck_assert(tetromino->state == 0);

  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X - 1] == Moving);

  rotateTetromino(tetromino);
  //       {{0, 0}, {0, 1}, {0, -1}, {1, -1}},
  ck_assert(tetromino->state == 1);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  //       {{0, 0}, {-1, 0}, {1, 0}, {1, 1}},
  ck_assert(tetromino->state == 2);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  //       {{0, 0}, {0, -1}, {0, 1}, {-1, 1}}
  ck_assert(tetromino->state == 3);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X - 1] == Moving);

  rotateTetromino(tetromino);
  ck_assert(tetromino->state == 0);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X - 1] == Moving);
}
END_TEST

START_TEST(test_rotate_tetromino_t) {
  const GameInfo_t *gameInfo = getGameInfo();
  Tetromino *tetromino = getTetromino();

  tetromino->type = T;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  spawnTetromino(tetromino);

  //   {{0, 0}, {-1, 0}, {1, 0}, {0, -1}},
  ck_assert(tetromino->state == 0);

  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X] == Moving);

  rotateTetromino(tetromino);
  //         {{0, 0}, {0, 1}, {0, -1}, {1, 0}},
  ck_assert(tetromino->state == 1);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);

  rotateTetromino(tetromino);
  //         {{0, 0}, {1, 0}, {-1, 0}, {0, 1}},

  ck_assert(tetromino->state == 2);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);

  rotateTetromino(tetromino);
  //         {{0, 0}, {0, -1}, {0, 1}, {-1, 0}}

  ck_assert(tetromino->state == 3);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y + 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);

  rotateTetromino(tetromino);
  ck_assert(tetromino->state == 0);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X + 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y][SPAWN_X - 1] == Moving);
  ck_assert(gameInfo->field[SPAWN_Y - 1][SPAWN_X] == Moving);
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
