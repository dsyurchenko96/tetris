#include <check.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "../tetris.h"
#include "test_suite.h"

START_TEST(test_userInput_start) {
  GameState *gameState = getGameState();
  ck_assert_int_eq(*gameState, Started);
  userInput(Start, false);
  ck_assert_int_eq(*gameState, Spawning);
}
END_TEST

START_TEST(test_userInput_start_invalid) {
  GameState *gameState = getGameState();
  ck_assert_int_eq(*gameState, Started);
  userInput(Pause, false);
  ck_assert_int_eq(*gameState, Started);
  userInput(Left, false);
  ck_assert_int_eq(*gameState, Started);
  userInput(Right, false);
  ck_assert_int_eq(*gameState, Started);
  userInput(Down, false);
  ck_assert_int_eq(*gameState, Started);
}
END_TEST

START_TEST(test_userInput_pause) {
  GameState *gameState = getGameState();
  userInput(Start, false);
  userInput(Pause, false);
  ck_assert_int_eq(*gameState, Paused);
}
END_TEST

START_TEST(test_userInput_terminate) {
  GameState *gameState = getGameState();
  userInput(Start, false);
  userInput(Terminate, false);
  ck_assert_int_eq(*gameState, Terminated);
}
END_TEST

START_TEST(test_userInput_move_left) {
  GameState *gameState = getGameState();
  // GameInfo_t *gameInfo = getGameInfo();
  Tetromino *tetromino = getTetromino();
  tetromino->type = I;

  ck_assert_int_eq(spawnTetromino(tetromino), 0);
  *gameState = Idle;
  userInput(Left, false);
  ck_assert_int_eq(*gameState, Shifting);
  ck_assert_int_eq(tetromino->x, SPAWN_X - 1);
  userInput(Left, false);
  ck_assert_int_eq(tetromino->x, SPAWN_X - 2);
  userInput(Left, false);
  ck_assert_int_eq(tetromino->x, SPAWN_X - 3);
  userInput(Left, false);
  ck_assert_int_eq(tetromino->x, SPAWN_X - 3);
}
END_TEST

START_TEST(test_userInput_move_right) {
  GameState *gameState = getGameState();
  // GameInfo_t *gameInfo = getGameInfo();
  Tetromino *tetromino = getTetromino();
  tetromino->type = L;

  ck_assert_int_eq(spawnTetromino(tetromino), 0);
  *gameState = Idle;
  userInput(Right, false);
  ck_assert_int_eq(*gameState, Shifting);
  ck_assert_int_eq(tetromino->x, SPAWN_X + 1);
  userInput(Right, false);
  ck_assert_int_eq(tetromino->x, SPAWN_X + 2);
  userInput(Right, false);
  ck_assert_int_eq(tetromino->x, SPAWN_X + 3);
  userInput(Right, false);
  ck_assert_int_eq(tetromino->x, SPAWN_X + 3);
}
END_TEST

START_TEST(test_userInput_move_down) {
  GameState *gameState = getGameState();
  // GameInfo_t *gameInfo = getGameInfo();
  Tetromino *tetromino = getTetromino();
  tetromino->type = O;

  ck_assert_int_eq(spawnTetromino(tetromino), 0);
  *gameState = Idle;
  ck_assert_int_eq(tetromino->y, SPAWN_Y);
  userInput(Down, false);
  ck_assert_int_eq(*gameState, Falling);
}
END_TEST

START_TEST(test_userInput_action) {
  GameState *gameState = getGameState();
  Tetromino *tetromino = getTetromino();
  tetromino->type = T;

  ck_assert_int_eq(spawnTetromino(tetromino), 0);
  *gameState = Idle;
  userInput(Action, true);
  ck_assert_int_eq(*gameState, Rotating);
}
END_TEST

START_TEST(test_processInput_invalid_input) {
  GameState *gameState = getGameState();
  *gameState = Idle;
  processInput('x');
  ck_assert_int_eq(*gameState, Idle);
}
END_TEST

