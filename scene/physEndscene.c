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

    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/physEndscene.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
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
        window = GameScene_L;
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
