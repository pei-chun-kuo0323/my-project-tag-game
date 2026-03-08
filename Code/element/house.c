#include "house.h"

Elements *New_House(int label){
    House *pDerivedObj = (House *)malloc(sizeof(House));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/house.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 3500;
    pDerivedObj->y = 1500;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2,
                                        pDerivedObj->y-pDerivedObj->height/2,
                                        pDerivedObj->x+pDerivedObj->width/2,
                                        pDerivedObj->y+pDerivedObj->height/2);

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = House_update;
    pObj->Interact = House_interact;
    pObj->Draw = House_draw;
    pObj->Destroy = House_destroy;
    return pObj;
}
void House_update(Elements *self){
}
void House_interact(Elements *self, Elements *tar){
    
}
void House_draw(Elements *self){

}
void House_destroy(Elements *self){
    House *Obj = ((House *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}