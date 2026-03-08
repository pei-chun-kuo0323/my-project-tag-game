#include "gamescene.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../element/element.h"
#include "../element/RodUP.h"
#include "../element/RodDOWN.h"
#include "../element/player1.h"
#include "../element/ball.h"
#include <allegro5/allegro_primitives.h>
#include "menu.h"

/*
   [GameScene function]
*/

enum{ READY = 0, GAME, GAMEOVER};
int sceneNow2 = 0;
int ready_time_number = 0;
bool plus_minus = false; //正負(Ready動畫)

//各角色(名字)
const char *skin[5] = {"Conan","Kid","Angel","Heiji","Kazuha"};

//各角色冷卻時間
double character_cooldown[5] = {2.5,12.0,8.0,15.0,15.0};
int character_ultimate_long[5] = {1,5,1,8,6};

//技能儲存次數
int max_ultimate_charge[5] = {3,1,1,1,1};

//scale1是Victory和Defeat ， scale2是Gameover轉場 ， scale3 是入場動畫
float scale1 = 0.0,alpha1 = 0.0,scale2 = 0.0,scale3 = 1.0,alpha2 = 0.5; 

Btn GameAgain[3];

Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->ready[0] = al_load_bitmap("assets/image/ready.png");
    pDerivedObj->ready[1] = al_load_bitmap("assets/image/3.png");
    pDerivedObj->ready[2] = al_load_bitmap("assets/image/2.png");
    pDerivedObj->ready[3] = al_load_bitmap("assets/image/1.png");
    pDerivedObj->ready[4] = al_load_bitmap("assets/image/start.png");
    pDerivedObj->background = al_load_bitmap("assets/image/scene/1.1.png");
    pDerivedObj->game_result[0] = al_load_bitmap("assets/image/victory.png");
    pDerivedObj->game_result[1] = al_load_bitmap("assets/image/defeat.png");
    pDerivedObj->gameagain = al_load_bitmap("assets/image/gameagain.png");
    pDerivedObj->crown = al_load_bitmap("assets/image/crown.png");
    pDerivedObj->font = al_load_ttf_font("assets/font/Rubik-Black.ttf", 20, 0);

    for(int i=0;i<5;i++){
        pDerivedObj->ready_x[i] = al_get_bitmap_width(pDerivedObj->ready[i]);
        pDerivedObj->ready_y[i] = al_get_bitmap_height(pDerivedObj->ready[i]);
    }

    //結束介面按紐

    char file_path[50];
    for (int dir = 0; dir < 3; dir++) {
        for (int frame = 0; frame < 2; frame++) {
            snprintf(file_path, sizeof(file_path), "assets/image/again.%d.%d.png", dir, frame);
            GameAgain[dir].img[frame] = al_load_bitmap(file_path);
        }
    }

    for(int i=0;i<3;i++){
        GameAgain[i].x = 400;
    }
    GameAgain[0].y = 150;
    GameAgain[1].y = 400;
    GameAgain[2].y = 650;

    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Player1(Player1_L));
    _Register_elements(pObj, New_Player2(Player2_L));
    _Register_elements(pObj, New_Ball(Ball_L));
    _Register_elements(pObj, New_Crown(Crown_L));
    _Register_elements(pObj, New_Time1(Time1_L));
    _Register_elements(pObj, New_Time2(Time2_L));
    _Register_elements(pObj, New_House(House_L));
    _Register_elements(pObj, New_Pool1(Pool1_L));
    _Register_elements(pObj, New_Pool2(Pool2_L));
    _Register_elements(pObj, New_Pool3(Pool3_L));
    _Register_elements(pObj, New_Pool4(Pool4_L));
    _Register_elements(pObj, New_Pool5(Pool5_L));
    _Register_elements(pObj, New_Wood1(Wood1_L));
    _Register_elements(pObj, New_Wood2(Wood2_L));
    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}
