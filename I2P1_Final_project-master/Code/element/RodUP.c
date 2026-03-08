#include "RodUP.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
/*
   [RodUP function]
*/
Elements *New_RodUP(int label)
{
    RodUP *pDerivedObj = (RodUP *)malloc(sizeof(RodUP));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/RodUP.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 100;
    pDerivedObj->y = 100;
    pDerivedObj->hitbox = 

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = RodUP_update;
    pObj->Interact = RodUP_interact;
    pObj->Draw = RodUP_draw;
    pObj->Destroy = RodUP_destroy;
    return pObj;
}
void RodUP_update(Elements *self) {}
void RodUP_interact(Elements *self, Elements *tar) {}
void RodUP_draw(Elements *self)
{
    RodUP *Obj = ((RodUP *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void RodUP_destroy(Elements *self)
{
    RodUP *Obj = ((RodUP *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
