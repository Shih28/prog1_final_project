#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "lakeEndscene.h"
#include "quest_gamescene_lake.h"
#include "sceneManager.h"
#include <stdbool.h>
/*
   [lakeEndscene function]
*/
Scene *New_lakeEndscene(int label)
{
    lakeEndscene *pDerivedObj = (lakeEndscene*)malloc(sizeof(lakeEndscene));
    Scene *pObj = New_Scene(label);
    pDerivedObj->img=al_load_bitmap("assets/image/lake_end.png");
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 95, 0);
    pObj->pDerivedObj = pDerivedObj;

    //set score
    sprintf(pDerivedObj->score, "%d", score_of_lake_quest);

    // setting derived object function
    pObj->Update = lakeEndscene_update;
    pObj->Draw = lakeEndscene_draw;
    pObj->Destroy = lakeEndscene_destroy;
    return pObj;
}
void lakeEndscene_update(Scene *self)
{
    if (key_state[ALLEGRO_KEY_ENTER])
    {
        self->scene_end = true;
        QuestComp[QuestLake_L]=1;
        key_state[ALLEGRO_KEY_ENTER]=0;
        for(int i=0; i<4; i++){
            if(QuestComp[i]==0){
                window = GameScene_L;
                break;
            }
            if(i==3 && QuestComp[i]) window=outro_1_L;
        }
    }
    return;
}
void lakeEndscene_draw(Scene *self)
{
    lakeEndscene *Obj = ((lakeEndscene *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img,0,0,0);
    al_draw_text(Obj->font, al_map_rgb(0,0,0), 1365 ,528, ALLEGRO_ALIGN_CENTRE, Obj->score);
    
}
void lakeEndscene_destroy(Scene *self)
{
    lakeEndscene *Obj = ((lakeEndscene *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
