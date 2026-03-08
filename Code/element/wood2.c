#include "wood2.h"

Elements *New_Wood2(int label){
    Wood2 *pDerivedObj = (Wood2 *)malloc(sizeof(Wood2));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/wood.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 3500;
    pDerivedObj->y = 900;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2,
                                        pDerivedObj->y-pDerivedObj->height/2,
                                        pDerivedObj->x+pDerivedObj->width/2,
                                        pDerivedObj->y+pDerivedObj->height/2);

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Wood2_update;
    pObj->Interact = Wood2_interact;
    pObj->Draw = Wood2_draw;
    pObj->Destroy = Wood2_destroy;
    return pObj;
}
void Wood2_update(Elements *self){
}
void Wood2_interact(Elements *self, Elements *tar){
    
}
void Wood2_draw(Elements *self){

}
void Wood2_destroy(Elements *self){
    Wood2 *Obj = ((Wood2 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}