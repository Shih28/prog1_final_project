#include <allegro5/allegro_audio.h>
#include "quest_gamescene_2.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/questNode.h"
#include "../element/projectile.h"
#include "../element/button.h"
#include "../global.h"
/*
   [questGame2 function]
*/
Scene *New_questGame2(int label)
{
    questGame2 *pDerivedObj = (questGame2 *)malloc(sizeof(questGame2));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/stage.jpg");
    pObj->pDerivedObj = pDerivedObj;
    // register element

    

    // setting derived object function
    pObj->Update = questGame2_update;
    pObj->Draw = questGame2_draw;
    pObj->Destroy = questGame2_destroy;
    return pObj;
}
void questGame2_update(Scene *self)
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
void questGame2_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    questGame2 *gs = ((questGame2 *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void questGame2_destroy(Scene *self)
{
    questGame2 *Obj = ((questGame2 *)(self->pDerivedObj));
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
