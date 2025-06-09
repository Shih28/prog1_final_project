#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "finalEndscene.h"
#include "quest_gamescene_phys.h"
#include "sceneManager.h"
#include <stdbool.h>
/*
   [finalEndscene function]
*/
Scene *New_finalEndscene(int label)
{
    finalEndscene *pDerivedObj = (finalEndscene*)malloc(sizeof(finalEndscene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    char buf[40];
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 95, 0);
    for(int i=0; i<3; i++){
        sprintf(buf, "assets/image/end_%d", i);
        pDerivedObj->img[i] = al_load_bitmap(buf);
    }


    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = finalEndscene_update;
    pObj->Draw = finalEndscene_draw;
    pObj->Destroy = finalEndscene_destroy;
    return pObj;
}
void finalEndscene_update(Scene *self)
{
    if (key_state[ALLEGRO_KEY_ENTER])
    {
        self->scene_end = true;
        window = GameScene_L;
    }
    return;
}
void finalEndscene_draw(Scene *self)
{
    finalEndscene *Obj = ((finalEndscene *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img[0], 0,0,0);
}
void finalEndscene_destroy(Scene *self)
{
    finalEndscene *Obj = ((finalEndscene *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
