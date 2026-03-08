#include "time1.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

Elements *New_Time1(int label){
    Time1 *pDerivedObj = (Time1 *)malloc(sizeof(Time1));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->size = 20;
    pDerivedObj->x = 380;
    pDerivedObj->y = 0;
    pDerivedObj->font = al_load_ttf_font("assets/font/Rubik-Black.ttf", pDerivedObj->size, 0);
    pDerivedObj->elapsed_time = 0.0;
    pDerivedObj->start = false;
    pDerivedObj->crown_catch_start_time = 0;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Player1_L;
    pObj->Update = Time1_update;
    pObj->Interact = Time1_interact;
    pObj->Draw = Time1_draw;
    pObj->Destroy = Time1_destroy;
    return pObj;
}
void Time1_update(Elements *self){
    Time1_draw(self);      // 繪製碼表
    
}
void Time1_interact(Elements *self, Elements *tar){
}
void Time1_draw(Elements *self){
    Time1 *Obj = ((Time1 *)(self->pDerivedObj));
    char timer_text[32];
    // 將已經過的時間格式化為文字
    snprintf(timer_text, sizeof(timer_text), "Time: %.1f s", Obj->elapsed_time);

    // 在螢幕中央上方繪製時間
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->x, Obj->y, ALLEGRO_ALIGN_CENTER, timer_text);
}
void Time1_destroy(Elements *self){

}