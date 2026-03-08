#include "wood1.h"

Elements *New_Wood1(int label){
    Wood1 *pDerivedObj = (Wood1 *)malloc(sizeof(Wood1));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/wood.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 2048;
    pDerivedObj->y = 100;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2,
                                        pDerivedObj->y-pDerivedObj->height/2,
                                        pDerivedObj->x+pDerivedObj->width/2,
                                        pDerivedObj->y+pDerivedObj->height/2);

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Wood1_update;
    pObj->Interact = Wood1_interact;
    pObj->Draw = Wood1_draw;
    pObj->Destroy = Wood1_destroy;
    return pObj;
}
void Wood1_update(Elements *self){
}
void Wood1_interact(Elements *self, Elements *tar){
    
}
void Wood1_draw(Elements *self){

}
void Wood1_destroy(Elements *self){
    Wood1 *Obj = ((Wood1 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}