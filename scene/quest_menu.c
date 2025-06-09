#include <allegro5/allegro_audio.h>
#include "quest_menu.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/questNode.h"
#include "../element/projectile.h"
#include "../element/button.h"
#include "sceneManager.h"
/*
   [quest_menu function]
*/
Scene *New_quest_menu(int label, int next_secene, ALLEGRO_BITMAP *img)
{
    quest_menu *pDerivedObj = (quest_menu *)malloc(sizeof(quest_menu));
    Scene *pObj = New_Scene(label);
    pDerivedObj->next_scene=next_secene;
    pDerivedObj->background=img;
    // setting derived object member

    // switch(label){
    //     case quest_menu_phys_L:
    //         _Register_elements(pObj, New_button(StartButton_L, 100,50, al_load_bitmap("assets/image/start_button.png"), quest_gameScene_phys_L));
    //         break;
    //     case quest_menu_math_L:
    //         _Register_elements(pObj, New_button(StartButton_L, 100,50, al_load_bitmap("assets/image/start_button.png"), Math_gamescene_L));
    //         break;
    //     case quest_menu_lifeSci_L:
    //         _Register_elements(pObj, New_button(StartButton_L, 100,50, al_load_bitmap("assets/image/start_button.png"), quest_gameScene_lifeSci_L));
    //         break;
    //     case quest_menu_lake_L:
    //         _Register_elements(pObj, New_button(StartButton_L, 100,50, al_load_bitmap("assets/image/start_button.png"), quest_gameScene_lake_L));
    //         break;
    //     default:
    //         printf("menu label out of range: %d\n", label);
    //         break;

    // }
    
    pObj->pDerivedObj = pDerivedObj;
    
    // register element
    
    
    // setting derived object function
    pObj->Update = quest_menu_update;
    pObj->Draw = quest_menu_draw;
    pObj->Destroy = quest_menu_destroy;
    return pObj;
}
void quest_menu_update(Scene *self)
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
    if(key_state[ALLEGRO_KEY_ENTER]){
        self->scene_end=true;
        window = ((quest_menu*)self->pDerivedObj)->next_scene;
        key_state[ALLEGRO_KEY_ENTER]=0;
        // al_rest(0.1);
    }
}
void quest_menu_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    quest_menu *gs = ((quest_menu *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void quest_menu_destroy(Scene *self)
{
    quest_menu *Obj = ((quest_menu *)(self->pDerivedObj));
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
