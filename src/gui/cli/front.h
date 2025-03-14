
#ifndef FRONT_H
#define FRONT_H
#include "../../brick_game/tetris/tetris.h"

#define COLOR_PURPLE 245

void print_field(struct GameInfo_t *gameinf);
void input_field();
void print_next_f(struct GameInfo_t *gameinf);
void clear_next_f(struct GameInfo_t *gameinf);
void start_win();
void pause_win();

#endif
