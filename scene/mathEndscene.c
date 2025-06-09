#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "mathEndscene.h"
#include "quest_gamescene_math.h"
#include "sceneManager.h"
#include <stdbool.h>
/*
   [mathEndscene function]
*/
Scene *New_mathEndscene(int label)
{
    mathEndscene *pDerivedObj = (mathEndscene*)malloc(sizeof(mathEndscene));
    Scene *pObj = New_Scene(label);
    pDerivedObj->img=al_load_bitmap("assets/image/math_end.png");
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 95, 0);
    pObj->pDerivedObj = pDerivedObj;

    //set score
    sprintf(pDerivedObj->score, "%d", score_of_Math_quest);

    // setting derived object function
    pObj->Update = mathEndscene_update;
    pObj->Draw = mathEndscene_draw;
    pObj->Destroy = mathEndscene_destroy;
    return pObj;
}
void mathEndscene_update(Scene *self)
{
    if (key_state[ALLEGRO_KEY_ENTER])
    {
        self->scene_end = true;
        QuestComp[QuestMath_L]=1;
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
void mathEndscene_draw(Scene *self)
{
    mathEndscene *Obj = ((mathEndscene *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img,0,0,0);
    al_draw_text(Obj->font, al_map_rgb(0,0,0), 970 ,610, ALLEGRO_ALIGN_CENTRE, Obj->score);
    
}
void mathEndscene_destroy(Scene *self)
{
    mathEndscene *Obj = ((mathEndscene *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
