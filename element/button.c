#include "button.h"
#include "../shapes/Rectangle.h"
#include "../scene/sceneManager.h"
#include "../scene/quest_menu.h"
#include "../shapes/Shape.h"
#include "../shapes/Point.h"
#include "../scene/quest_gamescene_lake.h"


Elements *New_button(int label, int x, int y, ALLEGRO_BITMAP *img, ALLEGRO_BITMAP *img2, int v){
    button *pDerivedObj = (button*)malloc(sizeof(button));
    Elements* pobj = New_Elements(label);
    
    pDerivedObj->x=x;
    pDerivedObj->y=y;
    pDerivedObj->img[0]=img;
    pDerivedObj->img[1]=img2;
    pDerivedObj->display=img;
    pDerivedObj->gamespeed=v;
    pDerivedObj->width = al_get_bitmap_width(img);
    pDerivedObj->height = al_get_bitmap_height(img);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);

    pobj->pDerivedObj=pDerivedObj;
    pobj->Update=button_update;
    pobj->Interact=button_interact;
    pobj->Draw=button_draw;
    pobj->Destroy=button_destroy;

    return pobj;
}

void button_update(Elements *self){
    
    button *obj = (button*)self->pDerivedObj;
    if(obj->hitbox->overlap(New_Point(mouse.x, mouse.y), obj->hitbox)){
        obj->display=obj->img[1];
        if(mouse_state[1]){
            scene->scene_end=true;
            window=quest_gameScene_lake_L;
        }
    }else{
        obj->display=obj->img[0];
    }
}

void button_interact(Elements *self){
}


void button_draw(Elements *self){

    button *obj = (button*)self->pDerivedObj;
    al_draw_bitmap(obj->img[0], obj->x, obj->y, 0);
}

void button_destroy(Elements *self){
    button *obj=(button*)self->pDerivedObj;
    al_destroy_bitmap(obj->img[0]);
    al_destroy_bitmap(obj->img[1]);
    
    free(obj->hitbox);
    free(obj);
    free(self);
}
