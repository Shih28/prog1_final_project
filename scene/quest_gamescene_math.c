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
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/stage2.png");
    pDerivedObj->formula_img[0] = al_load_bitmap("assets/image/questionPicA.jpg");
    pDerivedObj->formula_img[1] = al_load_bitmap("assets/image/questionPicB.jpg");
    pDerivedObj->formula_img[2] = al_load_bitmap("assets/image/questionPicC.jpg");

    pDerivedObj->desc_imgs[0] = al_load_bitmap("assets/image/ansA.jpg");
    pDerivedObj->desc_imgs[1] = al_load_bitmap("assets/image/ansB.jpg");
    pDerivedObj->desc_imgs[2] = al_load_bitmap("assets/image/ansC.jpg");

    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_CharacterGauss(CharacterGauss_L));     //New_CharacterGuass()in characterNewton.c.h

    _Register_elements(pObj, New_Ball(Ball_L, 0, 600, 70));    //位置未測試，需要後續修正
    _Register_elements(pObj, New_Ball(Ball_L, 1, 600, 190));
    _Register_elements(pObj, New_Ball(Ball_L, 2, 600, 310));


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

    if (checkMatching(self)) {
        self->scene_end = true;
        window = GameScene_L;
        printf("in the if");
    }

}
void questGameMath_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    questGameMath *gs = ((questGameMath *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);

    //畫題目，位置未測試，需要後續修正
    al_draw_scaled_bitmap(gs->formula_img[0], 
        0, 0, 
        al_get_bitmap_width(gs->formula_img[0]), al_get_bitmap_height(gs->formula_img[0]), 
        100, 50,   // 目標位置 x, y
        300, 100,  // 目標大小 width, height
        0
    );
    al_draw_scaled_bitmap(gs->formula_img[1], 
        0, 0, 
        al_get_bitmap_width(gs->formula_img[1]), al_get_bitmap_height(gs->formula_img[1]), 
        100, 170,   // 目標位置 x, y
        300, 100,  // 目標大小 width, height
        0
    );
    al_draw_scaled_bitmap(gs->formula_img[2], 
        0, 0, 
        al_get_bitmap_width(gs->formula_img[2]), al_get_bitmap_height(gs->formula_img[2]), 
        100, 290,   // 目標位置 x, y
        300, 100,  // 目標大小 width, height
        0
    );

    //畫選項位置未測試，需要後續修正
    al_draw_scaled_bitmap(gs->desc_imgs[0],
        0, 0,
        al_get_bitmap_width(gs->desc_imgs[0]), al_get_bitmap_height(gs->desc_imgs[0]),
        50, 200,  // 目標位置 x, y
        250, 100,
        0
    );
    al_draw_scaled_bitmap(gs->desc_imgs[1],
        0, 0,
        al_get_bitmap_width(gs->desc_imgs[1]), al_get_bitmap_height(gs->desc_imgs[1]),
        170, 200,  // 目標位置 x, y
        250, 100,
        0
    );
    al_draw_scaled_bitmap(gs->desc_imgs[2],
        0, 0,
        al_get_bitmap_width(gs->desc_imgs[2]), al_get_bitmap_height(gs->desc_imgs[2]),
        290, 200,  // 目標位置 x, y
        250, 100,
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

int checkMatching(Scene *self) {
    ElementVec holes = _Get_label_elements(self, Hole_L);
    for (int i = 0; i < holes.len; i++) {
        hole *h = (hole *)(holes.arr[i]->pDerivedObj);
        if (!h->correct)
            return 0;
    }
    printf("All accepted!!!\n");
    return 1;
}
