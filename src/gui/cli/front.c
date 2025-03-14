#include "front.h"

#include "../../brick_game/tetris/tetris.h"

const chtype BLOCK = ' ' | A_REVERSE;
WINDOW *win1;

void print_back();

void print_field(struct GameInfo_t *gameinf) {
  print_back();

  for (int y = 0; y < 20; y++) {
    for (int x = 0; x < 10; x++) {
      if (gameinf->field[y][x]) {
        wattron(win1, COLOR_PAIR(gameinf->field[y][x]));
        mvwaddch(win1, y + 1, x * 2 + 1, BLOCK);
        mvwaddch(win1, y + 1, x * 2 + 2, BLOCK);
        wattroff(win1, COLOR_PAIR(gameinf->field[y][x]));
      } else {
        mvwaddch(win1, y + 1, x * 2 + 1, ' ');
        mvwaddch(win1, y + 1, x * 2 + 2, ' ');
      }
    }
  }
  wrefresh(win1);
}

void input_field() {
  use_default_colors();
  start_color();
  init_pair(1, COLOR_MAGENTA, -1);
  init_pair(2, COLOR_RED, -1);
  init_pair(3, COLOR_GREEN, -1);
  init_pair(4, COLOR_WHITE, -1);
  init_pair(5, COLOR_YELLOW, -1);
  init_pair(6, COLOR_CYAN, -1);
  init_pair(7, COLOR_BLUE, -1);
  init_color(COLOR_PURPLE, 200, 0, 300);
  init_pair(8, COLOR_WHITE, COLOR_PURPLE);
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, 1);
  nodelay(stdscr, 1);
  timeout(1000);

  win1 = subwin(stdscr, BOARD_HEIGHT + 2, BOARD_WIDTH * 2 + 2, 1, 2);
  wbkgd(win1, COLOR_PAIR(8));

  wresize(stdscr, 24, 42);
  print_back();

  box(win1, 0, 0);
  refresh();
}

void print_back() {
  mvwprintw(stdscr, 1, 30, "HISCORE");
  mvwprintw(stdscr, 5, 31, "SCORE");
  mvwprintw(stdscr, 9, 31, "LEVEL");
  mvwprintw(stdscr, 13, 31, "SPEED");
  mvwprintw(stdscr, 17, 31, "NEXT");
  box(stdscr, ACS_VLINE, ACS_HLINE);
  box(win1, ACS_VLINE, ACS_HLINE);
}

void print_next_f(struct GameInfo_t *gameinf) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (shapes[gameinf->next_f.figure][gameinf->next_f.rotation][y][x]) {
        wattron(stdscr, COLOR_PAIR(gameinf->field[y][x]));
        mvwaddch(stdscr, y + 18, x * 2 + 31, BLOCK);
        mvwaddch(stdscr, y + 18, x * 2 + 32, BLOCK);
        wattroff(stdscr, COLOR_PAIR(gameinf->field[y][x]));
      }
    }
  }
}

void clear_next_f(struct GameInfo_t *gameinf) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (shapes[gameinf->next_f.figure][gameinf->next_f.rotation][y][x]) {
        wattron(stdscr, COLOR_PAIR(gameinf->field[y][x]));
        mvwaddch(stdscr, y + 18, x * 2 + 31, ' ');
        mvwaddch(stdscr, y + 18, x * 2 + 32, ' ');
        wattroff(stdscr, COLOR_PAIR(gameinf->field[y][x]));
      }
    }
  }
}

void start_win() {
  box(win1, ACS_VLINE, ACS_HLINE);

  mvwprintw(stdscr, 11, 3, "PRESS ENTER TO START");

  refresh();
}

void pause_win() {
  WINDOW *pausew = newwin(30, 20, 0, 0);
  wbkgd(pausew, COLOR_PAIR(8));
  box(pausew, 0, 0);
  mvwprintw(pausew, 11, 11, "PAUSE");
  refresh();
}
