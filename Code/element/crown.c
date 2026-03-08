#include "crown.h"

Elements *New_Crown(int label){
    Crown *pDerivedObj = (Crown *)malloc(sizeof(Crown));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->x = 2048;
    pDerivedObj->y = 1152;
    pDerivedObj->img = al_load_bitmap("assets/image/crown.png");
    pDerivedObj->width[0] = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height[0] = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->width[1] = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height[1] = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->touch = false;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width[0]/2,
                                        pDerivedObj->y-pDerivedObj->height[0]/2,
                                        pDerivedObj->x+pDerivedObj->width[0]/2,
                                        pDerivedObj->y+pDerivedObj->height[0]/2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Player1_L;
    pObj->inter_obj[pObj->inter_len++] = Player2_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Crown_update;
    pObj->Interact = Crown_interact;
    pObj->Draw = Crown_draw;
    pObj->Destroy = Crown_destroy;
    return pObj;
}
void Crown_update(Elements *self){

}
void Crown_interact(Elements *self, Elements *target){
    Crown *Obj = ((Crown *)(self->pDerivedObj));
    if (target->label == Player1_L)
    {
        Player1 *Obj2 = ((Player1 *)(target->pDerivedObj));
        if(!Obj->touch){
                if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox))
            {
                Obj->touch = true;
                Obj2->crown_catch = true;
            }  
        }
         
    }
    if (target->label == Player2_L)
    {
        Player2 *Obj2 = ((Player2 *)(target->pDerivedObj));

        if(!Obj->touch){
            if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox))
            {
                Obj->touch = true;
                Obj2->crown_catch = true;
            }
        }else{
            Obj2->robot_crown_catch = true;
        }
           
    }
}
void Crown_draw(Elements *self){
}
void Crown_destroy(Elements *self){
    Crown *Obj = ((Crown *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}