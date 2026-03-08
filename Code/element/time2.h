#ifndef TIME2_H_INCLUDED
#define TIME2_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

/*
   [Time object]
*/
typedef struct _Time2
{
    int x, y;          // the position of image
    int size; // the width and height of image
    ALLEGRO_FONT *font;
    double elapsed_time;
    bool start;
    double crown_catch_start_time;
} Time2;

Elements *New_Time2(int label);
void Time2_update(Elements *self);
void Time2_interact(Elements *self, Elements *tar);
void Time2_draw(Elements *self);

void Time2_destroy(Elements *self);

#endif
