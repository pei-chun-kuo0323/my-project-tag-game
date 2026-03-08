#include "conan.h"

Elements *New_Conan(int label){
    Conan *pDerivedObj = (Conan *)malloc(sizeof(Conan));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    char file_path[50];
    

    for (int dir = 0; dir < 4; dir++) {
        for (int frame = 0; frame < 4; frame++) {
            snprintf(file_path, sizeof(file_path), "assets/image/Conan/%d.%d.png", dir, frame);
            pDerivedObj->img[dir][frame] = al_load_bitmap(file_path);
        }
    }
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Player1_L;
    pObj->inter_obj[pObj->inter_len++] = Crown_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Conan_update;
    pObj->Interact = Conan_interact;
    pObj->Draw = Conan_draw;
    pObj->Destroy = Conan_destroy;
    return pObj;
}
void Conan_update(Elements *self){

}
void Conan_interact(Elements *self, Elements *tar){
    // Conan *Obj = ((Conan *)(self->pDerivedObj));
    // if(player_1_chara == Conan_L){
    //     Player1 *Obj2 = ((Player1 *)(tar->pDerivedObj));
    //     for(int i=0;i<4;i++){
    //         for(int j=0;j<4;j++){
    //             Obj2->img[i][j] = Obj->img[i][j];
    //         }
    //     }
    // }
}
void Conan_draw(Elements *self){

}
void Conan_destroy(Elements *self){
    Conan *Obj = ((Conan *)(self->pDerivedObj));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (Obj->img[i][j]) {
                al_destroy_bitmap(Obj->img[i][j]);
            }
        }
    }
    free(Obj);
    free(self);
}