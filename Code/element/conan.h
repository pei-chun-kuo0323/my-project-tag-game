#ifndef CONAN_H_INCLUDED
#define CONAN_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include "player1.h"

/*
   [rod_down object]
*/
typedef struct _Conan
{
    ALLEGRO_BITMAP *img[4][4];

} Conan;

Elements *New_Conan(int label);
void Conan_update(Elements *self);
void Conan_interact(Elements *self, Elements *tar);
void Conan_draw(Elements *self);
void Conan_destroy(Elements *self);

#endif
