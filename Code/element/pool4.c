#include "pool4.h"

Elements *New_Pool4(int label){
    Pool4 *pDerivedObj = (Pool4 *)malloc(sizeof(Pool4));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/Pool4.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 2480;
    pDerivedObj->y = 1670;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2+50,
                                        pDerivedObj->y-pDerivedObj->height/2+50,
                                        pDerivedObj->x+pDerivedObj->width/2-50,
                                        pDerivedObj->y+pDerivedObj->height/2-50);

    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Player1_L;
    pObj->inter_obj[pObj->inter_len++] = Player2_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Pool4_update;
    pObj->Interact = Pool4_interact;
    pObj->Draw = Pool4_draw;
    pObj->Destroy = Pool4_destroy;
    return pObj;
}
void Pool4_update(Elements *self){




}
void Pool4_interact(Elements *self, Elements *target){
    Pool4 *Obj = ((Pool4 *)(self->pDerivedObj));
    if (target->label == Player1_L)
    {
        Player1 *Obj2 = ((Player1 *)(target->pDerivedObj));

        
        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox))
        {
            if(Obj2->slow == false)
            {
                Obj2->speed /= 2;
                Obj2->slow = true;
                Obj2->in = Pool4_L;
            }
        }
        else{
            if(Obj2->in == Pool4_L){
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
                Obj2->in = Pool4_L;
            }
        }
        else{
            if(Obj2->in == Pool4_L){
                if(Obj2->slow == true){
                    Obj2->speed *= 2;
                    Obj2->slow = false;
                    Obj2->in = -1;
                }
            }
        }  
    }
}
void Pool4_draw(Elements *self){

}
void Pool4_destroy(Elements *self){
    Pool4 *Obj = ((Pool4 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}