START_TEST(test_processInput_key_down) {
  GameState *gameState = getGameState();
  *gameState = Idle;
  processInput(KEY_DOWN);
  ck_assert_int_eq(*gameState, Falling);
}
END_TEST

START_TEST(test_processInput_key_left) {
  GameState *gameState = getGameState();
  Tetromino *tetromino = getTetromino();

  ck_assert_int_eq(spawnTetromino(tetromino), 0);
  *gameState = Idle;
  processInput(KEY_LEFT);
  ck_assert_int_eq(*gameState, Shifting);
}
END_TEST

START_TEST(test_processInput_move_right) {
  GameState *gameState = getGameState();
  Tetromino *tetromino = getTetromino();
  tetromino->type = L;

  ck_assert_int_eq(spawnTetromino(tetromino), 0);
  *gameState = Idle;
  processInput(KEY_RIGHT);
  ck_assert_int_eq(*gameState, Shifting);
}
END_TEST

START_TEST(test_userInput_start_action) {
  GameState *gameState = getGameState();
  ck_assert_int_eq(*gameState, Started);
  processInput('\n');
  ck_assert_int_eq(*gameState, Spawning);
}
END_TEST

START_TEST(test_processInput_space_action) {
  GameState *gameState = getGameState();
  *gameState = Idle;
  processInput(' ');
  ck_assert_int_eq(*gameState, Rotating);
}
END_TEST

START_TEST(test_processInput_pause) {
  GameState *gameState = getGameState();
  processInput('\n');
  processInput('p');
  ck_assert_int_eq(*gameState, Paused);
  *gameState = Idle;
  processInput('P');
  ck_assert_int_eq(*gameState, Paused);
}
END_TEST

START_TEST(test_processInput_terminate) {
  GameState *gameState = getGameState();
  processInput('\n');
  processInput('q');
  ck_assert_int_eq(*gameState, Terminated);
  *gameState = Idle;
  processInput('Q');
  ck_assert_int_eq(*gameState, Terminated);
}
END_TEST

Suite *input_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("input");
  tc = tcase_create("input");
  tcase_add_checked_fixture(tc, setup_tetromino, teardown);
  tcase_add_test(tc, test_userInput_start);
  tcase_add_test(tc, test_userInput_start_invalid);
  tcase_add_test(tc, test_userInput_pause);
  tcase_add_test(tc, test_userInput_terminate);
  tcase_add_test(tc, test_userInput_move_left);
  tcase_add_test(tc, test_userInput_move_right);
  tcase_add_test(tc, test_userInput_move_down);
  tcase_add_test(tc, test_userInput_action);

  tcase_add_test(tc, test_processInput_invalid_input);
  tcase_add_test(tc, test_processInput_key_down);
  tcase_add_test(tc, test_processInput_key_left);
  tcase_add_test(tc, test_processInput_move_right);
  tcase_add_test(tc, test_userInput_start_action);
  tcase_add_test(tc, test_processInput_space_action);
  tcase_add_test(tc, test_processInput_pause);
  tcase_add_test(tc, test_processInput_terminate);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(test_updateCurrentState_falling) {
  GameState *gameState = getGameState();
  Tetromino *tetromino = getTetromino();
  tetromino->type = T;

  ck_assert_int_eq(spawnTetromino(tetromino), 0);
  *gameState = Falling;
  ck_assert_int_eq(tetromino->y, SPAWN_Y);
  updateCurrentState();
  ck_assert_int_eq(tetromino->y, SPAWN_Y + 1);
  ck_assert_int_eq(*gameState, Idle);
}
END_TEST