void game_scene_update(Scene *self)
{
    // update every element
    double mx = mouse.x , my = mouse.y ;
    ElementVec allEle = _Get_all_elements(self);

    //入場動畫
    if(sceneNow2 == READY){
        
        if(ready_time_number<=3){
            if(scale3 >0 && !plus_minus){
                scale3 -= 0.02;
            }else if(scale3 <=0 && !plus_minus){
                ready_time_number += 1;
                plus_minus = true ;
            }else if(scale3 < 1 && plus_minus){
                scale3 += 0.02;
            }else if(scale3 >= 1 && plus_minus){
                plus_minus = false ;
            }
        }
        
        else if(ready_time_number == 4){
            if(scale3 < 1 && plus_minus){
                scale3 += 0.02;
            }else if(scale3 >= 1 && plus_minus){
                plus_minus = false ;
            }if(scale3 >0 && !plus_minus){
                scale3 -= 0.02;
                alpha2 -= 0.01;
            }
        }
        
        if(alpha2 <= 0){
            sceneNow2 = GAME;
        }
    }


    if(sceneNow2 == GAME)    
    {
        for (int i = 0; i < allEle.len; i++)
        {
            allEle.arr[i]->Update(allEle.arr[i]);
        }

        // run interact for every element
        for (int i = 0; i < allEle.len; i++)
        {
            Elements *ele = allEle.arr[i];
            // run every interact object
            for (int j = 0; j < ele->inter_len; j++)
            {
                int inter_label = ele->inter_obj[j];
                ElementVec labelEle = _Get_label_elements(self, inter_label);
                for (int i = 0; i < labelEle.len; i++)
                {
                    ele->Interact(ele, labelEle.arr[i]);
                }
            }
        }
        if(player_1_win||player_2_win){
            if(key_state[ALLEGRO_KEY_ENTER]){
                sceneNow2 = GAMEOVER;
            }
        }
    }
    else if(sceneNow2 == GAMEOVER){
        for(int i=0;i<3;i++){
            double w = al_get_bitmap_width(GameAgain[i].img[0]), h = al_get_bitmap_height(GameAgain[i].img[0]);
            double x = GameAgain[i].x, y = GameAgain[i].y;
            if(mx >= x && mx <= x + w && my >= y && my <= y + h && GameAgain[i].state == 2 && !mouse_state[1]){
                if(i == 0) {
                    self->scene_end = true;
                    window = 0;
                    sceneNow = MENU;
                }
                else if(i == 1) 
                {
                    self->scene_end = true;
                    window = 0;
                    sceneNow = CHOOSE_CHARACTER;
                }
                else if(i == 2) {
                    self->scene_end = true;
                    exit(0); 
                }
                GameAgain[i].state = 0;
                sceneNow2 = READY;
                player_1_win = false;
                player_2_win = false;
                game_end = false;
                scale1 = 0.0,alpha1 = 0.0,scale2 = 0.0,scale3 = 1.0,alpha2 = 0.5;
                plus_minus = false;
                ready_time_number = 0;

            }
            if(mx >= x && mx <= x + w && my >= y && my <= y + h){
                GameAgain[i].state = mouse_state[1] ? 2 : 1, HoverOnItem = true;
            }else GameAgain[i].state = 0;
        }
    }
    
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
}
void game_scene_draw(Scene *self )
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(self->pDerivedObj));

    //角色
    ElementVec Player1_element = _Get_label_elements(self, Player1_L);
    Elements *player1 = Player1_element.arr[0];
    Player1 *Player1_Obj = (Player1 *)(player1->pDerivedObj);
    ElementVec Player2_element = _Get_label_elements(self, Player2_L);
    Elements *player2 = Player2_element.arr[0];
    Player2 *Player2_Obj = (Player2 *)(player2->pDerivedObj);

    //其餘物件
    ElementVec Crown_element = _Get_label_elements(self, Crown_L);
    Elements *crown = Crown_element.arr[0];
    Crown *Crown_Obj = (Crown *)(crown->pDerivedObj);

    ElementVec House_element = _Get_label_elements(self, House_L);
    Elements *house = House_element.arr[0];
    House *house_Obj = (House *)(house->pDerivedObj);

    ElementVec Wood1_element = _Get_label_elements(self, Wood1_L);
    Elements *wood1 = Wood1_element.arr[0];
    Wood1 *wood1_Obj = (Wood1 *)(wood1->pDerivedObj);
    ElementVec Wood2_element = _Get_label_elements(self, Wood2_L);
    Elements *wood2 = Wood2_element.arr[0];
    Wood2 *wood2_Obj = (Wood2 *)(wood2->pDerivedObj);

    ElementVec Pool1_element = _Get_label_elements(self, Pool1_L);
    Elements *pool1 = Pool1_element.arr[0];
    Pool1 *Pool1_Obj = (Pool1 *)(pool1->pDerivedObj);
    ElementVec Pool2_element = _Get_label_elements(self, Pool2_L);
    Elements *pool2 = Pool2_element.arr[0];
    Pool2 *Pool2_Obj = (Pool2 *)(pool2->pDerivedObj);
    ElementVec Pool3_element = _Get_label_elements(self, Pool3_L);
    Elements *pool3 = Pool3_element.arr[0];
    Pool3 *Pool3_Obj = (Pool3 *)(pool3->pDerivedObj);
    ElementVec Pool4_element = _Get_label_elements(self, Pool4_L);
    Elements *pool4 = Pool4_element.arr[0];
    Pool4 *Pool4_Obj = (Pool4 *)(pool4->pDerivedObj);
    ElementVec Pool5_element = _Get_label_elements(self, Pool5_L);
    Elements *pool5 = Pool5_element.arr[0];
    Pool5 *Pool5_Obj = (Pool5 *)(pool5->pDerivedObj);

    int a = 257 ,b = 94 ;
    int target_a = 480 ,target_b = 540 ;


    //繪製人物視角(地圖跟隨)

    x1 = Player1_Obj->x;
    y1 = Player1_Obj->y;
    x2 = Player2_Obj->x;
    y2 = Player2_Obj->y;

    offset_x1 = x1 - player_1_width/2;
    offset_y1 = y1 - player_1_height/2;
    offset_x2 = x2 - player_2_width/2;
    offset_y2 = y2 - player_2_height/2;

    if (offset_x1 < 0)
        offset_x1 = 0; // 左邊界
    if (offset_y1 < 0)
        offset_y1 = 0; // 上邊界
    if (offset_x1 > bg_width-player_1_width)
        offset_x1 = bg_width-player_1_width; // 右邊界
    if (offset_y1 > bg_height-player_1_height)
        offset_y1 = bg_height-player_1_height; // 下邊界
    
    if (offset_x2 < 0)
        offset_x2 = 0; // 左邊界
    if (offset_y2 < 0)
        offset_y2 = 0; // 上邊界
    if (offset_x2 > bg_width-player_1_width)
        offset_x2 = bg_width-player_1_width; // 右邊界
    if (offset_y2 > bg_height-player_1_height)
        offset_y2 = bg_height-player_1_height; // 下邊界
    
    //左邊
    al_draw_bitmap_region(gs->background, offset_x1, offset_y1, player_1_width, player_1_height, 0, 0, 0);//背景
    if(Crown_Obj->touch == false){
        game_scene_item_draw_Left(Crown_Obj->img,Crown_Obj->x,Crown_Obj->y,Crown_Obj->width[0],Crown_Obj->height[0], Player1_Obj->x, Player1_Obj->y, bg_width, bg_height, player_1_width, player_1_height);
    }//王冠

    //其他建築物(角落需另外處理)

    //房子
    game_scene_item_draw_Left(house_Obj->img,house_Obj->x,house_Obj->y,house_Obj->width,house_Obj->height, Player1_Obj->x, Player1_Obj->y, bg_width, bg_height, player_1_width, player_1_height);
    
    //木頭
    game_scene_item_draw_Left(wood1_Obj->img,wood1_Obj->x,wood1_Obj->y,wood1_Obj->width,wood1_Obj->height, Player1_Obj->x, Player1_Obj->y, bg_width, bg_height, player_1_width, player_1_height);
    game_scene_item_draw_Left(wood2_Obj->img,wood2_Obj->x,wood2_Obj->y,wood2_Obj->width,wood2_Obj->height, Player1_Obj->x, Player1_Obj->y, bg_width, bg_height, player_1_width, player_1_height);
    
    //減速水池
    game_scene_item_draw_Left(Pool1_Obj->img,Pool1_Obj->x,Pool1_Obj->y,Pool1_Obj->width,Pool1_Obj->height, Player1_Obj->x, Player1_Obj->y, bg_width, bg_height, player_1_width, player_1_height);
    game_scene_item_draw_Left(Pool2_Obj->img,Pool2_Obj->x,Pool2_Obj->y,Pool2_Obj->width,Pool2_Obj->height, Player1_Obj->x, Player1_Obj->y, bg_width, bg_height, player_1_width, player_1_height);
    game_scene_item_draw_Left(Pool3_Obj->img,Pool3_Obj->x,Pool3_Obj->y,Pool3_Obj->width,Pool3_Obj->height, Player1_Obj->x, Player1_Obj->y, bg_width, bg_height, player_1_width, player_1_height);
    game_scene_item_draw_Left(Pool4_Obj->img,Pool4_Obj->x,Pool4_Obj->y,Pool4_Obj->width,Pool4_Obj->height, Player1_Obj->x, Player1_Obj->y, bg_width, bg_height, player_1_width, player_1_height);
    game_scene_item_draw_Left(Pool5_Obj->img,Pool5_Obj->x,Pool5_Obj->y,Pool5_Obj->width,Pool5_Obj->height, Player1_Obj->x, Player1_Obj->y, bg_width, bg_height, player_1_width, player_1_height);

    
    //敵人人物
    if(x1-x2<480||x1-x2>-480||y1-y2<540||y1-y2>-540){
        if(!(player_2_chara == Kid_skin && Player2_Obj->ultimate)){
            Player2_draw2(player2,player1);
        }
        
    }

    //右邊
    al_draw_bitmap_region(gs->background,offset_x2, offset_y2, player_2_width, player_2_height, 960, 0, 0);

    
    al_set_clipping_rectangle(960,0,1920,1080);//螢幕邊界裁切


    if(Crown_Obj->touch == false){
        game_scene_item_draw_Right(Crown_Obj->img,Crown_Obj->x,Crown_Obj->y,Crown_Obj->width[0],Crown_Obj->height[0], Player2_Obj->x, Player2_Obj->y, bg_width, bg_height, player_2_width, player_2_height);
    }//王冠
    
    //其他建築物
    //房子
    game_scene_item_draw_Right(house_Obj->img,house_Obj->x,house_Obj->y,house_Obj->width,house_Obj->height, Player2_Obj->x, Player2_Obj->y, bg_width, bg_height, player_2_width, player_2_height);
    
    //木頭
    game_scene_item_draw_Right(wood1_Obj->img,wood1_Obj->x,wood1_Obj->y,wood1_Obj->width,wood1_Obj->height, Player2_Obj->x, Player2_Obj->y, bg_width, bg_height, player_2_width, player_2_height);
    game_scene_item_draw_Right(wood2_Obj->img,wood2_Obj->x,wood2_Obj->y,wood2_Obj->width,wood2_Obj->height, Player2_Obj->x, Player2_Obj->y, bg_width, bg_height, player_2_width, player_2_height);
    
    //減速水池
    game_scene_item_draw_Right(Pool1_Obj->img,Pool1_Obj->x,Pool1_Obj->y,Pool1_Obj->width,Pool1_Obj->height, Player2_Obj->x, Player2_Obj->y, bg_width, bg_height, player_2_width, player_2_height);
    game_scene_item_draw_Right(Pool2_Obj->img,Pool2_Obj->x,Pool2_Obj->y,Pool2_Obj->width,Pool2_Obj->height, Player2_Obj->x, Player2_Obj->y, bg_width, bg_height, player_2_width, player_2_height);
    game_scene_item_draw_Right(Pool3_Obj->img,Pool3_Obj->x,Pool3_Obj->y,Pool3_Obj->width,Pool3_Obj->height, Player2_Obj->x, Player2_Obj->y, bg_width, bg_height, player_2_width, player_2_height);
    game_scene_item_draw_Right(Pool4_Obj->img,Pool4_Obj->x,Pool4_Obj->y,Pool4_Obj->width,Pool4_Obj->height, Player2_Obj->x, Player2_Obj->y, bg_width, bg_height, player_2_width, player_2_height);
    game_scene_item_draw_Right(Pool5_Obj->img,Pool5_Obj->x,Pool5_Obj->y,Pool5_Obj->width,Pool5_Obj->height, Player2_Obj->x, Player2_Obj->y, bg_width, bg_height, player_2_width, player_2_height);

    //敵人人物
    if(x1-x2<480||x1-x2>-480||y1-y2<540||y1-y2>-540){
        if(!(player_1_chara == Kid_skin && Player1_Obj->ultimate)){
            Player1_draw2(player1,player2);
        }
    }
    al_reset_clipping_rectangle(); //螢幕裁切恢復
    

    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }

    if(player_1_win){
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
        if(alpha1<0.7){
            alpha1 += 0.02;
            al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT,al_map_rgba_f(0, 0, 0, alpha1) );
        }else{
            al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT,al_map_rgba_f(0, 0, 0, 0.7) );
        }
        
        if (scale1 < 1) {
            scale1 += 0.02; // 增加縮放比例
            target_a = 480 - a * scale1; // 480是960/2(左右螢幕正中間)
            target_b = 540 - b * scale1; //540是1080/2(上下螢幕正中間)
            al_draw_scaled_bitmap(gs->game_result[0],0, 0, 514, 188,target_a, target_b, 514* scale1, 188 * scale1,0);
            al_draw_scaled_bitmap(gs->game_result[1],0, 0, 514, 188,target_a+960, target_b, 514* scale1, 188 * scale1,0);
        }

        else if(scale1 >= 1){
            al_draw_bitmap(gs->game_result[0],480-a, 540-b,0);
            al_draw_bitmap(gs->game_result[1],1440-a,540-b,0);
        }
    }
    else if(player_2_win){
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
        if(alpha1<0.7){
            alpha1 += 0.02;
            al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT,al_map_rgba_f(0, 0, 0, alpha1) );
        }else{
            al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT,al_map_rgba_f(0, 0, 0, 0.7) );
        }
        
        if (scale1 < 1) {
            scale1 += 0.02; // 增加縮放比例
            target_a = 480 - a * scale1; // 480是960/2(左右螢幕正中間)
            target_b = 540 - b * scale1; //540是1080/2(上下螢幕正中間)
            al_draw_scaled_bitmap(gs->game_result[1],0, 0, 514, 188,target_a, target_b, 514* scale1, 188 * scale1,0);
            al_draw_scaled_bitmap(gs->game_result[0],0, 0, 514, 188,target_a+960, target_b, 514* scale1, 188 * scale1,0);
        }

        else if(scale1 >= 1){
            al_draw_bitmap(gs->game_result[1],480-a, 540-b,0);
            al_draw_bitmap(gs->game_result[0],1440-a,540-b,0);
        }
    }

    //測試
    if(Player1_Obj->crown_catch){
        al_draw_bitmap(gs->crown,480,0,0);
    }
    if(Player2_Obj->crown_catch){
        al_draw_bitmap(gs->crown,1340,0,0);
    }

    char timer_text[32];
    // 將已經過的時間格式化為文字
    snprintf(timer_text, sizeof(timer_text), "%d", Player1_Obj->ultimate_charge);

    // 在螢幕中央上方技能冷卻Player1
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 100, 0, ALLEGRO_ALIGN_CENTER, timer_text);
    if(sceneNow2 == GAME){
        snprintf(timer_text, sizeof(timer_text), "%.2f", Player1_Obj->ultimate_cooldown_long - (al_get_time() - Player1_Obj->ultimate_cooldown_time));
    }else{
        snprintf(timer_text, sizeof(timer_text), "%.2f", 0.0);
    }
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 150, 0, ALLEGRO_ALIGN_CENTER, timer_text);

    // 將已經過的時間格式化為文字
    snprintf(timer_text, sizeof(timer_text), "%d", Player2_Obj->ultimate_charge);

    // 在螢幕中央上方技能冷卻Player2
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 1060, 0, ALLEGRO_ALIGN_CENTER, timer_text);
    if(sceneNow2 == GAME){
        snprintf(timer_text, sizeof(timer_text), "%.2f", Player2_Obj->ultimate_cooldown_long - (al_get_time() - Player2_Obj->ultimate_cooldown_time));
    }else{
        snprintf(timer_text, sizeof(timer_text), "%.2f", 0.0);
    }
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 1110, 0, ALLEGRO_ALIGN_CENTER, timer_text);


    if(sceneNow2 == READY){
        al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT,al_map_rgba_f(0, 0, 0, alpha2) );
        al_draw_scaled_bitmap(gs->ready[ready_time_number],0,0,gs->ready_x[ready_time_number],gs->ready_y[ready_time_number], 960 - gs->ready_x[ready_time_number]*scale3/2, 540 - gs->ready_y[ready_time_number]*scale3/2,gs->ready_x[ready_time_number]*scale3,gs->ready_y[ready_time_number]*scale3, 0);
    }
    else if(sceneNow2 == GAMEOVER){
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
        if (scale2 < 1) {
            scale2 += 0.02; // 增加縮放比例
            al_draw_bitmap(gs->gameagain,1920*(1-scale2), 0,0);
            al_draw_bitmap(GameAgain[0].img[GameAgain[0].state>=1],GameAgain[0].x+1920-1920*scale2,GameAgain[0].y,0);
            al_draw_bitmap(GameAgain[1].img[GameAgain[1].state>=1],GameAgain[1].x+1920-1920*scale2,GameAgain[1].y,0);
            al_draw_bitmap(GameAgain[2].img[GameAgain[2].state>=1],GameAgain[2].x+1920-1920*scale2,GameAgain[2].y,0);
        }

        else if(scale1 >= 1){
            al_draw_bitmap(gs->gameagain,0, 0,0);
            al_draw_bitmap(GameAgain[0].img[GameAgain[0].state>=1],GameAgain[0].x+1920-1920*scale2,GameAgain[0].y,0);
            al_draw_bitmap(GameAgain[1].img[GameAgain[1].state>=1],GameAgain[1].x+1920-1920*scale2,GameAgain[1].y,0);
            al_draw_bitmap(GameAgain[2].img[GameAgain[2].state>=1],GameAgain[2].x+1920-1920*scale2,GameAgain[2].y,0);
        }
    }
}

