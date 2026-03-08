#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "menu.h"
#include <stdio.h>
#include "../element/element.h"
#include "../element/RodUP.h"
#include "../element/RodDOWN.h"
#include "../element/player1.h"
#include "../element/ball.h"
#include "../element/player2.h"
#include "../shapes/Rectangle.h"
#include "../element/crown.h"
#include "../element/time1.h"
#include "../element/time2.h"
#include "../element/house.h"
#include "../element/pool1.h"
#include "../element/pool2.h"
#include "../element/pool3.h"
#include "../element/pool4.h"
#include "../element/pool5.h"
#include "../element/wood1.h"
#include "../element/wood2.h"
#include "../element/conan.h"
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
/*
   [game scene object]
*/



typedef enum EleType
{
    RodUP_L = 0,
    Ball_L,
    Player1_L,
    Player2_L,
    Time1_L,
    Time2_L,
    Conan_L,
    Crown_L,
    House_L,
    Pool1_L,
    Pool2_L,
    Pool3_L,
    Pool4_L,
    Pool5_L,
    Wood1_L,
    Wood2_L
    
} EleType;

typedef enum SkinType
{
    Conan_skin = 0,
    Kid_skin,
    Angel_skin,
    Heiji_skin,
    Kazuha_skin
    
} Skin;

typedef struct _GameScene
{
    int ready_x[5],ready_y[5];
    ALLEGRO_BITMAP *ready[5] , *background , *gameagain, *crown;
    ALLEGRO_BITMAP *game_result[2];
    ALLEGRO_FONT *font;

} GameScene;

typedef enum Type
{
    STOP_C ,
    MOVE_C,
    jump_C
    
} Type;

typedef enum Dir
{
    UP = 0 ,
    DOWN,
    LEFT,
    RIGHT
    
} Dir;

typedef struct _Btn
{   
    ALLEGRO_BITMAP *img[2];
    double x, y;
    int state;
    bool check;
} Btn;



Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self );
void game_scene_destroy(Scene *self);
void game_scene_item_draw_Left(ALLEGRO_BITMAP *img,int Obj_x,int Obj_y,int Obj_width,int Obj_height, int player_x, int player_y, int bg_width, int bg_height, int player_width, int player_height);
void game_scene_item_draw_Right(ALLEGRO_BITMAP *img,int Obj_x,int Obj_y,int Obj_width,int Obj_height, int player_x, int player_y, int bg_width, int bg_height, int player_width, int player_height);
void position_correct_Heiji(Elements *player , Elements * self);
void position_correct_Conan(Elements *player , Elements * self);

int x1,y1,x2,y2,offset_x1,offset_y1,offset_x2,offset_y2;
int player_1_chara;
int player_2_chara;
double character_cooldown[5];
int character_ultimate_long[5];
const char *skin[5];
int max_ultimate_charge[5]; //技能儲存次數
extern int sceneNow;

#endif
