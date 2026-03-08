#ifndef WOOD2_H_INCLUDED
#define WOOD2_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [rod_up object]
*/
typedef struct _Wood2
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Wood2;

Elements *New_Wood2(int label);
void Wood2_update(Elements *self);
void Wood2_interact(Elements *self, Elements *tar);
void Wood2_draw(Elements *self);
void Wood2_destroy(Elements *self);

#endif
