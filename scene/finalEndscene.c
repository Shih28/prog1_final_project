#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "finalEndscene.h"
#include "finalEndscene.h"
#include "quest_gamescene_lake.h"
#include "quest_gamescene_lifeSci.h"
#include "quest_gamescene_phys.h"
#include "sceneManager.h"
#include <stdbool.h>
/*
   [finalEndscene function]
*/
int total_score=0;
Scene *New_finalEndscene(int label)
{
    finalEndscene *pDerivedObj = (finalEndscene*)malloc(sizeof(finalEndscene));
    Scene *pObj = New_Scene(label);
    pDerivedObj->img=al_load_bitmap("assets/image/end_2.png");
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 200, 0);
    
    pObj->pDerivedObj = pDerivedObj;

    //set score
    total_score=score_of_lake_quest+score_of_lifeSci+score_of_phys_quest;

    // setting derived object function
    pObj->Update = finalEndscene_update;
    pObj->Draw = finalEndscene_draw;
    pObj->Destroy = finalEndscene_destroy;
    return pObj;
}
void finalEndscene_update(Scene *self)
{
    if (key_state[ALLEGRO_KEY_0])
    {
        self->scene_end = true;
        memset(QuestComp,0,sizeof(int));
        window=GameScene_L;
    }
    return;
}
void finalEndscene_draw(Scene *self)
{
    finalEndscene *Obj = ((finalEndscene *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img,0,0,0);
    char buf[15];
    sprintf(buf, "%d", total_score);
    al_draw_text(Obj->font, al_map_rgb(255,255,255), 580 ,400, ALLEGRO_ALIGN_CENTRE, buf);
    
}
void finalEndscene_destroy(Scene *self)
{
    finalEndscene *Obj = ((finalEndscene *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
