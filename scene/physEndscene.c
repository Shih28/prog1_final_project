#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "physEndscene.h"
#include "quest_gamescene_phys.h"
#include "sceneManager.h"
#include <stdbool.h>
/*
   [physEndscene function]
*/
Scene *New_physEndscene(int label)
{
    physEndscene *pDerivedObj = (physEndscene*)malloc(sizeof(physEndscene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 95, 0);

    pDerivedObj->img = al_load_bitmap("assets/image/phys_end.png");

    sprintf(pDerivedObj->score, "%d", score_of_phys_quest);
   
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = physEndscene_update;
    pObj->Draw = physEndscene_draw;
    pObj->Destroy = physEndscene_destroy;
    return pObj;
}
void physEndscene_update(Scene *self)
{
    if (key_state[ALLEGRO_KEY_ENTER])
    {
        self->scene_end = true;
        QuestComp[QuestPhys_L]=1;
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
void physEndscene_draw(Scene *self)
{
    physEndscene *Obj = ((physEndscene *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, 0,0,0);
    al_draw_text(Obj->font, al_map_rgb(0,0,0), 1205, 500, ALLEGRO_ALIGN_CENTRE, Obj->score);
}
void physEndscene_destroy(Scene *self)
{
    physEndscene *Obj = ((physEndscene *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
