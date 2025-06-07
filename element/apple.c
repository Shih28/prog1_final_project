#include "apple.h"
#include "questNode.h"
#include "../shapes/Circle.h"
#include "../scene/quest_gamescene_phys.h" // for element label
#include "../scene/sceneManager.h" // for scene variable
/*
   [apple function]
*/
Elements *New_apple(int label, int x, int y, int v)
{
    apple *pDerivedObj = (apple *)malloc(sizeof(apple));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/projectile.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->v = v;
    pDerivedObj->type = label;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
   
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = apple_update;
    pObj->Interact = apple_interact;
    pObj->Draw = apple_draw;
    pObj->Destroy = apple_destory;

    return pObj;
}
void apple_update(Elements *self)
{
    apple *Obj = ((apple *)(self->pDerivedObj));
    _apple_update_position(self, 0, Obj->v);
    _apple_interact_Floor(self);
}
void _apple_update_position(Elements *self, int dx, int dy)
{
    apple *Obj = ((apple *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void apple_interact(Elements *self)
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
void _apple_interact_Floor(Elements *self)
{
    apple *Obj = ((apple *)(self->pDerivedObj));
    if (Obj->y >= HEIGHT){
        self->dele = true;
        printf("apple deleted\n");
    }
}

void apple_draw(Elements *self)
{
    apple *Obj = ((apple *)(self->pDerivedObj));
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void apple_destory(Elements *self)
{
    apple *Obj = ((apple *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
