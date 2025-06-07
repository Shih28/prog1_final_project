#include "bat.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro_font.h>
#include "../scene/quest_gamescene_lake.h" // for element label
#include "../scene/sceneManager.h" // for scene variable
/*
   [bat function]
*/

char bat_pic[2][50]={
    {"assets/image/node.png"},
    {"assets/image/projectile.png"}
};

Elements *New_bat(int label)
{
    bat *pDerivedObj = (bat *)malloc(sizeof(bat));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap(bat_pic[0]);
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = mouse.x;
    pDerivedObj->y = mouse.y;
    pDerivedObj->status = 0; //default; 1:attack
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
   
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = bat_update;
    pObj->Interact = bat_interact;
    pObj->Draw = bat_draw;
    pObj->Destroy = bat_destory;

    return pObj;
}
void bat_update(Elements *self)
{
    bat *Obj = ((bat *)(self->pDerivedObj));
    Obj->x = mouse.x;
    Obj->y = mouse.y;
    if(Obj->status!=mouse_state[1]){
        Obj->status=mouse_state[1];
        Obj->img = al_load_bitmap(bat_pic[Obj->status]);
    }
    
}



void bat_interact(Elements *self)
{
    for (int j = 0; j < self->inter_len; j++)
    {
        int inter_label = self->inter_obj[j];
        ElementVec labelEle = _Get_label_elements(scene, inter_label);
        
        for (int i = 0; i < labelEle.len; i++)
        {
            
        }
    }
}

void bat_draw(Elements *self)
{
    bat *Obj = ((bat *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_ALIGN_CENTRE);
}
void bat_destory(Elements *self)
{
    bat *Obj = ((bat *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
