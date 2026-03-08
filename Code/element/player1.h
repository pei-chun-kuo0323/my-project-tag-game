#ifndef PLAYER1_H_INCLUDED
#define PLAYER1_H_INCLUDED
#include "../shapes/Shape.h"
#include "element.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdbool.h>
#include "../scene/gamescene.h"
#include "player2.h"


typedef struct _Player1
{
    int x, y;
    int width[2], height[2];
    ALLEGRO_BITMAP *img[4][4][2] , *crown; //圖片
    Shape *hitbox; 
    int in; //互動(減速)
    int dir; //方向
    int state; //行走or站立
    int pre_state_dir; //前一動作
    int speed; //角色移動速度
    bool slow; //是否減速

    //行走動畫
    int frame;             // 當前幀
    float frame_delay;     // 幾幀切換一次
    float frame_timer;     // 幀計時器

    //拿到王冠
    double current_time; //現在時間
    bool crown_catch; //是否拿到王冠

    //小王冠圖片
    int crown_width; //小王冠 寬 (頭部)
    int crown_height; //小王冠 高 (頭部)

    //暈眩
    bool diz; //是否暈眩
    bool diz_start; //暈眩是否開始
    double diz_time; //暈眩開始時間

    //加速
    bool boost; // 是否加速狀態
    double boost_start; // 加速開始的時間
    double boost_long; //加速時長
    bool boost_cooldown; // 是否進入冷卻
    int boost_cooldown_long; //冷卻長度
    double boost_cooldown_time; // 冷卻開始的時間

    //時鐘
    double escape_time; //持得王冠總時間
    bool escape_time_start; //持得王冠時間計算是否開始
    double crown_catch_start_time; //持得王冠開始時間
    double accumulated_time; //累積時間

    //大招
    bool ultimate_catch; //是否獲得大絕
    bool ultimate; // 是否開啟大招狀態
    double ultimate_start; // 大招開始的時間
    double ultimate_long; // 大招持續時間
    bool ultimate_cooldown; // 是否進入冷卻
    double ultimate_cooldown_long; // 冷卻時長
    double ultimate_cooldown_time; // 冷卻開始的時間
    bool ultimate_effect; //技能效果是否已經生效
    bool ultimate_effect_stop; //技能效果是否結束
    int ultimate_charge; //技能儲存次數
    bool key_press; //避免連按

    //柯南大招
    int Conan_teleportation; //瞬移距離

    //小蘭大招
    double Angel_radius; //大招範圍半徑

} Player1;

Elements *New_Player1(int label);
void _Player1_update_position(Elements *self, int dx, int dy);
void Player1_update(Elements *self);
void Player1_interact(Elements *self, Elements *target);
void Player1_draw(Elements *self);
void Player1_draw2(Elements *self,Elements *tar);
void Player1_destroy(Elements *self);
void Player1_moveback(Elements *self,Player1 *Obj);
float move_last_time ,move_current_time ,move_delta_time;

#endif