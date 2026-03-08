#ifndef CROWN_H_INCLUDED
#define CROWN_H_INCLUDED
#include "../shapes/Shape.h"
#include "element.h"
#include "../algif5/src/algif.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdbool.h>
#include "../scene/gamescene.h"
#include "player2.h"
#include "player1.h"

typedef struct _Crown
{
    int x, y;
    int width[2], height[2];
    ALLEGRO_BITMAP *img;
    Shape *hitbox;
    bool touch ;

} Crown;

Elements *New_Crown(int label);
void Crown_update(Elements *self);
void Crown_interact(Elements *self, Elements *target);
void Crown_draw(Elements *self);
void Crown_destroy(Elements *self);

#endif