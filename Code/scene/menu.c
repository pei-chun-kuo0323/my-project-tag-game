#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h> 
#include "menu.h"
#include <stdbool.h>
#include "../global.h"
/*
   [Menu function]
*/


float scale = 0,alpha = 0; 
Button Menubutton[2];
Button Storybutton[2];
Button Teachbutton[3];
Button Bonusbutton;
Button AboutButton;
Button ModeButton[3];
Button ChooseButton;
Btn Choose_character[13];

Scene *New_Menu(int label)
{
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->img[0] = al_load_bitmap("assets/image/menu.png");
    pDerivedObj->img[1] = al_load_bitmap("assets/image/aboutus.png");
    pDerivedObj->img[2] = al_load_bitmap("assets/image/story.png");
    pDerivedObj->img[3] = al_load_bitmap("assets/image/Teach.png");
    pDerivedObj->img[4] = al_load_bitmap("assets/image/Bonus.png");
    pDerivedObj->img[5] = al_load_bitmap("assets/image/mode.png");
    
    for(int i=0;i<6;i++){
        pDerivedObj->x[i]=0;
        pDerivedObj->y[i]=0;
    }
    pDerivedObj->x[4]=1320;
    pDerivedObj->y[4]=886;

    pDerivedObj->choose_Robot[0] = al_load_bitmap("assets/image/choose.0.png");
    pDerivedObj->choose_Robot[1] = al_load_bitmap("assets/image/choose.1.png");

    Menubutton[0].img[0] = al_load_bitmap("assets/image/button.0.0.png");
    Menubutton[0].img[1] = al_load_bitmap("assets/image/button.0.1.png");
    Menubutton[1].img[0] = al_load_bitmap("assets/image/about.0.0.png");
    Menubutton[1].img[1] = al_load_bitmap("assets/image/about.0.1.png");
    Menubutton[0].x = 760;
    Menubutton[0].y = 700;
    Menubutton[1].x = 0;
    Menubutton[1].y = 0;

    Storybutton[0].img[0] = al_load_bitmap("assets/image/Next.0.png");
    Storybutton[0].img[1] = al_load_bitmap("assets/image/Next.1.png");
    Storybutton[1].img[0] = al_load_bitmap("assets/image/arrow.0.png");
    Storybutton[1].img[1] = al_load_bitmap("assets/image/arrow.1.png");
    Storybutton[0].x = 1080;
    Storybutton[0].y = 800;
    Storybutton[1].x = 0;
    Storybutton[1].y = 920;

    Teachbutton[0].img[0] = al_load_bitmap("assets/image/Play.0.png");
    Teachbutton[0].img[1] = al_load_bitmap("assets/image/Play.1.png");
    Teachbutton[1].img[0] = al_load_bitmap("assets/image/arrow.0.png");
    Teachbutton[1].img[1] = al_load_bitmap("assets/image/arrow.1.png");
    Teachbutton[2].img[0] = al_load_bitmap("assets/image/Bonus_button.0.png");
    Teachbutton[2].img[1] = al_load_bitmap("assets/image/Bonus_button.1.png");
    Teachbutton[0].x = 1650;
    Teachbutton[0].y = 920;
    Teachbutton[1].x = 0;
    Teachbutton[1].y = 920;
    Teachbutton[2].x = 0;
    Teachbutton[2].y = 0;

    Bonusbutton.img[0] = al_load_bitmap("assets/image/exit_button.0.png");
    Bonusbutton.img[1] = al_load_bitmap("assets/image/exit_button.1.png");
    Bonusbutton.x = 1545;
    Bonusbutton.y = 22;

    AboutButton.img[0] = al_load_bitmap("assets/image/arrow.0.png");
    AboutButton.img[1] = al_load_bitmap("assets/image/arrow.1.png");
    AboutButton.x = 0;
    AboutButton.y = 920;

    ModeButton[0].img[0] = al_load_bitmap("assets/image/one_player.0.png");
    ModeButton[0].img[1] = al_load_bitmap("assets/image/one_player.1.png");
    ModeButton[1].img[0] = al_load_bitmap("assets/image/two_player.0.png");
    ModeButton[1].img[1] = al_load_bitmap("assets/image/two_player.1.png");
    ModeButton[2].img[0] = al_load_bitmap("assets/image/arrow.0.png");
    ModeButton[2].img[1] = al_load_bitmap("assets/image/arrow.1.png");
    ModeButton[0].x = 180;
    ModeButton[0].y = 100;
    ModeButton[1].x = 1140;
    ModeButton[1].y = 100;
    ModeButton[2].x = 0;
    ModeButton[2].y = 920;

    //選角介面按紐

    char file_path[50];
    const char *skin[5] = {"conan","kid","Angel","Heiji","Kazuha"};
    for (int dir = 0; dir < 5; dir++) {
        for (int frame = 0; frame < 2; frame++) {
            snprintf(file_path, sizeof(file_path), "assets/image/choose_%s.%d.png",skin[dir], frame);
            Choose_character[dir].img[frame] = al_load_bitmap(file_path);
        }
    }
    for (int dir = 5; dir < 10; dir++) {
        for (int frame = 0; frame < 2; frame++) {
            snprintf(file_path, sizeof(file_path), "assets/image/choose_%s.%d.png",skin[dir-5], frame);
            Choose_character[dir].img[frame] = al_load_bitmap(file_path);
        }
    }
    Choose_character[0].x = 100;
    Choose_character[1].x = 350;
    Choose_character[2].x = 600;
    Choose_character[3].x = 225;
    Choose_character[4].x = 475;
    for(int i=0;i<3;i++){
        Choose_character[i].y = 200;
    }
    for(int i=3;i<5;i++){
        Choose_character[i].y = 500;
    }
    for(int i=5;i<8;i++){
        Choose_character[i].y = 200;
    }
    for(int i=8;i<10;i++){
        Choose_character[i].y = 500;
    }

    Choose_character[5].x = 100+1040;
    Choose_character[6].x = 350+1040;
    Choose_character[7].x = 600+1040;
    Choose_character[8].x = 225+1040;
    Choose_character[9].x = 475+1040;
    for(int i=0;i<3;i++){
        Choose_character[i].y = 200;
    }
    for(int i=3;i<5;i++){
        Choose_character[i].y = 500;
    }

    Choose_character[10].img[0] = al_load_bitmap("assets/image/OK.0.png");
    Choose_character[10].img[1] = al_load_bitmap("assets/image/OK.1.png");
    Choose_character[11].img[0] = al_load_bitmap("assets/image/OK.0.png");
    Choose_character[11].img[1] = al_load_bitmap("assets/image/OK.1.png");
    Choose_character[10].x = 300;
    Choose_character[10].y = 800;
    Choose_character[11].x = 330+1040;
    Choose_character[11].y = 800;

    Choose_character[12].img[0] = al_load_bitmap("assets/image/arrow.0.png");
    Choose_character[12].img[1] = al_load_bitmap("assets/image/arrow.1.png");
    Choose_character[12].x = 0;
    Choose_character[12].y = 920;

    for(int i=0;i<12;i++){
        Choose_character[i].check = false;
    }

    pObj->pDerivedObj = pDerivedObj;
    // Load sound
    pDerivedObj->song[0] = al_load_sample("assets/sound/1.wav");
    pDerivedObj->song[1] = al_load_sample("assets/sound/2.ogg");
    pDerivedObj->song[2] = al_load_sample("assets/sound/3.ogg");
    al_reserve_samples(20);
    pDerivedObj->sample_instance[0] = al_create_sample_instance(pDerivedObj->song[0]);
    pDerivedObj->sample_instance[1] = al_create_sample_instance(pDerivedObj->song[1]);
    pDerivedObj->sample_instance[2] = al_create_sample_instance(pDerivedObj->song[2]);
    // Loop the song until the display closes
    for(int i=0;i<3;i++){
        al_set_sample_instance_playmode(pDerivedObj->sample_instance[i], ALLEGRO_PLAYMODE_LOOP);
        al_restore_default_mixer();
        al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance[i], al_get_default_mixer());

    }
    
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}
void menu_update(Scene *self)
{
    double mx = mouse.x, my = mouse.y;
    if(sceneNow == MENU){
        for(int i=0;i<2;i++){
            double w = al_get_bitmap_width(Menubutton[i].img[0]), h = al_get_bitmap_height(Menubutton[i].img[0]);
            double x = Menubutton[i].x, y = Menubutton[i].y;
            if(mx >= x && mx <= x + w && my >= y && my <= y + h && Menubutton[i].state == 2 && !mouse_state[1]){
                if(i == 0) sceneNow = STORY;
                else if(i == 1) sceneNow = ABOUTUS;
                Menubutton[i].state = 0;
            }
            if(mx >= x && mx <= x + w && my >= y && my <= y + h){
                Menubutton[i].state = mouse_state[1] ? 2 : 1, HoverOnItem = true;
            }else Menubutton[i].state = 0;
        }
    }
    else if(sceneNow == ABOUTUS){
        double w = al_get_bitmap_width(AboutButton.img[0]) , h = al_get_bitmap_height(AboutButton.img[0]) ;
        double x = AboutButton.x, y = AboutButton.y;
        if(mx >= x && mx <= x + w && my >= y && my <= y + h && AboutButton.state == 2 && !mouse_state[1]){
            sceneNow = MENU, AboutButton.state = 0;
        }
        if(mx >= x && mx <= x + w && my >= y && my <= y + h){
            AboutButton.state = mouse_state[1] ? 2 : 1, HoverOnItem = true;
        }else AboutButton.state = 0;
    }
    else if(sceneNow == STORY){
        for(int i=0;i<2;i++){
            double w = al_get_bitmap_width(Storybutton[i].img[0]), h = al_get_bitmap_height(Storybutton[i].img[0]);
            double x = Storybutton[i].x, y = Storybutton[i].y;
            if(mx >= x && mx <= x + w && my >= y && my <= y + h && Storybutton[i].state == 2 && !mouse_state[1]){
                if(i == 0) sceneNow = TEACH;
                else if(i == 1) sceneNow = MENU;
                Storybutton[i].state = 0;
            }
            if(mx >= x && mx <= x + w && my >= y && my <= y + h){
                Storybutton[i].state = mouse_state[1] ? 2 : 1, HoverOnItem = true;
            }
            else Storybutton[i].state = 0;
        }
    }
    else if(sceneNow == TEACH){
        for(int i=0;i<3;i++){
            double w = al_get_bitmap_width(Teachbutton[i].img[0]), h = al_get_bitmap_height(Teachbutton[i].img[0]);
            double x = Teachbutton[i].x, y = Teachbutton[i].y;
            if(mx >= x && mx <= x + w && my >= y && my <= y + h && Teachbutton[i].state == 2 && !mouse_state[1]){
                if(i == 0) sceneNow = MODE;
                else if(i == 1) sceneNow = STORY;
                else if(i == 2) sceneNow = BONUS;
                Teachbutton[i].state = 0;
            }
            if(mx >= x && mx <= x + w && my >= y && my <= y + h){
                Teachbutton[i].state = mouse_state[1] ? 2 : 1, HoverOnItem = true;
            }else Teachbutton[i].state = 0;
        }
    }
    else if(sceneNow == BONUS){
            double w = al_get_bitmap_width(Bonusbutton.img[0]), h = al_get_bitmap_height(Bonusbutton.img[0]);
            double x = Bonusbutton.x, y = Bonusbutton.y;
            if(mx >= x && mx <= x + w && my >= y && my <= y + h && Bonusbutton.state == 2 && !mouse_state[1]){
                sceneNow = PROCESS;
                Bonusbutton.state = 0;
            }
            if(mx >= x && mx <= x + w && my >= y && my <= y + h){
                Bonusbutton.state = mouse_state[1] ? 2 : 1, HoverOnItem = true;
            }else Bonusbutton.state = 0;
    }

    else if(sceneNow == MODE){
        for(int i=0;i<3;i++){
            double w = al_get_bitmap_width(ModeButton[i].img[0]), h = al_get_bitmap_height(ModeButton[i].img[0]);
            double x = ModeButton[i].x, y = ModeButton[i].y;
            if(mx >= x && mx <= x + w && my >= y && my <= y + h && ModeButton[i].state == 2 && !mouse_state[1]){
                if(i == 0) {
                    sceneNow = CHOOSE_CHARACTER;
                    robot = true;
                } 
                else if(i == 1) {
                    sceneNow = CHOOSE_CHARACTER;
                    robot = false;
                } 
                else if(i == 2) sceneNow = TEACH;
                ModeButton[i].state = 0;
            }
            if(mx >= x && mx <= x + w && my >= y && my <= y + h){
                ModeButton[i].state = mouse_state[1] ? 2 : 1, HoverOnItem = true;
            }else ModeButton[i].state = 0;
        }
    }

    if(sceneNow == CHOOSE_CHARACTER){
        for(int i=0;i<5;i++){
            if(!Choose_character[10].check)
            {
                double w = al_get_bitmap_width(Choose_character[i].img[0]), h = al_get_bitmap_height(Choose_character[i].img[0]);
                double x = Choose_character[i].x, y = Choose_character[i].y;
                if(mx >= x && mx <= x + w && my >= y && my <= y + h && Choose_character[i].state == 2 && !mouse_state[1]){
                    for(int i=0;i<5;i++){
                        Choose_character[i].state = 0;
                        Choose_character[i].check = false;
                    
                    }
                    player_1_chara = i;
                    Choose_character[i].check = true;
                    
                }
                if(mx >= x && mx <= x + w && my >= y && my <= y + h){
                    Choose_character[i].state = mouse_state[1] ? 2 : 1, HoverOnItem = true;
                }else if(!Choose_character[i].check) Choose_character[i].state = 0;
            }
            
        }
        for(int i=5;i<10;i++){
            if(!Choose_character[11].check){
                double w = al_get_bitmap_width(Choose_character[i].img[0]), h = al_get_bitmap_height(Choose_character[i].img[0]);
                double x = Choose_character[i].x, y = Choose_character[i].y;
                if(mx >= x && mx <= x + w && my >= y && my <= y + h && Choose_character[i].state == 2 && !mouse_state[1]){
                    for(int i=5;i<10;i++){
                        Choose_character[i].state = 0;
                        Choose_character[i].check = false;
                    
                    }
                    player_2_chara = i-5;
                    Choose_character[i].check = true;
                    
                }
                if(mx >= x && mx <= x + w && my >= y && my <= y + h){
                    Choose_character[i].state = mouse_state[1] ? 2 : 1, HoverOnItem = true;
                }else if(!Choose_character[i].check) Choose_character[i].state = 0;
            }
        }
        for(int i=10;i<11;i++){
            if(Choose_character[0].check||Choose_character[1].check||Choose_character[2].check||Choose_character[3].check||Choose_character[4].check)
            {
                double w = al_get_bitmap_width(Choose_character[i].img[0]), h = al_get_bitmap_height(Choose_character[i].img[0]);
                double x = Choose_character[i].x, y = Choose_character[i].y;
                if(mx >= x && mx <= x + w && my >= y && my <= y + h && Choose_character[i].state == 2 && !mouse_state[1]){
                    Choose_character[i].check = true;
                }
                if(mx >= x && mx <= x + w && my >= y && my <= y + h){
                    Choose_character[i].state = mouse_state[1] ? 2 : 1, HoverOnItem = true;
                }else if(!Choose_character[i].check) Choose_character[i].state = 0;
            }
        }
        for(int i=11;i<12;i++){
            if(Choose_character[5].check||Choose_character[6].check||Choose_character[7].check||Choose_character[8].check||Choose_character[9].check){
                double w = al_get_bitmap_width(Choose_character[i].img[0]), h = al_get_bitmap_height(Choose_character[i].img[0]);
                double x = Choose_character[i].x, y = Choose_character[i].y;
                if(mx >= x && mx <= x + w && my >= y && my <= y + h && Choose_character[i].state == 2 && !mouse_state[1]){
                    Choose_character[i].check = true;
                }
                if(mx >= x && mx <= x + w && my >= y && my <= y + h){
                    Choose_character[i].state = mouse_state[1] ? 2 : 1, HoverOnItem = true;
                }else if(!Choose_character[i].check) Choose_character[i].state = 0;
            }
        }
        for(int i=12;i<13;i++){
            double w = al_get_bitmap_width(Choose_character[i].img[0]), h = al_get_bitmap_height(Choose_character[i].img[0]);
            double x = Choose_character[i].x, y = Choose_character[i].y;
            if(mx >= x && mx <= x + w && my >= y && my <= y + h && Choose_character[i].state == 2 && !mouse_state[1]){
                sceneNow = MODE;
                for(int j=0;j<13;j++){
                    Choose_character[j].state = 0;
                }
            }
            if(mx >= x && mx <= x + w && my >= y && my <= y + h){
                Choose_character[i].state = mouse_state[1] ? 2 : 1, HoverOnItem = true;
            }else if(!Choose_character[i].check) Choose_character[i].state = 0;
        }
        
        if(Choose_character[10].check && Choose_character[11].check){
            self->scene_end = true;
            window = 1;
        }
    }
    else if(sceneNow == PROCESS){
        if(alpha<=0&&scale<=0) {
            sceneNow = TEACH;
        }
    }
    
}
void menu_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    int a=0,b=0,target_a = (WIDTH-Obj->x[sceneNow])/2,target_b = (HEIGHT-Obj->y[sceneNow])/2;
    if(sceneNow!=BONUS && sceneNow != PROCESS && sceneNow != CHOOSE_CHARACTER){
        al_draw_scaled_bitmap(Obj->img[sceneNow], 0, 0, 1920,1080,0,0,(WIDTH-Obj->x[sceneNow]),(HEIGHT-Obj->y[sceneNow]),0);
        if(sceneNow == MENU){
            al_set_sample_instance_gain(Obj->sample_instance[0],1);
            al_play_sample_instance(Obj->sample_instance[0]);
            al_set_sample_instance_playing(Obj->sample_instance[1], false);
            for(int i=0;i<2;i++){
                al_draw_bitmap(Menubutton[i].img[Menubutton[i].state>=1], Menubutton[i].x, Menubutton[i].y, 0);  
            }
        }
        if(sceneNow == ABOUTUS){
            for(int i=0;i<2;i++){
                al_draw_bitmap(AboutButton.img[AboutButton.state>=1], AboutButton.x, AboutButton.y, 0);  
            }
        }
        if(sceneNow == STORY){
            al_set_sample_instance_playing(Obj->sample_instance[0], false);
            al_set_sample_instance_gain(Obj->sample_instance[2],1);
            al_play_sample_instance(Obj->sample_instance[2]);
            for(int i=0;i<2;i++){
                al_draw_bitmap(Storybutton[i].img[Storybutton[i].state>=1], Storybutton[i].x, Storybutton[i].y, 0);  
            }
        }
        if(sceneNow == TEACH){
            al_set_sample_instance_playing(Obj->sample_instance[1], false);
            al_set_sample_instance_playing(Obj->sample_instance[2], true);
            al_set_sample_instance_gain(Obj->sample_instance[2],1);
            al_play_sample_instance(Obj->sample_instance[2]);
            for(int i=0;i<3;i++){
                al_draw_bitmap(Teachbutton[i].img[Teachbutton[i].state>=1], Teachbutton[i].x, Teachbutton[i].y, 0);  
            }
        }
        if(sceneNow == MODE){
            al_set_sample_instance_playing(Obj->sample_instance[2], true);
            al_set_sample_instance_gain(Obj->sample_instance[2],1);
            al_play_sample_instance(Obj->sample_instance[2]);
            for(int i=0;i<3;i++){
                al_draw_bitmap(ModeButton[i].img[ModeButton[i].state>=1], ModeButton[i].x, ModeButton[i].y, 0);  
            }
        }
        
    }
    else if(sceneNow == BONUS){
        al_set_sample_instance_playing(Obj->sample_instance[2], false);
        al_set_sample_instance_gain(Obj->sample_instance[1],1);
        al_play_sample_instance(Obj->sample_instance[1]);
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
        al_draw_scaled_bitmap(Obj->img[TEACH], 0, 0, 1920,1080,0,0,(WIDTH-Obj->x[TEACH]),(HEIGHT-Obj->y[TEACH]),0);
        if(alpha<0.5){
            alpha += 0.01;
            al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT,al_map_rgba_f(0, 0, 0, alpha) );
        }else{
            al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT,al_map_rgba_f(0, 0, 0, 0.7) );
        }
        
        if (scale < 1.0) {
            scale += 0.02; // 增加縮放比例
            a = target_a * scale; // 計算新位置
            b = target_b * scale;
            al_draw_scaled_bitmap(Obj->img[sceneNow],0, 0, 1320, 886,a, b, 1320* scale, 886 * scale,0);
        }
        else if(scale >= 1){
            al_draw_bitmap(Obj->img[sceneNow],target_a, target_b,0);
            al_draw_bitmap(Bonusbutton.img[Bonusbutton.state>=1],target_a+1245,target_b-75,0);
        }
    }
    
    else if(sceneNow == PROCESS){
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
        al_draw_scaled_bitmap(Obj->img[TEACH], 0, 0, 1920,1080,0,0,(WIDTH-Obj->x[TEACH]),(HEIGHT-Obj->y[TEACH]),0);
        for(int i=0;i<3;i++){
            al_draw_bitmap(Teachbutton[i].img[Teachbutton[i].state>=1], Teachbutton[i].x, Teachbutton[i].y, 0);  
        }

        if(alpha > 0.0){
            alpha -= 0.01;
            al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT,al_map_rgba_f(0, 0, 0, alpha) );
        }
        
        if (scale > 0.0) {
            scale -= 0.02; // 增加縮放比例
            a = (1920 - 1320)/2 * scale; // 計算新位置
            b = (1080 - 886)/2 * scale;
         al_draw_scaled_bitmap(Obj->img[BONUS],0, 0, 1320, 886,a, b, 1320* scale, 886 * scale,0);
        }
    }

    else if(sceneNow == CHOOSE_CHARACTER){
        al_draw_bitmap(Obj->choose_Robot[!robot],0,0,0);
        for(int i=0;i<13;i++){
            al_draw_bitmap(Choose_character[i].img[Choose_character[i].state>=1],Choose_character[i].x,Choose_character[i].y,0);
        }
    }
}
        
void menu_destroy(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    for(int i=0;i<3;i++){
        al_destroy_sample(Obj->song[i]);
        al_destroy_sample_instance(Obj->sample_instance[i]);
    }
    
    for(int i=0;i<5;i++){
        al_destroy_bitmap(Obj->img[i]);
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            al_destroy_bitmap(Menubutton[i].img[j]);
        }
    }
    free(Obj);
    free(self);
}
