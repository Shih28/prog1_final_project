#include "questNode.h"
#include "../global.h"
#include "../scene/sceneManager.h"
#include <allegro5/allegro_primitives.h>
#include "../shapes/Rectangle.h"
#include "../shapes/Circle.h"
#include "../shapes/Point.h"
/*
   [tree function]
*/
Elements *New_questNode(int label, int x, int y, int change_scene, ALLEGRO_BITMAP *img)
{
    questNode *pDerivedObj = (questNode *)malloc(sizeof(questNode));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->change_scene=change_scene;
    pDerivedObj->img = img;
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    double r = pDerivedObj->width>=pDerivedObj->height? pDerivedObj->height:pDerivedObj->width;
    pDerivedObj->hitbox =  New_Circle(x+pDerivedObj->width*0.5, y+pDerivedObj->height*0.5, r*0.15);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = questNode_update;
    pObj->Interact = questNode_interact;
    pObj->Draw = questNode_draw;
    pObj->Destroy = questNode_destroy;
    return pObj;
}
void questNode_update(Elements *self) {}
void questNode_interact(Elements *self) {}
void questNode_draw(Elements *self)
{
    questNode *Obj = ((questNode *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    // al_draw_rectangle(Obj->x+Obj->width*0.4, Obj->y+Obj->height*0.3, Obj->width*0.7+Obj->x, Obj->height*0.6+Obj->y, al_map_rgb(255,255,255), 1);
    // float r = Obj->height>=Obj->width? Obj->width:Obj->height;
    // al_draw_circle(Obj->x+Obj->width*0.5, Obj->y+Obj->height*0.5, r*0.15, al_map_rgb(255,255,255), 1);
    
}
void questNode_destroy(Elements *self)
{
    questNode *Obj = ((questNode *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
