#include "questNode.h"
#include "../global.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
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
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width/3,
                                        pDerivedObj->y + pDerivedObj->width/3,
                                        pDerivedObj->x +  2*pDerivedObj->width/3,
                                        pDerivedObj->y +  2*pDerivedObj->height/3);
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
    
}
void questNode_destroy(Elements *self)
{
    questNode *Obj = ((questNode *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
