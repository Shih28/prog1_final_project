#include <allegro5/allegro_audio.h>
#include "quest_gamescene_3.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/questNode.h"
#include "../element/projectile.h"
#include "../element/button.h"
#include "../global.h"
/*
   [questGame3 function]
*/
Scene *New_questGame3(int label)
{
    questGame3 *pDerivedObj = (questGame3 *)malloc(sizeof(questGame3));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/stage.jpg");
    pObj->pDerivedObj = pDerivedObj;
    // register element
    
    
    // setting derived object function
    pObj->Update = questGame3_update;
    pObj->Draw = questGame3_draw;
    pObj->Destroy = questGame3_destroy;
    return pObj;
}
void questGame3_update(Scene *self)
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
void questGame3_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    questGame3 *gs = ((questGame3 *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void questGame3_destroy(Scene *self)
{
    questGame3 *Obj = ((questGame3 *)(self->pDerivedObj));
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
