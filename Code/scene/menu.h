#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "gamescene.h"
/*
   [Menu object]
*/
typedef struct _Button
{   
    ALLEGRO_BITMAP *img[2];
    double x, y;
    int state;
} Button;
typedef struct _Menu
{
    int x[6],y[6];
    ALLEGRO_BITMAP *img[6] ,*choose_Robot[2];
    ALLEGRO_SAMPLE *song[3];
    ALLEGRO_SAMPLE_INSTANCE *sample_instance[3];
    // Shape *hitbox;
    // bool start,save0,save1;
    // int title_x, title_y;
} Menu;
Scene *New_Menu(int label);
void menu_update(Scene *self);
void menu_draw(Scene *self);
void menu_destroy(Scene *self);
int sceneNow;
enum{ MENU = 0, ABOUTUS, STORY, TEACH ,BONUS,MODE,CHOOSE_CHARACTER,SETTING,PROCESS};
#endif