void game_scene_item_draw_Left(ALLEGRO_BITMAP *img,int Obj_x,int Obj_y,int Obj_width,int Obj_height, int player_x, int player_y, int bg_width, int bg_height, int player_width, int player_height)
{
    int item_x = 10000,item_y = 10000;

    if (player_x > player_width / 2  && player_x < bg_width - player_width / 2 ) {
        item_x = 480  + (Obj_x - player_x);
    } else if (player_x >= bg_width - player_width ) {
        item_x = 960 - (bg_width - Obj_x);
    } else if (player_x <= player_width / 2 ) {
        item_x = Obj_x;
    }

    if (player_y > player_height / 2 && player_y < bg_height - player_height / 2) {
        item_y = 540 + (Obj_y - player_y);
    } else if (player_y >= bg_height - player_height / 2) {
        item_y = 1080 - (bg_height - Obj_y);
    } else if (player_y <= player_height / 2) {
        item_y = Obj_y;
    }

    al_draw_scaled_bitmap(img, 0, 0, Obj_width, Obj_height, item_x - Obj_width/2, item_y - Obj_height/2,Obj_width,Obj_height, 0);
}

void game_scene_item_draw_Right(ALLEGRO_BITMAP *img,int Obj_x,int Obj_y,int Obj_width,int Obj_height, int player_x, int player_y, int bg_width, int bg_height, int player_width, int player_height)
{
    int item_x = 10000,item_y = 10000;

    if (player_x > player_width / 2  && player_x < bg_width - player_width / 2) {
        item_x = 480 + (Obj_x - player_x) + 960;
    } else if (player_x >= bg_width - player_width/2) {
        item_x = 960 - (bg_width - Obj_x) + 960;
    } else if (player_x <= player_width / 2) {
        item_x = Obj_x + 960;
    }

    if (player_y > player_height / 2 && player_y < bg_height - player_height / 2) {
        item_y = 540 + (Obj_y - player_y);
    } else if (player_y >= bg_height - player_height / 2) {
        item_y = 1080 - (bg_height - Obj_y);
    } else if (player_y <= player_height / 2) {
        item_y = Obj_y;
    }

    al_draw_scaled_bitmap(img, 0, 0, Obj_width, Obj_height, item_x - Obj_width/2, item_y - Obj_height/2,Obj_width,Obj_height, 0);
}

