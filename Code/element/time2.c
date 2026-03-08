#include "time2.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

Elements *New_Time2(int label){
    Time2 *pDerivedObj = (Time2 *)malloc(sizeof(Time2));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->size = 20;
    pDerivedObj->x = 1380;
    pDerivedObj->y = 0;
    pDerivedObj->font = al_load_ttf_font("assets/font/Rubik-Black.ttf", pDerivedObj->size, 0);
    pDerivedObj->elapsed_time = 0.0;
    pDerivedObj->start = false;
    pDerivedObj->crown_catch_start_time = 0;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Player2_L;
    pObj->Update = Time2_update;
    pObj->Interact = Time2_interact;
    pObj->Draw = Time2_draw;
    pObj->Destroy = Time2_destroy;
    return pObj;
}
void Time2_update(Elements *self){
    Time2_draw(self);      // 繪製碼表
    
}
void Time2_interact(Elements *self, Elements *tar){
}
void Time2_draw(Elements *self){
    Time2 *Obj = ((Time2 *)(self->pDerivedObj));
    char timer_text[32];
    // 將已經過的時間格式化為文字
    snprintf(timer_text, sizeof(timer_text), "Time: %.1f s", Obj->elapsed_time);

    // 在螢幕中央上方繪製時間
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->x, Obj->y, ALLEGRO_ALIGN_CENTER, timer_text);
}
void Time2_destroy(Elements *self){

}