#include "pool5.h"

Elements *New_Pool5(int label){
    Pool5 *pDerivedObj = (Pool5 *)malloc(sizeof(Pool5));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/Pool5.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 3900;
    pDerivedObj->y = 1850;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2+50,
                                        pDerivedObj->y-pDerivedObj->height/2+50,
                                        pDerivedObj->x+pDerivedObj->width/2-50,
                                        pDerivedObj->y+pDerivedObj->height/2-50);

    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Player1_L;
    pObj->inter_obj[pObj->inter_len++] = Player2_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Pool5_update;
    pObj->Interact = Pool5_interact;
    pObj->Draw = Pool5_draw;
    pObj->Destroy = Pool5_destroy;
    return pObj;
}
void Pool5_update(Elements *self){




}
void Pool5_interact(Elements *self, Elements *target){
    Pool5 *Obj = ((Pool5 *)(self->pDerivedObj));
    if (target->label == Player1_L)
    {
        Player1 *Obj2 = ((Player1 *)(target->pDerivedObj));

        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox))
        {
            if(Obj2->slow == false)
            {
                Obj2->speed /= 2;
                Obj2->slow = true;
                Obj2->in = Pool5_L;
            }
        }
        else{
            if(Obj2->in == Pool5_L){
                if(Obj2->slow == true){
                    Obj2->speed *= 2;
                    Obj2->slow = false;
                    Obj2->in = -1;
                }
            }
            
        }  
    }
    if (target->label == Player2_L)
    {
        Player2 *Obj2 = ((Player2 *)(target->pDerivedObj));

        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox))
        {
            if(Obj2->slow == false)
            {
                Obj2->speed /= 2;
                Obj2->slow = true;
                Obj2->in = Pool5_L;
            }
        }
        else{
            if(Obj2->in == Pool5_L){
                if(Obj2->slow == true){
                    Obj2->speed *= 2;
                    Obj2->slow = false;
                    Obj2->in = -1;
                }
            }
        }  
    }
}
void Pool5_draw(Elements *self){

}
void Pool5_destroy(Elements *self){
    Pool5 *Obj = ((Pool5 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}