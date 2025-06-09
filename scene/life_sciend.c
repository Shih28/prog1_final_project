#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "life_sciend.h"
#include "quest_gamescene_lifeSci.h"
#include "sceneManager.h"
#include <stdbool.h>
/*
   [lakeEndscene function]
*/
Scene *New_life_sciend(int label)
{
    life_sciend *pDerivedObj = (life_sciend*)malloc(sizeof(life_sciend));
    Scene *pObj = New_Scene(label);
    pDerivedObj->img=al_load_bitmap("assets/image/life_sci_2.png");
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 95, 0);
    
    pObj->pDerivedObj = pDerivedObj;

    //set score
    //sprintf(pDerivedObj->score, "%d", score_of_lake_quest);

    // setting derived object function
    pObj->Update = life_sciend_update;
    pObj->Draw = life_sciend_draw;
    pObj->Destroy = life_sciend_destroy;
    return pObj;
}
void life_sciend_update(Scene *self)
{
    if (key_state[ALLEGRO_KEY_ENTER])
    {
        self->scene_end = true;
        QuestComp[QuestLifeSci_L]=1;
        window = GameScene_L;
    }
}
void life_sciend_draw(Scene *self)
{
    life_sciend *Obj = ((life_sciend *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img,0,0,0);
    //al_draw_text(Obj->font, al_map_rgb(0,0,0), 1365 ,528, ALLEGRO_ALIGN_CENTRE, Obj->score);
    
}
void life_sciend_destroy(Scene *self)
{
    life_sciend *Obj = ((life_sciend *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
