#include "global.h"
#include "shapes/Shape.h"
#include <stdbool.h>
// variables for global usage
const double FPS = 60.0;
const int WIDTH = 1920;
const int HEIGHT = 1080;
int window = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
Point mouse;
bool HoverOnItem=false;
bool debug_mode = true;
int bg_width = 4096;
int bg_height = 2304;
int player_1_width = 960;
int player_1_height = 1080;
int player_2_width = 960;
int player_2_height = 1080;
int player_1_win = false;
int player_2_win = false;
bool game_end = false;
// int player_1_chara = -1;
// int player_2_chara = -1;