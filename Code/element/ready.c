// #include "ready.h"


// Elements *New_Ready(int label){
//     Ready *pDerivedObj = (Ready *)malloc(sizeof(Ready));
//     Elements *pObj = New_Elements(label);
//     // setting derived object member
//     pDerivedObj->size = 20;
//     pDerivedObj->x = 1380;
//     pDerivedObj->y = 0;
//     pDerivedObj->font = al_load_ttf_font("assets/font/Rubik-Black.ttf", pDerivedObj->size, 0);
//     // setting derived object function
//     pObj->pDerivedObj = pDerivedObj;
//     // setting the interact object
//     pObj->inter_obj[pObj->inter_len++] = Player2_L;
//     pObj->Update = Ready_update;
//     pObj->Interact = Ready_interact;
//     pObj->Draw = Ready_draw;
//     pObj->Destroy = Ready_destroy;
//     return pObj;
// }
// void Ready_update(Elements *self){

// }
// void Ready_interact(Elements *self, Elements *tar){

// }
// void Ready_draw(Elements *self){
//     Ready *Obj = ((Ready *)(self->pDerivedObj));
//     char timer_text[32];
//     // 將已經過的時間格式化為文字
//     snprintf(timer_text, sizeof(timer_text), "%s", Obj->elapsed_time);

//     // 在螢幕中央上方繪製時間
//     al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->x, Obj->y, ALLEGRO_ALIGN_CENTER, timer_text);
// }

// void Ready_destroy(Elements *self){

// }