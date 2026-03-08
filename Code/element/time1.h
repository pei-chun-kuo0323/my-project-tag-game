#ifndef TIME1_H_INCLUDED
#define TIME1_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include "player1.h"
/*
   [Time object]
*/
typedef struct _Time1
{
    int x, y;          // the position of image
    int size; // the width and height of image
    ALLEGRO_FONT *font;
    double elapsed_time;
    bool start;
    double crown_catch_start_time;
} Time1;

Elements *New_Time1(int label);
void Time1_update(Elements *self);
void Time1_interact(Elements *self, Elements *tar);
void Time1_draw(Elements *self);

void Time1_destroy(Elements *self);

#endif
