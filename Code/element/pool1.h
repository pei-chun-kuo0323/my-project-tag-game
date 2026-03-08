#ifndef POOL1_H_INCLUDED
#define POOL1_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [rod_up object]
*/
typedef struct _Pool1
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Pool1;

Elements *New_Pool1(int label);
void Pool1_update(Elements *self);
void Pool1_interact(Elements *self, Elements *target);
void Pool1_draw(Elements *self);
void Pool1_destroy(Elements *self);

#endif
