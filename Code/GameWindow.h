#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED
#include <allegro5/allegro.h>
#include <stdbool.h>
// include allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

typedef struct _GAME Game;
typedef void (*fptrGameExecute)(Game *); //函數指針，當後方引用型態與回傳型態皆相同，則可套用(舉例如12行)
typedef void (*fptrGameInit)(Game *);
typedef bool (*fptrGameUpdate)(Game *);
typedef void (*fptrGameDraw)(Game *);
typedef void (*fptrGameDestroy)(Game *);
void execute(Game *); //後方型態為Game * ,回傳為void ,和上方fptGameExecute相同
void game_init(Game *);
bool game_update(Game *);
void game_draw(Game *);
void game_destroy(Game *);
struct _GAME
{
    const char *title;
    // ALLEGRO Variables
    ALLEGRO_DISPLAY *display; //ALLEGRO_DISPLAY為  (#include <allegro5/allegro.h>) 內的型別
    fptrGameExecute execute;
    fptrGameInit game_init;
    fptrGameUpdate game_update;
    fptrGameDraw game_draw;
    fptrGameDestroy game_destroy;
};
Game *New_Game();

#endif
