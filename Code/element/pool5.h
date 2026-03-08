#ifndef POOL5_H_INCLUDED
#define POOL5_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [rod_up object]
*/
typedef struct _Pool5
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Pool5;

Elements *New_Pool5(int label);
void Pool5_update(Elements *self);
void Pool5_interact(Elements *self, Elements *target);
void Pool5_draw(Elements *self);
void Pool5_destroy(Elements *self);

#endif
