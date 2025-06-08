#include "apple.h"
#include "questNode.h"
#include "../shapes/Circle.h"
#include "../scene/quest_gamescene_phys.h" // for element label
#include "../scene/sceneManager.h" // for scene variable
#define MAX_NUM_OF_APPLE 10
/*
   [apple function]
*/

char pic_apple[MAX_NUM_OF_APPLE][2][50]={
    {"assets/image/rightApple_1.png", "assets/image/wrongApple_1.png"},
    {"assets/image/rightApple_2.png", "assets/image/wrongApple_2.png"},
    {"assets/image/rightApple_3.png", "assets/image/wrongApple_3.png"},
    {"assets/image/rightApple_4.png", "assets/image/wrongApple_4.png"},
    {"assets/image/rightApple_5.png", "assets/image/wrongApple_5.png"},
    {"assets/image/rightApple_6.png", "assets/image/wrongApple_6.png"},
    {"assets/image/rightApple_7.png", "assets/image/wrongApple_7.png"},
    {"assets/image/rightApple_8.png", "assets/image/wrongApple_8.png"},
    {"assets/image/rightApple_9.png", "assets/image/wrongApple_9.png"},
    {"assets/image/rightApple_10.png", "assets/image/wrongApple_10.png"}
};

Elements *New_apple(int label, int x, int y, int v, int type)
{
    apple *pDerivedObj = (apple *)malloc(sizeof(apple));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap(pic_apple[type][label]);
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
