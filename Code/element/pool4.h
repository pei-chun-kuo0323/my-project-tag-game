#ifndef POOL4_H_INCLUDED
#define POOL4_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [rod_up object]
*/
typedef struct _Pool4
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Pool4;

Elements *New_Pool4(int label);
void Pool4_update(Elements *self);
void Pool4_interact(Elements *self, Elements *target);
void Pool4_draw(Elements *self);
void Pool4_destroy(Elements *self);

#endif
