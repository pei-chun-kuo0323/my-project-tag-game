#include <stdio.h>
#include <stdbool.h>
#include "player1.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h> 
#include "../shapes/Rectangle.h" 
#include "../global.h"

Elements *New_Player1(int label){
    Player1 *pDerivedObj = (Player1 *)malloc(sizeof(Player1));
    Elements *pObj = New_Elements(label);

    pDerivedObj->x = 2048 - 480; 
    pDerivedObj->y = 1152;

    //圖片引入(動畫)
    char file_path[50];
    for (int dir = 0; dir < 4; dir++) {
        for (int frame = 0; frame < 4; frame++) {
            for(int i=0;i<2;i++){
                snprintf(file_path, sizeof(file_path), "assets/image/%s/%d.%d.%d.png",skin[player_1_chara], dir, frame,i);
                pDerivedObj->img[dir][frame][i] = al_load_bitmap(file_path);
            }
        }
    }
    
    pDerivedObj->width[0] = al_get_bitmap_width(pDerivedObj->img[0][0][0]);
    pDerivedObj->height[0] = al_get_bitmap_height(pDerivedObj->img[0][0][0]);
    pDerivedObj->width[1] = al_get_bitmap_width(pDerivedObj->img[0][0][1]);
    pDerivedObj->height[1] = al_get_bitmap_height(pDerivedObj->img[0][0][1]);

    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x - pDerivedObj->width[0]/2,
                                        pDerivedObj->y - pDerivedObj->height[0]/2,
                                        pDerivedObj->x + pDerivedObj->width[0]/2,
                                        pDerivedObj->y + pDerivedObj->height[0]/2);
    pDerivedObj->in = -1;
    pDerivedObj->dir = DOWN; 
    pDerivedObj->state = STOP_C;
    pDerivedObj->pre_state_dir = DOWN;
    pDerivedObj->speed = 6; //偶數，不然除完會無條件捨d去
    pDerivedObj->slow = false;

    //行走動畫
    pDerivedObj->frame = 0;
    pDerivedObj->frame_delay = 0.25f;
    pDerivedObj->frame_timer = 0.0f;
    
    pDerivedObj->crown_catch = false;

    //小王冠
    pDerivedObj->crown = al_load_bitmap("assets/image/crown.2.png");
    pDerivedObj->crown_width = al_get_bitmap_width(pDerivedObj->crown);
    pDerivedObj->crown_height = al_get_bitmap_height(pDerivedObj->crown);

    //暈眩
    pDerivedObj->diz = false;
    pDerivedObj->diz_start = false;

    //加速
    pDerivedObj->boost = false;
    pDerivedObj->boost_long = 1;
    pDerivedObj->boost_start = 0;
    pDerivedObj->boost_cooldown_long = 3;
    pDerivedObj->boost_cooldown = false;

    //時鐘
    pDerivedObj->escape_time = 0.0;
    pDerivedObj->escape_time_start = false;
    pDerivedObj->crown_catch_start_time = 0.0;
    pDerivedObj->accumulated_time = 0.0;

    //大招
    pDerivedObj->ultimate_catch = false;
    pDerivedObj->ultimate = false;
    pDerivedObj->ultimate_long = character_ultimate_long[player_1_chara];         //因角色而異
    pDerivedObj->ultimate_start = 0;
    pDerivedObj->ultimate_cooldown_long = character_cooldown[player_1_chara];    //因角色而異
    pDerivedObj->ultimate_cooldown = false;
    pDerivedObj->ultimate_effect = false;
    pDerivedObj->ultimate_effect_stop = false;
    pDerivedObj->ultimate_charge = 1;
    pDerivedObj->key_press = false;

    //柯南大招
    pDerivedObj->Conan_teleportation = 300;

    //小蘭大招
    pDerivedObj->Angel_radius = 350.0;



    pObj->pDerivedObj = pDerivedObj;
    // 設置互動
    pObj->inter_obj[pObj->inter_len++] = Conan_L;
    pObj->inter_obj[pObj->inter_len++] = Player2_L;
    pObj->inter_obj[pObj->inter_len++] = Time1_L;
    pObj->inter_obj[pObj->inter_len++] = House_L;
    pObj->inter_obj[pObj->inter_len++] = Wood1_L;
    pObj->inter_obj[pObj->inter_len++] = Wood2_L;
    // setting derived object function
    pObj->Draw = Player1_draw;
    pObj->Update = Player1_update;
    pObj->Interact = Player1_interact;
    pObj->Destroy = Player1_destroy;
    return pObj;
}

