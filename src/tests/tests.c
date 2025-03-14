#include "tests.h"

#include <check.h>

START_TEST(test_clear_field) {
  struct GameInfo_t tetris;

  for (int y = 0; y < 20; y++) {
    for (int x = 0; x < 10; x++) {
      tetris.field[y][x] = 1;
    }
  }

  clear_field(&tetris);

  for (int y = 0; y < 20; y++) {
    for (int x = 0; x < 10; x++) {
      fail_unless(tetris.field[y][x] == 0);
    }
  }
}
END_TEST

START_TEST(test_print_shapes) {
  struct GameInfo_t tetris;

  tetris.current.figure = 0;
  tetris.current.rotation = 0;
  tetris.current.pos_x = 5;
  tetris.current.pos_y = 2;

  print_shapes(&tetris);

  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (shapes[tetris.current.figure][tetris.current.rotation][y][x]) {
        fail_unless(
            tetris.field[tetris.current.pos_y + y][tetris.current.pos_x + x] ==
            shapes[tetris.current.figure][tetris.current.rotation][y][x]);
      }
    }
  }
}
END_TEST

START_TEST(test_remove_shapes) {
  struct GameInfo_t tetris;

  tetris.current.figure = 0;
  tetris.current.rotation = 0;
  tetris.current.pos_x = 5;
  tetris.current.pos_y = 2;

  for (int y = 0; y < 20; y++) {
    for (int x = 0; x < 10; x++) {
      tetris.field[y][x] = rand() % 2;
    }
  }

  remove_shapes(&tetris);

  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (shapes[tetris.current.figure][tetris.current.rotation][y][x]) {
        fail_unless(
            tetris.field[tetris.current.pos_y + y][tetris.current.pos_x + x] ==
            0);
      }
    }
  }
}
END_TEST

START_TEST(test_turn_shapes) {
  struct GameInfo_t tetris = {0};

  tetris.current.rotation = 0;

  turn_shapes(&tetris);

  fail_unless(tetris.current.rotation == 1);

  turn_shapes(&tetris);

  fail_unless(tetris.current.rotation == 2);

  turn_shapes(&tetris);

  fail_unless(tetris.current.rotation == 3);

  turn_shapes(&tetris);

  fail_unless(tetris.current.rotation == 0);
}
END_TEST

START_TEST(test_checl_line) {
  struct GameInfo_t tetris = {0};

  for (int x = 0; x < 10; x++) {
    tetris.field[15][x] = 1;
  }

  check_line(&tetris);

  fail_unless(tetris.field[15][0] == 0);

  for (int x = 0; x < 10; x++) {
    tetris.field[15][x] = 1;
    tetris.field[16][x] = 1;
  }

  check_line(&tetris);

  fail_unless(tetris.field[16][0] == 0);

  for (int x = 0; x < 10; x++) {
    tetris.field[15][x] = 1;
    tetris.field[16][x] = 1;
    tetris.field[17][x] = 1;
  }

  check_line(&tetris);

  fail_unless(tetris.field[17][0] == 0);

  for (int x = 0; x < 10; x++) {
    tetris.field[15][x] = 1;
    tetris.field[16][x] = 1;
    tetris.field[17][x] = 1;
    tetris.field[18][x] = 1;
  }

  check_line(&tetris);

  fail_unless(tetris.field[18][0] == 0);
}
END_TEST

START_TEST(test_hiscore_show) {
  struct GameInfo_t tetris = {0};

  hiscore_show(&tetris);
  tetris.high_score = 0;

  fail_unless(tetris.high_score == 0);
}
END_TEST

START_TEST(test_hiscore_save) {
  struct GameInfo_t tetris = {0};

  hiscore_save(&tetris);
  tetris.high_score = 0;

  fail_unless(tetris.high_score == 0);
}
END_TEST

START_TEST(test_completion) {
  struct GameInfo_t tetris;

  for (int y = 0; y < 20; ++y) {
    for (int x = 0; x < 10; ++x) {
      tetris.field[y][x] = 0;
    }
  }
  tetris.current.figure = 0;
  tetris.current.rotation = 0;
  tetris.current.pos_x = 5;
  tetris.current.pos_y = 2;

  tetris.field[3][5] = 1;

  fail_unless(completion(&tetris) == 1);
}
END_TEST

START_TEST(test_left) {
  struct GameInfo_t tetris = {0};

  tetris.current.pos_x = 5;

  left(&tetris);

  fail_unless(tetris.current.pos_x == 4);

  left(&tetris);

  fail_unless(tetris.current.pos_x == 3);
}
END_TEST

START_TEST(test_right) {
  struct GameInfo_t tetris = {0};
  random_f(&tetris);
  random_next_f(&tetris);

  tetris.current.pos_x = 4;

  right(&tetris);

  fail_unless(tetris.current.pos_x == 5);

  right(&tetris);

  fail_unless(tetris.current.pos_x == 6);
}
END_TEST

START_TEST(test_down) {
  struct GameInfo_t tetris = {0};

  tetris.current.pos_y = 5;
  tetris.current.pos_x = 5;

  down(&tetris);

  fail_unless(tetris.current.pos_y == 6);

  tetris.field[7][5] = 1;
  down(&tetris);

  fail_unless(tetris.current.pos_y == 7);
}
END_TEST

int main(void) {
  Suite *s = suite_create("\033[45m-=S21_GAME_TEST=-\033[0m");
  TCase *tc;

  tc = tcase_create("s21_game");
  tcase_add_test(tc, test_clear_field);
  tcase_add_test(tc, test_print_shapes);
  tcase_add_test(tc, test_remove_shapes);
  tcase_add_test(tc, test_turn_shapes);
  tcase_add_test(tc, test_checl_line);
  tcase_add_test(tc, test_hiscore_show);
  tcase_add_test(tc, test_hiscore_save);
  tcase_add_test(tc, test_completion);
  tcase_add_test(tc, test_left);
  tcase_add_test(tc, test_right);
  tcase_add_test(tc, test_down);
  suite_add_tcase(s, tc);

  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  int fail = 0;
  fail = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
