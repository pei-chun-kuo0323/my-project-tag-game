#include "pool2.h"

Elements *New_Pool2(int label){
    Pool2 *pDerivedObj = (Pool2 *)malloc(sizeof(Pool2));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/Pool2.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 1780;
    pDerivedObj->y = 900;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2+50,
                                        pDerivedObj->y-pDerivedObj->height/2+50,
                                        pDerivedObj->x+pDerivedObj->width/2-50,
                                        pDerivedObj->y+pDerivedObj->height/2-50);

    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Player1_L;
    pObj->inter_obj[pObj->inter_len++] = Player2_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Pool2_update;
    pObj->Interact = Pool2_interact;
    pObj->Draw = Pool2_draw;
    pObj->Destroy = Pool2_destroy;
    return pObj;
}
void Pool2_update(Elements *self){




}
void Pool2_interact(Elements *self, Elements *target){
    Pool2 *Obj = ((Pool2 *)(self->pDerivedObj));
    if (target->label == Player1_L)
    {
        Player1 *Obj2 = ((Player1 *)(target->pDerivedObj));

        
        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox))
        {
            if(Obj2->slow == false)
            {
                Obj2->speed /= 2;
                Obj2->slow = true;
                Obj2->in = Pool2_L;
            }
        }
        else{
            if(Obj2->in == Pool2_L){
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
                Obj2->in = Pool2_L;
            }
        }
        else{
            if(Obj2->in == Pool2_L){
                if(Obj2->slow == true){
                    Obj2->speed *= 2;
                    Obj2->slow = false;
                    Obj2->in = -1;
                }
            }
        }  
    }
}
void Pool2_draw(Elements *self){

}
void Pool2_destroy(Elements *self){
    Pool2 *Obj = ((Pool2 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}