void _Player1_update_position(Elements *self, int dx, int dy){
    
    // 獲取角色物件
    Player1 *chara = ((Player1 *)(self->pDerivedObj));
    Shape *hitbox = chara->hitbox;
    
    // 更新位置
    chara->x += dx;  // 更新水平方向位置
    chara->y += dy;  // 更新垂直方向位置
    

    // 可選：限制角色在畫面內的移動（根據你的畫面尺寸和邊界限制角色的位置）
    if (chara->x < chara->width[0]/2)
    {
        chara->x = chara->width[0]/2;  // 防止角色移出畫面左邊界
    }
    else if (chara->x > bg_width- chara->width[0]/2)
    {
        chara->x = bg_width- chara->width[0]/2;  // 防止角色移出畫面右邊界
    }
    else
    {
        hitbox->update_center_x(hitbox, dx);
    }
    
    
    if (chara->y < chara->height[0]/2) 
    {
        chara->y = chara->height[0]/2;  // 防止角色移出畫面上邊界
    }
    else if (chara->y > bg_height-chara->height[0]/2 ) 
    {
        chara->y = bg_height-chara->height[0]/2 ;  // 防止角色移出畫面下邊界
    }
    else
    {
        hitbox->update_center_y(hitbox, dy);
    }
}


void Player1_update(Elements *self){
    Player1 *chara = ((Player1 *)(self->pDerivedObj));
    chara->current_time = al_get_time(); 

    //獲勝方法
    if(chara->escape_time > 30){
        player_1_win = true;
        game_end = true;
    }

    //遊戲進行
    if(!game_end)
    {
        //暈眩不能行動
        if(chara->diz){
            //計時(暈眩)
            if(!chara->diz_start){
                chara->diz_time = al_get_time();
                chara->diz_start = true;
            }
            else
            {
                if(chara->current_time - chara->diz_time > 3){
                    chara->diz = false;
                    chara->diz_start = false;
                }
            }
        }
        else{
            //計時(持王冠時間)
            if (chara->crown_catch) {
                if (!chara->escape_time_start) {
                    // 第一次開始計時，記錄起始時間
                    chara->crown_catch_start_time = al_get_time();
                    chara->escape_time_start = true;
                } else {
                    // 更新 escape_time 為目前累計的時間
                    if(!chara->diz){
                        chara->escape_time = (al_get_time() - chara->crown_catch_start_time) + chara->accumulated_time ;
                    }
                }
            } else {
                if (chara->escape_time_start && !chara->diz) {
                    // 將當前已經計算的時間存入 accumulated_time，避免多次累加
                    chara->accumulated_time = chara->escape_time;
                    chara->escape_time_start = false;
                }
            }
            
            //衝刺

            if (!chara->boost_cooldown)            
            {
                if(key_state[ALLEGRO_KEY_R] && !chara->boost){

                    chara->boost=true;
                    chara->boost_start = chara->current_time;
                    chara->speed *= 2;
                    chara->frame_delay /= 2;   
                    
                }else{
                    if(chara->boost && (chara->current_time - chara->boost_start) >= chara->boost_long){
                        chara->speed /= 2;
                        chara->frame_delay *= 2;
                        chara->boost=false;
                        chara->boost_cooldown = true;
                        chara->boost_cooldown_time = chara->current_time;
                    }
                }
            }
            else
            {
                if(chara->current_time - chara->boost_cooldown_time > chara->boost_cooldown_long){
                    chara->boost_cooldown = false;
                    chara->boost_start = 0;
                }
            }

            //大招
        
            if (chara->ultimate_catch) {
                if (chara->ultimate_charge >= 0) {
                    if (key_state[ALLEGRO_KEY_T] && !chara->key_press && !chara->ultimate && chara->ultimate_charge > 0) {
                        // 啟動技能
                        chara->ultimate = true;
                        chara->ultimate_start = chara->current_time;
                        chara->ultimate_effect = true;
                        chara->ultimate_charge--;  // 消耗一次技能次數
                        chara->key_press = true;
                    } 
                    else if (chara->ultimate && (chara->current_time - chara->ultimate_start) >= chara->ultimate_long) {
                        chara->ultimate = false;
                        chara->ultimate_cooldown = true;
                        chara->ultimate_effect_stop = true;
                    }
                    if(!key_state[ALLEGRO_KEY_T]){
                        chara->key_press = false;
                    }
                    
                    
                }
                if(chara->ultimate_charge < max_ultimate_charge[player_1_chara]) {
                    if (chara->current_time - chara->ultimate_cooldown_time > chara->ultimate_cooldown_long) {
                        chara->ultimate_cooldown_time = al_get_time();                        
                        // 冷卻結束後恢復技能次數，確保不超過上限
                        chara->ultimate_charge++;                        
                    }
                }else if(chara->ultimate_charge == max_ultimate_charge[player_1_chara]){
                    chara->ultimate_cooldown_time = al_get_time();  
                }
            }
            else{
                chara->ultimate_cooldown_time = al_get_time();
            }

            //柯南大招(瞬移)
            if(player_1_chara == Conan_skin && chara->ultimate){
                if(chara->dir == LEFT){
                    _Player1_update_position(self,-chara->Conan_teleportation,0);
                }else if(chara->dir == RIGHT){
                    _Player1_update_position(self,chara->Conan_teleportation, 0);
                }else if(chara->dir == UP){
                    _Player1_update_position(self,0,-chara->Conan_teleportation);
                }else if(chara->dir == DOWN){
                    _Player1_update_position(self,0, chara->Conan_teleportation);
                }
                chara->ultimate_effect_stop = true;
                chara->ultimate = false;
            }

            //基本移動
            
            if (chara->state == STOP_C)
            {
                if (key_state[ALLEGRO_KEY_A])
                {
                    chara->dir = LEFT;
                    chara->state = MOVE_C;
                }
                else if (key_state[ALLEGRO_KEY_D])
                {
                    chara->dir = RIGHT;
                    chara->state = MOVE_C;
                }
                else if (key_state[ALLEGRO_KEY_W])
                {
                    chara->dir = UP;
                    chara->state = MOVE_C;
                }
                else if (key_state[ALLEGRO_KEY_S])
                {
                    chara->dir = DOWN;
                    chara->state = MOVE_C;
                }
                else
                {
                    chara->state = STOP_C;
                }
            }
            else if (chara->state == MOVE_C)
            {
                move_current_time = al_get_time();
                
                if (key_state[ALLEGRO_KEY_A])
                {
                    chara->dir = LEFT;
                    _Player1_update_position(self, -chara->speed, 0);
                    chara->state = MOVE_C;
                    chara->pre_state_dir = LEFT;
                }
                else if (key_state[ALLEGRO_KEY_D])
                {
                    chara->dir = RIGHT;
                    _Player1_update_position(self, chara->speed, 0);                        
                    chara->state = MOVE_C;
                    chara->pre_state_dir = RIGHT;
                }        
                else if (key_state[ALLEGRO_KEY_W])
                {
                    chara->dir = UP;                        
                    _Player1_update_position(self, 0, -chara->speed);                    
                    chara->state = MOVE_C;
                    chara->pre_state_dir = UP;
                }   
                else if (key_state[ALLEGRO_KEY_S])
                {
                    chara->dir = DOWN;                    
                    _Player1_update_position(self,0, chara->speed);
                    chara->state = MOVE_C;
                    chara->pre_state_dir = DOWN;
                }
                else{
                    chara->state = STOP_C;
                }
            }
            //動畫幀數
            move_delta_time = move_current_time - move_last_time; 
            move_last_time = move_current_time;
            
            chara->frame_timer += move_delta_time;
            if (chara->frame_timer >= chara->frame_delay) {
                chara->frame_timer -= chara->frame_delay;
                chara->frame = (chara->frame +1) % 4;  // 切換到下一幀
            }
        }
    }
}