void position_correct_Heiji(Elements *player, Elements *self) {
    int player_x = 0, player_y = 0, player_width = 0, player_height = 0;
    int obstacle_x = 0, obstacle_y = 0, obstacle_width = 0, obstacle_height = 0;

    // 定義 player 和 obstacle 的 Obj
    void *Obj = NULL;

    // 確認玩家資料
    switch (player->label) {
        case Player1_L: {
            Obj = (Player1 *)(player->pDerivedObj);
            Player1 *playerObj = (Player1 *)Obj;
            player_x = playerObj->x;
            player_y = playerObj->y;
            player_width = playerObj->width[playerObj->ultimate == 1];
            player_height = playerObj->height[playerObj->ultimate == 1];
            break;
        }
        case Player2_L: {
            Obj = (Player2 *)(player->pDerivedObj);
            Player2 *playerObj = (Player2 *)Obj;
            player_x = playerObj->x;
            player_y = playerObj->y;
            player_width = playerObj->width[playerObj->ultimate == 1];
            player_height = playerObj->height[playerObj->ultimate == 1];
            break;
        }
    }

    // 確認障礙物資料
    switch (self->label) {
        case House_L: {
            Obj = (House *)(self->pDerivedObj);
            House *obstacleObj = (House *)Obj;
            obstacle_x = obstacleObj->x;
            obstacle_y = obstacleObj->y;
            obstacle_width = obstacleObj->width;
            obstacle_height = obstacleObj->height;
            break;
        }

        case Wood1_L: {
            Obj = (Wood1 *)(self->pDerivedObj);
            Wood1 *obstacleObj = (Wood1 *)Obj;
            obstacle_x = obstacleObj->x;
            obstacle_y = obstacleObj->y;
            obstacle_width = obstacleObj->width;
            obstacle_height = obstacleObj->height;
            break;
        }

        case Wood2_L: {
            Obj = (Wood2 *)(self->pDerivedObj);
            Wood2 *obstacleObj = (Wood2 *)Obj;
            obstacle_x = obstacleObj->x;
            obstacle_y = obstacleObj->y;
            obstacle_width = obstacleObj->width;
            obstacle_height = obstacleObj->height;
            break;
        }
    }

    // 計算距離
    int left_distance = abs(player_x - (obstacle_x - obstacle_width/2));
    int right_distance = abs((obstacle_x + obstacle_width/2) - player_x);
    int up_distance = abs(player_y - (obstacle_y - obstacle_height/2));
    int down_distance = abs((obstacle_y + obstacle_height/2) - player_y);

    // 找出最小距離並將角色移出障礙物
    int min_distance = left_distance;
    if (right_distance < min_distance) min_distance = right_distance;
    if (up_distance < min_distance) min_distance = up_distance;
    if (down_distance < min_distance) min_distance = down_distance;

    if (min_distance == left_distance) {
        player_x = - min_distance - player_width/2 - 1;
        player_y = 0;
    } else if (min_distance == right_distance) {
        player_x = min_distance + player_width/2 + 1;
        player_y = 0;
    } else if (min_distance == up_distance) {
        player_x = 0;
        player_y = - min_distance - player_height/2 - 1;
    } else if (min_distance == down_distance) {
        player_x = 0;
        player_y = min_distance + player_height/2 + 1;
    }

    // 更新玩家位置
    switch (player->label) {
        case Player1_L: {
            _Player1_update_position(player, player_x, player_y);
            break;
        }
        case Player2_L: {
            _Player2_update_position(player, player_x, player_y);
            break;
        }
    }
}

