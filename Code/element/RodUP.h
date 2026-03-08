#ifndef ROD_UP_H_INCLUDED
#define ROD_UP_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [rod_up object]
*/
typedef struct _RodUP
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} RodUP;

Elements *New_RodUP(int label);
void RodUP_update(Elements *self);
void RodUP_interact(Elements *self, Elements *tar);
void RodUP_draw(Elements *self);
void RodUP_destroy(Elements *self);

#endif
