#include <allegro5/allegro_audio.h>
#include "quest_gamescene_lake.h"
#include "../element/element.h"
#include "../element/bat.h"
#include "../element/button.h"
/*
   [questGameLake function]
*/
Scene *New_questGameLake(int label)
{
    questGameLake *pDerivedObj = (questGameLake *)malloc(sizeof(questGameLake));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/stage.jpg");
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_bat(Bat_L));
    

    // setting derived object function
    pObj->Update = questGameLake_update;
    pObj->Draw = questGamelake_draw;
    pObj->Destroy = questGameLake_destroy;
    return pObj;
}
void questGameLake_update(Scene *self)
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
}
void questGamelake_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    questGameLake *gs = ((questGameLake *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void questGameLake_destroy(Scene *self)
{
    questGameLake *Obj = ((questGameLake *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}