void position_correct_Conan(Elements *player , Elements * self){
    int player_x = 0, player_y = 0, player_width = 0, player_height = 0,dir = 0;
    int obstacle_x = 0, obstacle_y = 0, obstacle_width = 0, obstacle_height = 0;

    // 定義 player 和 obstacle 的 Obj
    void *Obj = NULL;

    // 確認玩家資料
    switch (player->label) {
        case Player1_L: {
            Obj = (Player1 *)(player->pDerivedObj);
            Player1 *playerObj = (Player1 *)Obj;
            player_x = playerObj->x;
            player_y = playerObj->y;
            dir = playerObj->dir;
            player_width = playerObj->width[playerObj->ultimate == 1];
            player_height = playerObj->height[playerObj->ultimate == 1];
            break;
        }
        case Player2_L: {
            Obj = (Player2 *)(player->pDerivedObj);
            Player2 *playerObj = (Player2 *)Obj;
            player_x = playerObj->x;
            player_y = playerObj->y;
            player_width = playerObj->width[playerObj->ultimate == 1];
            player_height = playerObj->height[playerObj->ultimate == 1];
            break;
        }
    }

    // 確認障礙物資料
    switch (self->label) {
        case House_L: {
            Obj = (House *)(self->pDerivedObj);
            House *obstacleObj = (House *)Obj;
            obstacle_x = obstacleObj->x;
            obstacle_y = obstacleObj->y;
            obstacle_width = obstacleObj->width;
            obstacle_height = obstacleObj->height;
            break;
        }

        case Wood1_L: {
            Obj = (Wood1 *)(self->pDerivedObj);
            Wood1 *obstacleObj = (Wood1 *)Obj;
            obstacle_x = obstacleObj->x;
            obstacle_y = obstacleObj->y;
            obstacle_width = obstacleObj->width;
            obstacle_height = obstacleObj->height;
            break;
        }

        case Wood2_L: {
            Obj = (Wood2 *)(self->pDerivedObj);
            Wood2 *obstacleObj = (Wood2 *)Obj;
            obstacle_x = obstacleObj->x;
            obstacle_y = obstacleObj->y;
            obstacle_width = obstacleObj->width;
            obstacle_height = obstacleObj->height;
            break;
        }
    }

    if (dir == LEFT) {
        player_x = (obstacle_x + obstacle_width/2 + player_width/2 + 1) - player_x;
    } else if (dir == RIGHT) {
        player_x = (obstacle_x - obstacle_width/2 - player_width/2 - 1) - player_x;
    } else if (dir == UP ) {
        player_y = (obstacle_y + obstacle_height/2 + player_height/2 + 1) - player_y;
    } else if (dir == DOWN) {
        player_y = (obstacle_y - obstacle_height/2 - player_height/2 - 1) - player_y;
    }

    // 更新玩家位置
    switch (player->label) {
        case Player1_L: {
            if (dir == LEFT || dir == RIGHT) {
                _Player1_update_position(player, player_x,0);
            } else if (dir == UP || dir == DOWN) {
                _Player1_update_position(player,0, player_y);
            }
            break;
        }
        case Player2_L: {
            if (dir == LEFT || dir == RIGHT) {
                _Player2_update_position(player, player_x,0);
            } else if (dir == UP || dir == DOWN) {
                _Player2_update_position(player,0, player_y);
            }
            break;
        }
    }
}

void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    // ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(Obj->background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}


