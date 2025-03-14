
#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
extern char shapes[7][4][4][4];
extern WINDOW *win1;
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define ESC 27
#define ENTER 10

typedef enum {
  Enter = 0,
  Pause,
  Terminate,
  Left,
  Right,
  Spin,
  Down,
  Nosig
} UserAction_t;

typedef enum { START, MOVING, PAUSE, GAMEOVER, EXIT } State;

enum rotation {
  ROTATION_NORMAL,
  ROTATION_RIGHT,
  ROTATION_DOWN,
  ROTATION_LEFT,
};

typedef struct piece {
  enum rotation rotation;
  int figure;
  int pos_x;
  int pos_y;
} piece;

typedef struct GameInfo_t {
  int field[30][20];
  struct piece *current;
  struct piece next_f;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int check;
} GameInfo_t;

#include "../../gui/cli/front.h"
void start_game(GameInfo_t *gameinf);
UserAction_t get_signal(chtype user_input);
void sigact(UserAction_t uact, State *state, GameInfo_t *gameinf);
void input_signals(struct GameInfo_t *tetris);
void clear_field(struct GameInfo_t *tetris);
void print_shapes(struct GameInfo_t *tetris);
void remove_shapes(struct GameInfo_t *tetris);
void hiscore_show(struct GameInfo_t *tetris);
void hiscore_save(struct GameInfo_t *tetris);
void turn_shapes(struct GameInfo_t *tetris);
void random_f(struct GameInfo_t *tetris);
void random_next_f(struct GameInfo_t *tetris);
void check_line(struct GameInfo_t *tetris);
void remove_line(struct GameInfo_t *tetris, int row);
int completion(struct GameInfo_t *tetris);
void left(struct GameInfo_t *tetris);
void right(struct GameInfo_t *tetris);
void down(struct GameInfo_t *tetris);
int crash(GameInfo_t *);

#endif