START_TEST(test_updateCurrentState_rotating) {
  GameState *gameState = getGameState();
  Tetromino *tetromino = getTetromino();
  tetromino->type = L;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];

  ck_assert_int_eq(spawnTetromino(tetromino), 0);
  *gameState = Rotating;
  ck_assert_int_eq(tetromino->state, 0);
  updateCurrentState();
  ck_assert_int_eq(tetromino->state, 1);
  ck_assert_int_eq(*gameState, Idle);
}
END_TEST

START_TEST(test_updateCurrentState_paused) {
  GameState *gameState = getGameState();
  GameInfo_t *gameInfo = getGameInfo();
  ck_assert_int_eq(gameInfo->pause, 0);
  *gameState = Paused;
  updateCurrentState();
  ck_assert_int_eq(gameInfo->pause, 1);
  ck_assert_int_eq(*gameState, Idle);
}
END_TEST

START_TEST(test_updateCurrentState_spawning_no_collision) {
  GameState *gameState = getGameState();
  *gameState = Spawning;
  updateCurrentState();
  ck_assert_int_eq(*gameState, Idle);
}
END_TEST

START_TEST(test_updateCurrentState_spawning_collision) {
  GameState *gameState = getGameState();
  Tetromino *tetromino = getTetromino();
  GameInfo_t *gameInfo = getGameInfo();
  tetromino->type = O;
  for (int row = SPAWN_Y; row < SPAWN_Y + 4; row++) {
    for (int col = SPAWN_X; col < SPAWN_X + 4; col++) {
      gameInfo->field[row][col] = Locked;
    }
  }
  *gameState = Spawning;
  updateCurrentState();
  ck_assert_int_eq(*gameState, Terminated);
}
END_TEST

START_TEST(test_updateCurrentState_locking) {
  GameState *gameState = getGameState();
  Tetromino *tetromino = getTetromino();
  GameInfo_t *gameInfo = getGameInfo();
  tetromino->type = I;
  tetromino->x = SPAWN_X;
  int last_line = 19;
  tetromino->y = last_line;

  gameInfo->field[last_line][0] = Locked;
  gameInfo->field[last_line][1] = Locked;
  gameInfo->field[last_line][2] = Locked;

  gameInfo->field[last_line][7] = Locked;
  gameInfo->field[last_line][8] = Locked;
  gameInfo->field[last_line][9] = Locked;

  spawnTetromino(tetromino);
  ck_assert_int_eq(getByte(StateByte, gameInfo->field[last_line][SPAWN_X - 2]),
                   Moving);
  ck_assert_int_eq(getByte(StateByte, gameInfo->field[last_line][SPAWN_X - 1]),
                   Moving);
  ck_assert_int_eq(getByte(StateByte, gameInfo->field[last_line][SPAWN_X]),
                   Moving);
  ck_assert_int_eq(getByte(StateByte, gameInfo->field[last_line][SPAWN_X + 1]),
                   Moving);

  *gameState = Locking;
  updateCurrentState();

  for (int col = 0; col < FIELD_WIDTH; col++) {
    ck_assert_int_eq(getByte(StateByte, gameInfo->field[last_line][col]),
                     Empty);
  }

  ck_assert_int_eq(*gameState, Spawning);
}
END_TEST

Suite *update_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("updateCurrentState");
  tc = tcase_create("updateCurrentState");
  tcase_add_checked_fixture(tc, setup_tetromino, teardown);
  tcase_add_test(tc, test_updateCurrentState_falling);
  tcase_add_test(tc, test_updateCurrentState_rotating);
  tcase_add_test(tc, test_updateCurrentState_paused);
  tcase_add_test(tc, test_updateCurrentState_spawning_no_collision);
  tcase_add_test(tc, test_updateCurrentState_spawning_collision);
  tcase_add_test(tc, test_updateCurrentState_locking);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(test_clearLines_1) {
  GameInfo_t *gameInfo = getGameInfo();
  int last_line = 19;
  for (int col = 0; col < FIELD_WIDTH; col++) {
    gameInfo->field[last_line][col] = Locked;
  }

  LineClearInfo lines = checkLineClear();
  ck_assert_int_eq(lines.num_cleared, 1);
  ck_assert_int_eq(lines.indeces[0], last_line);

  clearLines(lines);

  ck_assert_int_eq(gameInfo->score, 100);
  for (int col = 0; col < FIELD_WIDTH; col++) {
    ck_assert_int_eq(gameInfo->field[last_line][col], Empty);
  }
}
END_TEST

