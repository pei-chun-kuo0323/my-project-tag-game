#ifndef ROD_DOWN_H_INCLUDED
#define ROD_DOWN_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"

/*
   [rod_down object]
*/
typedef struct _RodDOWN
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} RodDOWN;

Elements *New_RodDOWN(int label);
void RodDOWN_update(Elements *self);
void RodDOWN_interact(Elements *self, Elements *tar);
void RodDOWN_draw(Elements *self);
void RodDOWN_destroy(Elements *self);

#endif
