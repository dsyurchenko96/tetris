#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <check.h>

Suite *rotate_suite();
Suite *input_suite();
Suite *update_suite();
Suite *clearLine_suite();
Suite *timer_suite();

void setup_tetromino();
void teardown();

#endif