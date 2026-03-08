#ifndef WOOD1_H_INCLUDED
#define WOOD1_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [rod_up object]
*/
typedef struct _Wood1
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Wood1;

Elements *New_Wood1(int label);
void Wood1_update(Elements *self);
void Wood1_interact(Elements *self, Elements *tar);
void Wood1_draw(Elements *self);
void Wood1_destroy(Elements *self);

#endif
