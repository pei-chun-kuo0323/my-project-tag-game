#ifndef HOUSE_H_INCLUDED
#define HOUSE_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [rod_up object]
*/
typedef struct _House
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} House;

Elements *New_House(int label);
void House_update(Elements *self);
void House_interact(Elements *self, Elements *tar);
void House_draw(Elements *self);
void House_destroy(Elements *self);

#endif
