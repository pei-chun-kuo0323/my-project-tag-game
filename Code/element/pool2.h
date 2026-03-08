#ifndef POOL2_H_INCLUDED
#define POOL2_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [rod_up object]
*/
typedef struct _Pool2
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Pool2;

Elements *New_Pool2(int label);
void Pool2_update(Elements *self);
void Pool2_interact(Elements *self, Elements *target);
void Pool2_draw(Elements *self);
void Pool2_destroy(Elements *self);

#endif
