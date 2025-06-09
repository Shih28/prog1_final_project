#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "quest_gamescene_math.h"
#include "../element/element.h"
#include "../element/hole.h"
#include "../element/ball.h"
#include "../element/characterGauss.h"
#include "sceneManager.h"
#include "../global.h"
#include "stdio.h"
int score_of_Math_quest=0;



/*
   [questGameMath function]
*/
Scene *New_questGameMath(int label)
{
    questGameMath *pDerivedObj = (questGameMath *)malloc(sizeof(questGameMath));
    Scene *pObj = New_Scene(label);
    pObj->pDerivedObj = pDerivedObj;

    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/math_bg.png");
    pDerivedObj->formula_img[0] = al_load_bitmap("assets/image/questionPicA.jpg");
    pDerivedObj->formula_img[1] = al_load_bitmap("assets/image/questionPicB.jpg");
    pDerivedObj->formula_img[2] = al_load_bitmap("assets/image/questionPicC.jpg");

    pDerivedObj->desc_imgs[0] = al_load_bitmap("assets/image/ansA.jpg");
    pDerivedObj->desc_imgs[1] = al_load_bitmap("assets/image/ansB.jpg");
    pDerivedObj->desc_imgs[2] = al_load_bitmap("assets/image/ansC.jpg");

    score_of_Math_quest=0;


    // register element
    _Register_elements(pObj, New_CharacterGauss(CharacterGauss_L));     
    //New_CharacterGuass()in characterNewton.c.h

    _Register_elements(pObj, New_hole(Hole_L, 1, 850, 1120));    //位置未測試，需要後續修正
    _Register_elements(pObj, New_hole(Hole_L, 2, 1200, 1120));
    _Register_elements(pObj, New_hole(Hole_L, 0, 1550, 1120));

    _Register_elements(pObj, New_Ball(Ball_L, 0, 100, 1000));    //位置未測試，需要後續修正
    _Register_elements(pObj, New_Ball(Ball_L, 1, 400, 1000));
    _Register_elements(pObj, New_Ball(Ball_L, 2, 700, 1000));

    // setting derived object function
    pObj->Update = questGameMath_update;
    pObj->Draw = questGameMath_draw;
    pObj->Destroy = questGameMath_destroy;
    return pObj;
}

void questGameMath_update(Scene *self)
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

    if (key_state[ALLEGRO_KEY_B]){
        self->scene_end=true;
        window=GameScene_L;
    }
    if(key_state[ALLEGRO_KEY_P]){
        self->scene_end=true;
        window=Math_endscene_L;
    }
    if (all_holes_have_balls(self) && key_state[ALLEGRO_KEY_SPACE]) {
        checkMatching(self);
        
        self->scene_end = true;
        window = Math_endscene_L;
        key_state[ALLEGRO_KEY_SPACE]=0;
        al_rest(0.1);
        printf("in the if");
    }

}

void questGameMath_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    questGameMath *gs = ((questGameMath *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);


    //畫題目
    al_draw_scaled_bitmap(gs->formula_img[0], 
        0, 0, 
        al_get_bitmap_width(gs->formula_img[0]), al_get_bitmap_height(gs->formula_img[0]), 
        100, 100,   // 目標位置 y, x
        //263, 256,  // 目標大小 width, height
        364,400,
        0
    );
    al_draw_scaled_bitmap(gs->formula_img[1], 
        0, 0, 
        al_get_bitmap_width(gs->formula_img[1]), al_get_bitmap_height(gs->formula_img[1]), 
        700, 100,   // 目標位置 y, x
        //233, 256,  // 目標大小 width, height
        364,400,
        0
    );
    al_draw_scaled_bitmap(gs->formula_img[2], 
        0, 0, 
        al_get_bitmap_width(gs->formula_img[2]), al_get_bitmap_height(gs->formula_img[2]), 
        1300, 100,   // 目標位置 y, x
        //242, 235,  // 目標大小 width, height
        379,368,
        0
    );

    //畫選項
    al_draw_scaled_bitmap(gs->desc_imgs[0],
        0, 0,
        al_get_bitmap_width(gs->desc_imgs[0]), al_get_bitmap_height(gs->desc_imgs[0]),
        1150, 600,  // 目標位置 y, x
        595, 54,
        0
    );
    al_draw_scaled_bitmap(gs->desc_imgs[1],
        0, 0,
        al_get_bitmap_width(gs->desc_imgs[1]), al_get_bitmap_height(gs->desc_imgs[1]),
        580, 890,  // 目標位置 y, x
        677, 55,
        0
    );
    al_draw_scaled_bitmap(gs->desc_imgs[2],
        0, 0,
        al_get_bitmap_width(gs->desc_imgs[2]), al_get_bitmap_height(gs->desc_imgs[2]),
        970, 770,  // 目標位置 y, x
        628, 58,
        0
    );

    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }


}
void questGameMath_destroy(Scene *self)
{
    questGameMath *Obj = ((questGameMath *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    for (int i = 0; i < 3; i++) {
        al_destroy_bitmap(Obj->formula_img[i]);
    }
    for (int i = 0; i < 3; i++) {
        al_destroy_bitmap(Obj->desc_imgs[i]);
    }
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}

void checkMatching(Scene *self) {
    ElementVec holes = _Get_label_elements(self, Hole_L);
    for(int i=0; i<holes.len; i++){
        hole *h = (hole*)holes.arr[i]->pDerivedObj;
        ball *b = (ball*)h->ball_in_hole->pDerivedObj;
        if(h->id==b->id) score_of_Math_quest+=5;
    }   
}

int all_holes_have_balls(Scene *self){
    ElementVec holes = _Get_label_elements(self, Hole_L);
    for(int i=0; i<holes.len; i++){
        hole *h = (hole*)holes.arr[i]->pDerivedObj;
        if(h->ball_in_hole==NULL) return 0;
    }
    return 1;
}