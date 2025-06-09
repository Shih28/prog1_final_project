#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../element/couple.h"
#include "quest_gamescene_lake.h"
#include "../element/element.h"
#include "../element/bat.h"
#include "../element/button.h"
#include "sceneManager.h"
#include "../global.h"
#include "stdio.h"
int score_of_lake_quest=0;
int speed;

/*
   [questGameLake function]
*/
Scene *New_questGameLake(int label)
{
    questGameLake *pDerivedObj = (questGameLake *)malloc(sizeof(questGameLake));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/lake_bg.png");
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_bat(Bat_L));

    //initaialize timer
    al_set_timer_count(lake_gamescene_timer, 0);
    al_set_timer_count(couple_timer, 0);
    al_start_timer(lake_gamescene_timer);
    al_start_timer(couple_timer);

    //initialize score
    score_of_lake_quest=0;

    // setting derived object function
    pObj->Update = questGameLake_update;
    pObj->Draw = questGamelake_draw;
    pObj->Destroy = questGameLake_destroy;
    return pObj;
}

void questGameLake_update(Scene *self)
{

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

    double current_time = al_get_timer_count(lake_gamescene_timer);

    if(current_time>=180){
    int time_gap = 45+rand()%75; //fps
    double time_count = al_get_timer_count(couple_timer);
    if(time_count>time_gap){
        int type = (rand()%15);
        int pos_x = 200 + rand()%(WIDTH-200);
        int pos_y = 100 + (rand()%(HEIGHT-100));
        _Register_elements(self, New_couple(Couple_L, pos_x, pos_y, type));
        al_set_timer_count(couple_timer, 0);
        // printf("type: %d, dir: %s\n", type, picC[type]);
    }
    }

    if(current_time>=33*60){
        al_rest(1);
        self->scene_end=true;
        window=Lake_endscene_L;
    }

    if(key_state[ALLEGRO_KEY_P]){
        self->scene_end=true;
        window=Lake_endscene_L;
        
    }else if (key_state[ALLEGRO_KEY_B]){
        self->scene_end=true;
        window=GameScene_L;
    }

}
void questGamelake_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    questGameLake *gs = ((questGameLake *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
    ALLEGRO_FONT *font = al_load_font("assets/font/pirulen.ttf", 50, 0);
    ALLEGRO_FONT *ready = al_load_font("assets/font/pirulen.ttf", 100, 0);
    double current_time = al_get_timer_count(lake_gamescene_timer);
    char buf[15], scor[15];
    if(current_time<180){
        int countdown = 3-(int)(current_time/60);
        sprintf(buf, "%d", countdown);
        al_draw_text(ready, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, buf);
    }else{
        int game_countdown = 32-(int)(current_time/60);
        sprintf(buf, "TIME: %d", game_countdown);
        sprintf(scor, "SCORE: %d", score_of_lake_quest);
        al_draw_text(font, al_map_rgb(255,255,255), 10, 10, ALLEGRO_ALIGN_LEFT, buf);
        al_draw_text(font, al_map_rgb(255,255,255), WIDTH-50, 50, ALLEGRO_ALIGN_RIGHT, scor);
    }

}
void questGameLake_destroy(Scene *self)
{
    questGameLake *Obj = ((questGameLake *)(self->pDerivedObj));
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
}
