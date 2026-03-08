#include "RodDOWN.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
/*
   [RodDOWN function]
*/
Elements *New_RodDOWN(int label)
{
    RodDOWN *pDerivedObj = (RodDOWN *)malloc(sizeof(RodDOWN));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/RodDOWN.png");
    pDerivedObj->width = 900;
    pDerivedObj->height = 672;
    pDerivedObj->x = 100;
    pDerivedObj->y = 100;
    pDerivedObj->hitbox = 

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = RodDOWN_update;
    pObj->Interact = RodDOWN_interact;
    pObj->Draw = RodDOWN_draw;
    pObj->Destroy = RodDOWN_destroy;
    return pObj;
}
void RodDOWN_update(Elements *self) {}
void RodDOWN_interact(Elements *self, Elements *tar) {}
void RodDOWN_draw(Elements *self)
{
    RodDOWN *Obj = ((RodDOWN *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void RodDOWN_destroy(Elements *self)
{
    RodDOWN *Obj = ((RodDOWN *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