START_TEST(test_clearLines_2) {
  GameInfo_t *gameInfo = getGameInfo();
  int last_line = 19;
  for (int row = last_line - 1; row < FIELD_HEIGHT; row++) {
    for (int col = 0; col < FIELD_WIDTH; col++) {
      gameInfo->field[row][col] = Locked;
    }
  }

  LineClearInfo lines = checkLineClear();
  ck_assert_int_eq(lines.num_cleared, 2);
  ck_assert_int_eq(lines.indeces[0], last_line - 1);
  ck_assert_int_eq(lines.indeces[1], last_line);

  clearLines(lines);

  ck_assert_int_eq(gameInfo->score, 300);
  for (int row = 0; row < FIELD_HEIGHT; row++) {
    for (int col = 0; col < FIELD_WIDTH; col++) {
      ck_assert_int_eq(gameInfo->field[row][col], Empty);
    }
  }
}
END_TEST

START_TEST(test_clearLines_3) {
  GameInfo_t *gameInfo = getGameInfo();
  int last_line = 19;
  for (int row = last_line - 2; row < FIELD_HEIGHT; row++) {
    for (int col = 0; col < FIELD_WIDTH; col++) {
      gameInfo->field[row][col] = Locked;
    }
  }

  LineClearInfo lines = checkLineClear();
  ck_assert_int_eq(lines.num_cleared, 3);
  ck_assert_int_eq(lines.indeces[0], last_line - 2);
  ck_assert_int_eq(lines.indeces[1], last_line - 1);
  ck_assert_int_eq(lines.indeces[2], last_line);

  clearLines(lines);

  ck_assert_int_eq(gameInfo->score, 700);
  ck_assert_int_eq(gameInfo->level, 2);
  for (int row = 0; row < FIELD_HEIGHT; row++) {
    for (int col = 0; col < FIELD_WIDTH; col++) {
      ck_assert_int_eq(gameInfo->field[row][col], Empty);
    }
  }
}
END_TEST

START_TEST(test_clearLines_4) {
  GameInfo_t *gameInfo = getGameInfo();
  int last_line = 19;
  for (int row = last_line - 3; row < FIELD_HEIGHT; row++) {
    for (int col = 0; col < FIELD_WIDTH; col++) {
      gameInfo->field[row][col] = Locked;
    }
  }

  LineClearInfo lines = checkLineClear();
  ck_assert_int_eq(lines.num_cleared, 4);
  ck_assert_int_eq(lines.indeces[0], last_line - 3);
  ck_assert_int_eq(lines.indeces[1], last_line - 2);
  ck_assert_int_eq(lines.indeces[2], last_line - 1);
  ck_assert_int_eq(lines.indeces[3], last_line);

  clearLines(lines);

  ck_assert_int_eq(gameInfo->score, 1500);
  ck_assert_int_eq(gameInfo->level, 3);
  for (int row = 0; row < FIELD_HEIGHT; row++) {
    for (int col = 0; col < FIELD_WIDTH; col++) {
      ck_assert_int_eq(gameInfo->field[row][col], Empty);
    }
  }
}
END_TEST

