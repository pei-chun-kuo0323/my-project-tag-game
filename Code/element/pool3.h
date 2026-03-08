#ifndef POOL3_H_INCLUDED
#define POOL3_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [rod_up object]
*/
typedef struct _Pool3
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Pool3;

Elements *New_Pool3(int label);
void Pool3_update(Elements *self);
void Pool3_interact(Elements *self, Elements *target);
void Pool3_draw(Elements *self);
void Pool3_destroy(Elements *self);

#endif