void Player1_interact(Elements *self, Elements *target){
    Player1 *Obj = ((Player1 *)(self->pDerivedObj));
    
    if (target->label == Player2_L)
    {
        Player2 *Obj2 = ((Player2 *)(target->pDerivedObj));
        if(Obj->crown_catch){
            Obj2->crown_catch = false;
        }

        //碰撞

        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox) && !Obj2->diz && !Obj->diz && (Obj->crown_catch || Obj2->crown_catch))
        {
            if(Obj2->crown_catch == true ){
                    
                if(!(player_2_chara == Kazuha_skin && Obj2->ultimate)){
                    if(!Obj->diz){
                    Obj->crown_catch = true;
                }
                Obj2->crown_catch = false;
                Obj2->diz = true;
                }
                

                //撞到人大招失效(kid)

                if(player_1_chara == Kid_skin){
                    if(Obj->ultimate){
                        Obj->ultimate = false;                        
                    Obj2->speed = -Obj2->speed;
                    }
                }
            }
        }   

        //大招

        //敵人持王冠15秒後有大招
        if(Obj2->escape_time >= 0){
            Obj->ultimate_catch = true;
        }

        if(Obj->ultimate){
            //基德的技能
            if(player_1_chara == Kid_skin){
                if(Obj->ultimate_effect){
                    Obj2->speed = -Obj2->speed;
                }
                
                if(Obj2->dir == 0 || Obj2->dir == 2){
                    Obj2->dir += 1;
                }
                else if(Obj2->dir == 1 || Obj2->dir == 3){
                    Obj2->dir -= 1;
                }
            }
            Obj->ultimate_effect = false ;

        }else if(Obj->ultimate_effect_stop){

            //基德的技能
            if(player_1_chara == Kid_skin){
                Obj2->speed = -Obj2->speed;
                Obj->ultimate_effect_stop = false;
            }
            if(player_1_chara == Angel_skin){

                double Angel_distance_x = Obj->x - Obj2->x ,Angel_distance_y = Obj->y - Obj2->y;
                double Angel_distance = sqrt(Angel_distance_x * Angel_distance_x + Angel_distance_y * Angel_distance_y);
                if(Angel_distance <= Obj->Angel_radius){
                    if(Obj->crown_catch){
                        Obj2->diz = true;
                        Obj->ultimate_effect_stop = false;
                    }else{
                        if(!(player_2_chara == Kazuha_skin && Obj2->ultimate)){
                            _Player2_update_position(target, Angel_distance_x, Angel_distance_y);
                        }
                        Obj->ultimate_effect_stop = false;
                    }
                }else{
                    Obj->ultimate_effect_stop = false;
                }
            }
        }
    }

    //計時器
    if(target->label == Time1_L){
        Time1 *Obj2 = ((Time1 *)(target->pDerivedObj));
        if(Obj->escape_time <=60.0){
            Obj2->elapsed_time = Obj->escape_time ;
        }else if(Obj->escape_time >60.0){
            Obj2->elapsed_time = 60.0;
        }
    }

    //建築物(不可穿越)
    if(target->label == House_L){
        House *Obj2 = ((House *)(target->pDerivedObj));

        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)){
            if(!(player_1_chara == Heiji_skin && Obj->ultimate)){
                Player1_moveback(self,Obj);
            }
            if(player_1_chara == Heiji_skin && !Obj->ultimate&& Obj->ultimate_effect_stop){
               position_correct_Heiji(self , target) ;
               Obj->ultimate_effect_stop = false;
            }
            if(player_1_chara == Conan_skin && !Obj->ultimate && Obj->ultimate_effect_stop){
               position_correct_Conan(self , target) ;
               Obj->ultimate_effect_stop = false;
            }
        }
    }

    if(target->label == Wood1_L){
        Wood1 *Obj2 = ((Wood1 *)(target->pDerivedObj));

        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)){
            if(!(player_1_chara == Heiji_skin && Obj->ultimate)){
                Player1_moveback(self,Obj);
            }
            if(player_1_chara == Heiji_skin && !Obj->ultimate&& Obj->ultimate_effect_stop){
               position_correct_Heiji(self , target) ;
               Obj->ultimate_effect_stop = false;
            }
            if(player_1_chara == Conan_skin && !Obj->ultimate && Obj->ultimate_effect_stop){
               position_correct_Conan(self , target) ;
               Obj->ultimate_effect_stop = false;
            }
        }
    }

    if(target->label == Wood2_L){
        Wood2 *Obj2 = ((Wood2 *)(target->pDerivedObj));

        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)){
            if(!(player_1_chara == Heiji_skin && Obj->ultimate)){
                Player1_moveback(self,Obj);
            }
            if(player_1_chara == Heiji_skin && !Obj->ultimate&& Obj->ultimate_effect_stop){
               position_correct_Heiji(self , target) ;
               Obj->ultimate_effect_stop = false;
            }
            if(player_1_chara == Conan_skin && !Obj->ultimate && Obj->ultimate_effect_stop){
               position_correct_Conan(self , target) ;
               Obj->ultimate_effect_stop = false;
            }
        }
    }

}
void Player1_draw(Elements *self){

    Player1 *Obj = ((Player1 *)(self->pDerivedObj));

    //使玩家角色置中
    int m = Obj->x , n = Obj->y;
    if(Obj->x > player_1_width/2 && Obj->x< bg_width - player_1_width/2){
        m = player_1_width/2;
    }else if(Obj->x >= bg_width - player_1_width){
        m = Obj->x - bg_width + player_1_width;
    }
    if(Obj->y > player_1_height/2 && Obj->y < bg_height - player_1_height/2){
        n = player_1_height/2;
    }else if(Obj->y >= bg_height - player_1_height/2){
        n = Obj->y - bg_height + player_1_height;
    }
    
    if(Obj->state == MOVE_C){
        al_draw_scaled_bitmap(Obj->img[Obj->dir][Obj->frame][Obj->ultimate],0,0,Obj->width[Obj->ultimate],Obj->height[Obj->ultimate],m - Obj->width[Obj->ultimate]/2 ,n - Obj->height[Obj->ultimate]/2 ,Obj->width[Obj->ultimate],Obj->height[Obj->ultimate], 0);
    }
    else if(Obj->state == STOP_C){
        al_draw_scaled_bitmap(Obj->img[Obj->pre_state_dir][0][Obj->ultimate],0,0,Obj->width[Obj->ultimate],Obj->height[Obj->ultimate],m - Obj->width[Obj->ultimate]/2 ,n - Obj->height[Obj->ultimate]/2 ,Obj->width[Obj->ultimate],Obj->height[Obj->ultimate], 0);
    }

    //Angel角色大招特效
    if(player_1_chara == Angel_skin && Obj->ultimate){
        al_draw_circle(m,n,Obj->Angel_radius,al_map_rgb(255, 0, 0),2);
    }
    
    //小王冠特效
    if(Obj->crown_catch){
        al_draw_scaled_bitmap(Obj->crown,0,0,Obj->crown_width,Obj->crown_height,m - Obj->crown_width/2 ,n - 9*Obj->height[0]/20 ,Obj->crown_width,Obj->crown_height, 0);
    }
    
}
void Player1_draw2(Elements *self,Elements *tar){
    Player1 *Obj = ((Player1 *)(self->pDerivedObj));
    Player2 *Player2_Obj = ((Player2 *)(tar->pDerivedObj));
    //另一視角的人物座標(與本玩家有關)
    int m2 = Obj->x+960 , n2 = Obj->y;
    if(Player2_Obj->x > player_1_width/2 && Player2_Obj->x< bg_width - player_1_width/2)
    {  
        m2 = (Obj->x+960)-(Player2_Obj->x-480);
    }else if(Player2_Obj->x >= bg_width - player_1_width){
        m2 = 960-(4096-Obj->x)+960;
    }
    if(Player2_Obj->y > player_1_height/2 && Player2_Obj->y < bg_height - player_1_height/2){
        n2 = (Obj->y)-(Player2_Obj->y-540);
    }else if(Player2_Obj->y >= bg_height - player_1_height/2){
        n2 = 1080-(2304-Obj->y);
    }

    if(Obj->state == MOVE_C){
        al_draw_scaled_bitmap(Obj->img[Obj->dir][Obj->frame][Obj->ultimate],0,0,Obj->width[Obj->ultimate],Obj->height[Obj->ultimate],m2 - Obj->width[Obj->ultimate]/2 ,n2 - Obj->height[Obj->ultimate]/2 ,Obj->width[Obj->ultimate],Obj->height[Obj->ultimate], 0);
    }
    else if(Obj->state == STOP_C){
        al_draw_scaled_bitmap(Obj->img[Obj->pre_state_dir][0][Obj->ultimate],0,0,Obj->width[Obj->ultimate],Obj->height[Obj->ultimate],m2 - Obj->width[Obj->ultimate]/2 ,n2 - Obj->height[Obj->ultimate]/2 ,Obj->width[Obj->ultimate],Obj->height[Obj->ultimate], 0);
    }
    if(Obj->crown_catch){
        al_draw_scaled_bitmap(Obj->crown,0,0,Obj->crown_width,Obj->crown_height,m2 - Obj->crown_width/2 ,n2 - 9*Obj->height[0]/20 ,Obj->crown_width,Obj->crown_height, 0);
    }
}

void Player1_moveback(Elements *self,Player1 *Obj){
    if(Obj->dir == LEFT){
        _Player1_update_position(self,Obj->speed,0);
    }else if(Obj->dir == RIGHT){
        _Player1_update_position(self,-Obj->speed, 0);
    }else if(Obj->dir == UP){
        _Player1_update_position(self,0, Obj->speed);
    }else if(Obj->dir == DOWN){
        _Player1_update_position(self,0, -Obj->speed);
    }
}

void Player1_destroy(Elements *self){
    Player1 *Obj = ((Player1 *)(self->pDerivedObj));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for(int k=0;k<2;k++){
                if (Obj->img[i][j][k]) {
                    al_destroy_bitmap(Obj->img[i][j][k]);
                }
            }
        }
    }
    free(Obj->hitbox);
    free(Obj);
    free(self);
}