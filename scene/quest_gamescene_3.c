#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "quest_gamescene_3.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/questNode.h"
#include "../element/projectile.h"
#include "../element/button.h"
#include "../element/dna.h"
#include "sceneManager.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
#include <stdbool.h>

int score = 0;
int current_keycode = -1;
/*
   [questGame3 function]
*/
Scene *New_questGame3(int label)
{
    questGame3 *pDerivedObj = (questGame3 *)malloc(sizeof(questGame3));
    Scene *pObj = New_Scene(label);

    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/phys.png");
    pObj->pDerivedObj = pDerivedObj;

    score = 0;
    current_keycode = -1;

    // 建立最初 DNA 或其他初始元素（例：產生四個初始 DNA）
    /*
    for (int i = 0; i < 4; i++) {
        Elements *dna = New_dna(3, 100 + i * 150, 200, 2); // x 間隔位置，自行調整
        _Register_elements(pObj, dna);
    }
    */
    al_set_timer_count(lifeSci_gamescene_timer, 0);
    al_start_timer(lifeSci_gamescene_timer);

    // setting derived object function
    pObj->Update = questGame3_update;
    pObj->Draw = questGame3_draw;
    pObj->Destroy = questGame3_destroy;

    return pObj;
}

void questGame3_update(Scene *self)
{
    // 偵測是否有輸入（只取一個鍵）
    if (key_state[ALLEGRO_KEY_A]){
        current_keycode = ALLEGRO_KEY_A;
    }
    else if (key_state[ALLEGRO_KEY_T]) {
        current_keycode = ALLEGRO_KEY_T;
    }
    else if (key_state[ALLEGRO_KEY_C]) {
        current_keycode = ALLEGRO_KEY_C;
    }
    else if (key_state[ALLEGRO_KEY_G]) {
        current_keycode = ALLEGRO_KEY_G;
    }
    // update every element
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->Update)
            ele->Update(ele);
    }
    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->Interact)
            ele->Interact(ele);
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
    static int dna_timer = 0;
    dna_timer++;
    if (dna_timer >= 60) { // 每 60 幀（約 1 秒）產生一個
        Elements *dna = New_dna(dna_L, 0, 200, 3); // 從左側進入
        _Register_elements(self, dna);
        dna_timer = 0;
    }

    double current_time = al_get_timer_count(lifeSci_gamescene_timer);
    if(current_time>=FPS*30)
    {
        self->scene_end=true;
        window=GameScene_L;
    }
    
}
void questGame3_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    questGame3 *gs = ((questGame3 *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }

    double ct = al_get_timer_count(lifeSci_gamescene_timer);
    ALLEGRO_FONT *font = al_load_font("assets/font/pirulen.ttf", 50, 0);
    char buf[15], buf_time[15];
    if(ct <=30*FPS){
        int time = 30 - ((int)ct/60);
        sprintf(buf, "SCORE: %d", score);
        sprintf(buf_time, "TIME: %d", time);
        al_draw_text(font, al_map_rgb(255,255,255), WIDTH-50, 50, ALLEGRO_ALIGN_RIGHT, buf);
        al_draw_text(font, al_map_rgb(255,255,255), 50, 50, ALLEGRO_ALIGN_LEFT, buf_time);
        
    }

}
void questGame3_destroy(Scene *self)
{
    questGame3 *Obj = ((questGame3 *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    al_stop_timer(lifeSci_gamescene_timer);
    free(Obj);
    free(self);
}