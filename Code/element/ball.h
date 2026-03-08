#ifndef Ball_H_INCLUDED
#define Ball_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include "crown.h"
/*
   [Ball object]
*/
typedef struct _Ball
{
    int x, y;          // the position of image
    int r; // the width and height of image
    int in;
    ALLEGRO_COLOR color;
    Shape *hitbox; // the hitbox of object
} Ball;
Elements *New_Ball(int label);
void Ball_update(Elements *self);
void Ball_interact(Elements *self, Elements *tar);
void Ball_draw(Elements *self);
void Ball_destory(Elements *self);

#endif
