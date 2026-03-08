#include "ball.h"
#include "../shapes/Circle.h"
#include "../global.h"
#include <allegro5/allegro_primitives.h> 


Elements *New_Ball(int label){
    Ball *pDerivedObj = (Ball *)malloc(sizeof(Ball));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->x = mouse.x;
    pDerivedObj->y = mouse.y;
    pDerivedObj->r = 10;
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(255,0,0);
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x,pDerivedObj->y,pDerivedObj->r);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Player1_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Ball_update;
    pObj->Interact = Ball_interact;
    pObj->Draw = Ball_draw;
    pObj->Destroy = Ball_destory;
    return pObj;
}
void Ball_update(Elements *self){
    Ball *Obj = ((Ball *)(self->pDerivedObj));
    
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, mouse.x - Obj->x);
    hitbox->update_center_y(hitbox, mouse.y - Obj->y);
    Obj->x = mouse.x;
    Obj->y = mouse.y;
}
void Ball_interact(Elements *self, Elements *tar){
    Ball *Obj = ((Ball *)(self->pDerivedObj));
    if (tar->label == Crown_L)
    {
        Crown *Obj2 = ((Crown *)(tar->pDerivedObj));

        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox))
        {
            Obj->color = al_map_rgb(0,255,255);
            Obj->in = Crown_L;
        }   
        else if(Obj->in == Crown_L)
        {
            Obj->color = al_map_rgb(255,0,0);
            Obj->in = -1;
        }
    }
    if (tar->label == Player1_L)
    {
        Player1 *Obj2 = ((Player1 *)(tar->pDerivedObj));

        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox))
        {
            Obj->color = al_map_rgb(0,255,255);
            Obj->in = Player1_L;
        }   
        else if(Obj->in == Player1_L)
        {
            Obj->color = al_map_rgb(255,0,0);
            Obj->in = -1;
        }
    }
}
void Ball_draw(Elements *self){
    Ball *Obj = ((Ball *)(self->pDerivedObj));
    al_draw_filled_circle(Obj->x, Obj->y,Obj->r,Obj->color);
}
void Ball_destory(Elements *self){
    Ball *Obj = ((Ball *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}