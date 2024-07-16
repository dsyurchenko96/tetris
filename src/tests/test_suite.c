#include "test_suite.h"

#include <check.h>
#include <stdio.h>

#include "../tetris.h"

int main(void) {
  int failed = 0;
  Suite *tetris_test[] = {input_suite(), rotate_suite(), update_suite(),
                          clearLine_suite(), NULL};

  for (int i = 0; tetris_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(tetris_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}

void setup_tetromino(void) {
  initGame();
  Tetromino *tetromino = getTetromino();
  tetromino->x = SPAWN_X;
  tetromino->y = SPAWN_Y;
  tetromino->state = 0;
}

void teardown(void) { destroyGame(); }