START_TEST(test_clearLines_2_in_game) {
  GameInfo_t *gameInfo = getGameInfo();

  int x_hole = 5;
  int last_line = 19;
  for (int row = last_line - 1; row < FIELD_HEIGHT; row++) {
    for (int col = 0; col < FIELD_WIDTH; col++) {
      if (col != x_hole) {
        gameInfo->field[row][col] = Locked;
      }
    }
  }

  Tetromino *tetromino = getTetromino();
  tetromino->type = I;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  tetromino->x = x_hole;
  tetromino->y = last_line - 3;

  GameState *gameState = getGameState();
  *gameState = Idle;
  spawnTetromino(tetromino);
  userInput(Action, false);
  ck_assert_int_eq(*gameState, Rotating);
  updateCurrentState();
  ck_assert_int_eq(*gameState, Idle);

  for (int i = 0; i < 2; i++) {
    userInput(Down, false);
    ck_assert_int_eq(*gameState, Falling);
    updateCurrentState();
    ck_assert_int_eq(*gameState, Idle);
  }

  userInput(Down, false);
  ck_assert_int_eq(*gameState, Locking);
  updateCurrentState();
  ck_assert_int_eq(*gameState, Spawning);

  for (int row = last_line - 1; row < FIELD_HEIGHT; row++) {
    for (int col = 0; col < FIELD_WIDTH; col++) {
      if (col != x_hole) {
        ck_assert_int_eq(getByte(StateByte, gameInfo->field[row][col]), Empty);
      } else {
        ck_assert_int_eq(getByte(StateByte, gameInfo->field[row][col]), Locked);
      }
    }
  }

  // for (int i = 0; i < FIELD_HEIGHT; i++) {
  //   for (int j = 0; j < FIELD_WIDTH; j++) {
  //     printf("%d ", getByte(StateByte, gameInfo->field[i][j]));
  //   }
  //   printf("\n");
  // }
}

START_TEST(test_clearLines_4_in_game) {
  GameInfo_t *gameInfo = getGameInfo();
  int last_line = 19;
  int x_hole = 5;

  for (int row = last_line - 3; row < FIELD_HEIGHT; row++) {
    for (int col = 0; col < FIELD_WIDTH; col++) {
      if (col != x_hole) {
        gameInfo->field[row][col] = Locked;
      }
    }
  }

  Tetromino *tetromino = getTetromino();
  tetromino->type = I;
  tetromino->number_of_states = STATES_COUNT[tetromino->type];
  tetromino->x = 5;
  tetromino->y = last_line - 5;

  GameState *gameState = getGameState();
  *gameState = Idle;
  spawnTetromino(tetromino);

  userInput(Action, false);
  ck_assert_int_eq(*gameState, Rotating);
  updateCurrentState();
  ck_assert_int_eq(*gameState, Idle);

  for (int i = 0; i < 4; i++) {
    userInput(Down, false);
    ck_assert_int_eq(*gameState, Falling);
    updateCurrentState();
  }

  userInput(Down, false);
  ck_assert_int_eq(*gameState, Locking);
  updateCurrentState();
  ck_assert_int_eq(*gameState, Spawning);
  updateCurrentState();

  // for (int i = 0; i < FIELD_HEIGHT; i++) {
  //   for (int j = 0; j < FIELD_WIDTH; j++) {
  //     printf("%d ", getByte(StateByte, gameInfo->field[i][j]));
  //   }
  //   printf("\n");
  // }

  for (int row = last_line - 3; row < FIELD_HEIGHT; row++) {
    for (int col = 0; col < FIELD_WIDTH; col++) {
      ck_assert_int_eq(getByte(StateByte, gameInfo->field[row][col]), Empty);
    }
  }
}

Suite *clearLine_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("clearLines");
  tc = tcase_create("clearLines");
  tcase_add_checked_fixture(tc, setup_tetromino, teardown);
  tcase_add_test(tc, test_clearLines_1);
  tcase_add_test(tc, test_clearLines_2);
  tcase_add_test(tc, test_clearLines_3);
  tcase_add_test(tc, test_clearLines_4);

  tcase_add_test(tc, test_clearLines_2_in_game);
  tcase_add_test(tc, test_clearLines_4_in_game);
  suite_add_tcase(s, tc);
  return s;
}