#include "./tetris.h"

int main() {
  initscr();
  input_field();

  srandom(time(NULL));
  struct GameInfo_t gameinf = {0};
  struct piece cur_fig = {0};
  gameinf.current = &cur_fig;
  State state = START;

  while (state != EXIT) {
    UserAction_t act = get_signal(getch());
    sigact(act, &state, &gameinf);

    if (state == START) start_win();

    if (state == MOVING) {
      print_shapes(&gameinf);
      print_field(&gameinf);
      print_next_f(&gameinf);
    }

    if (state == PAUSE) pause_win();
  }

  endwin();
  return 0;
}

UserAction_t get_signal(chtype user_input) {
  UserAction_t uact = Nosig;

  if (user_input == KEY_UP) {
    uact = Spin;
  } else if (user_input == KEY_DOWN) {
    uact = Down;
  } else if (user_input == KEY_RIGHT) {
    uact = Right;
  } else if (user_input == KEY_LEFT) {
    uact = Left;
  } else if (user_input == ENTER) {
    uact = Enter;
  } else if (user_input == ESC) {
    uact = Terminate;
  } else if (user_input == KEY_ENTER) {
    uact = Enter;
  } else {
    uact = Nosig;
  }
  return uact;
}

void sigact(UserAction_t uact, State *state, GameInfo_t *gameinf) {
  switch (*state) {
    case START:
      hiscore_show(gameinf);
      if (uact == Nosig) {
        start_win();
      } else if (uact == Enter) {
        *state = MOVING;
        random_f(gameinf);
        random_next_f(gameinf);
      } else if (uact == Terminate) {
        *state = EXIT;
      }
      break;

    case MOVING:

      if (uact == Left) {
        left(gameinf);
      } else if (uact == Right) {
        right(gameinf);
      } else if (uact == Spin) {
        turn_shapes(gameinf);
      } else if (uact == Down) {
        down(gameinf);
      } else if (uact == Terminate) {
        *state = EXIT;
      } else if (uact == Pause) {
        *state = PAUSE;
      }
      down(gameinf);
      if (completion(gameinf)) *state = GAMEOVER;
      if (crash(gameinf)) {
      }
      check_line(gameinf);
      break;

    case PAUSE:
      pause_win();
      if (uact == Terminate) {
        *state = EXIT;
      }
      if (uact == Pause) {
        *state = MOVING;
      }
      break;
    case GAMEOVER:
      wattron(stdscr, COLOR_PAIR(1));
      mvwprintw(stdscr, 9, 10, "GAME OVER");
      wattroff(stdscr, COLOR_PAIR(1));
      hiscore_save(gameinf);
      clear_field(gameinf);
      if (uact == Enter) {
        *state = START;
      }
      if (uact == Terminate) {
        *state = EXIT;
      }
      break;
    case EXIT:

      break;
  }
}
