#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "quest_gamescene_phys.h"
#include "../element/element.h"
#include "../element/characterNewton.h"
#include "sceneManager.h"
#include "../element/apple.h"
#include "../element/button.h"
#include "../global.h"
#include <stdlib.h>
#include <stdio.h>

int score_of_phys_quest;
int run=0;
/*
   [questGamePhys function]
*/
Scene *New_questGamePhys(int label)
{
    questGamePhys *pDerivedObj = (questGamePhys *)malloc(sizeof(questGamePhys));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/phys_bg.png");
    pObj->pDerivedObj = pDerivedObj;

    //initialize score
    score_of_phys_quest=0;

    //start timer
    al_set_timer_count(phys_gamescene_timer, 0);
    al_set_timer_count(apple_timer, 0);
    al_start_timer(phys_gamescene_timer);
    al_start_timer(apple_timer);

    // register element
    _Register_elements(pObj, New_CharacterNewton(CharacterNewton_L));
    

    // setting derived object function
    pObj->Update = questGamePhys_update;
    pObj->Draw = questGamePhys_draw;
    pObj->Destroy = questGamePhys_destroy;
    return pObj;
}
void questGamePhys_update(Scene *self)
{
    double c_time = al_get_timer_count(phys_gamescene_timer);
    // printf("phys_timer: %lf\n", c_time);
   if(c_time>=180){
        //add apple 
        double apple_time = al_get_timer_count(apple_timer);
        bool add = (60-apple_time)<=0; //time count:FPS
        if(add){
            addApple(self);
            al_set_timer_count(apple_timer, 0);
        }
    }

    if(c_time>=33*FPS){
        al_rest(1);
        self->scene_end=true;
        window=Phys_endscene_L;
    }

    if(key_state[ALLEGRO_KEY_P]){
        self->scene_end=true;
        window=Phys_endscene_L;
        
    }else if (key_state[ALLEGRO_KEY_B]){
        self->scene_end=true;
        window=GameScene_L;
    }
    
    

    // update every element
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Update(ele);
    }
    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Interact(ele);
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
}
void questGamePhys_draw(Scene *self)
{
   
    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    questGamePhys *gs = ((questGamePhys *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
    char buf[15], c[15];
    ALLEGRO_FONT *font = al_load_ttf_font("assets/font/pirulen.ttf", 50, 0);
    ALLEGRO_FONT *ready = al_load_ttf_font("assets/font/pirulen.ttf", 100, 0);
    double cur_time = al_get_timer_count(phys_gamescene_timer);

    if(cur_time<180){
        sprintf(c, "%d", 3-(int)(cur_time/60));
        al_draw_text(ready, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, c);
    }else{
        int time_left = 32-(int)(cur_time/60);
        sprintf(c, "TIME: %d", time_left);
        al_draw_text(font, al_map_rgb(255,255,255), 10, 10, ALLEGRO_ALIGN_LEFT, c);
        sprintf(buf, "SCORE: %d", score_of_phys_quest);
        al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH-50, 50, ALLEGRO_ALIGN_RIGHT, buf);
    }

}
void questGamePhys_destroy(Scene *self)
{
    questGamePhys *Obj = ((questGamePhys *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
    al_stop_timer(apple_timer);
    al_stop_timer(phys_gamescene_timer);
    al_stop_timer(apple_timer);
}

void addApple(Scene* self){
    int type_of_apple = rand()%2;
    int pos_x = 150+rand()%(WIDTH-150);
    int pos_y = -100;
    int pic_of_apple = rand()%10;
    _Register_elements(self, New_apple(type_of_apple, pos_x, pos_y, 3, pic_of_apple));
}
