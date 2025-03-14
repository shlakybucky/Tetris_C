#include "./shapes.h"
#include "./tetris.h"

void clear_field(struct GameInfo_t *gameinf) {
  for (int y = 0; y < 20; y++) {
    for (int x = 0; x < 10; x++) {
      gameinf->field[y][x] = 0;
    }
  }
}

void print_shapes(struct GameInfo_t *gameinf) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (shapes[gameinf->current->figure][gameinf->current->rotation][y][x]) {
        gameinf
            ->field[gameinf->current->pos_y + y][gameinf->current->pos_x + x] =
            shapes[gameinf->current->figure][gameinf->current->rotation][y][x];
      }
    }
  }
  wrefresh(win1);
}

void remove_shapes(struct GameInfo_t *gameinf) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (shapes[gameinf->current->figure][gameinf->current->rotation][y][x])
        gameinf
            ->field[gameinf->current->pos_y + y][gameinf->current->pos_x + x] =
            0;
    }
  }
}

int crash(struct GameInfo_t *gameinf) {
  int check = 0;
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (shapes[gameinf->current->figure][gameinf->current->rotation][y][x] &&
          ((gameinf->current->pos_y + y > 19) ||
           (gameinf->current->pos_x + x < 0) ||
           (gameinf->current->pos_x + x > 9) ||
           (gameinf->field[gameinf->current->pos_y + y]
                          [gameinf->current->pos_x + x]))) {
        check = 1;
      }
    }
  }
  return check;
}

void turn_shapes(struct GameInfo_t *gameinf) {
  remove_shapes(gameinf);
  if (gameinf->current->rotation == 3) {
    gameinf->current->rotation = 0;
  } else {
    gameinf->current->rotation += 1;
  }
  if (!crash(gameinf)) {
    print_shapes(gameinf);
  } else {
    if (gameinf->current->rotation == 0) {
      gameinf->current->rotation = 3;
    } else {
      gameinf->current->rotation -= 1;
    }
    remove_shapes(gameinf);
  }
}

void check_line(struct GameInfo_t *gameinf) {
  int remove_counter = 0;
  for (int y = 20; y >= 0; y--) {
    int check = 0;
    for (int x = 0; x < 10; x++) {
      if (gameinf->field[y][x]) {
        check++;
      }
    }
    if (check == 10) {
      remove_line(gameinf, y);
      y++;
      remove_counter++;
    }
  }
  if (remove_counter == 1) {
    gameinf->score += 100;
  } else if (remove_counter == 2) {
    gameinf->score += 300;
  } else if (remove_counter == 3) {
    gameinf->score += 700;
  } else if (remove_counter == 4) {
    gameinf->score += 1500;
  }
  mvprintw(7, 31, "%04d", gameinf->score);

  if (gameinf->score > 600 * (gameinf->level + 1) && gameinf->level < 10) {
    gameinf->level++;
    timeout(1000 - 100 * gameinf->level);
  }
  mvprintw(11, 31, "%02d", gameinf->level);
  mvprintw(15, 31, "%02d", gameinf->level);
  mvprintw(3, 31, "%04d", gameinf->high_score);
}

void remove_line(struct GameInfo_t *gameinf, int row) {
  for (int y = row; y > 0; y--) {
    for (int x = 0; x < 10; x++) {
      gameinf->field[y][x] = gameinf->field[y - 1][x];
    }
  }
  //  for (int x = 0; x < 10; x++) {
  //    gameinf->field[0][x] = 0;
  //  }
}

void hiscore_show(struct GameInfo_t *gameinf) {
  FILE *file = fopen("score.txt", "r");
  char str[6];
  if (file != NULL) {
    fgets(str, 6, file);
    gameinf->high_score = atoi(str);
    fclose(file);
  }
}

void hiscore_save(struct GameInfo_t *gameinf) {
  if (gameinf->score > gameinf->high_score) {
    FILE *file = fopen("score.txt", "w");
    char str[6];
    if (file != NULL) {
      sprintf(str, "%d", gameinf->score);
      fputs(str, file);
      fclose(file);
    }
  }
}

void random_f(struct GameInfo_t *gameinf) {
  gameinf->current->figure = random() % 7;
  gameinf->current->rotation = ROTATION_NORMAL;
  gameinf->current->pos_x = 3;
  gameinf->current->pos_y = 2;
}

void random_next_f(struct GameInfo_t *gameinf) {
  gameinf->next_f.figure = random() % 7;
  gameinf->next_f.rotation = ROTATION_NORMAL;
  gameinf->next_f.pos_x = 3;
  gameinf->next_f.pos_y = 2;
}

int completion(struct GameInfo_t *gameinf) {
  int check = 0;
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (shapes[gameinf->current->figure][gameinf->current->rotation][y][x] &&
          (gameinf->field[gameinf->current->pos_y + y]
                         [gameinf->current->pos_x + x]) &&
          (gameinf->current->pos_y - y == 1)) {
        check = 1;
      }
    }
  }
  return check;
}

void left(GameInfo_t *gameinf) {
  remove_shapes(gameinf);
  gameinf->current->pos_x -= 1;
  if (!crash(gameinf)) {
    remove_shapes(gameinf);
    print_shapes(gameinf);
  } else {
    gameinf->current->pos_x += 1;
  }
}

void right(struct GameInfo_t *gameinf) {
  remove_shapes(gameinf);
  gameinf->current->pos_x += 1;
  if (!crash(gameinf)) {
    remove_shapes(gameinf);
    print_shapes(gameinf);
  } else {
    gameinf->current->pos_x -= 1;
  }
}

void down(struct GameInfo_t *gameinf) {
  remove_shapes(gameinf);
  gameinf->current->pos_y += 1;
  if (crash(gameinf)) {
    gameinf->current->pos_y -= 1;
    print_shapes(gameinf);
    *gameinf->current = gameinf->next_f;
    clear_next_f(gameinf);
    random_next_f(gameinf);
  }
}
