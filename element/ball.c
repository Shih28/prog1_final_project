#include "ball.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "../shapes/Circle.h"
#include "../scene/quest_gamescene_math.h"
#include "../scene/sceneManager.h"
#include <stdlib.h>
#include <stdio.h>
/*
   [ball function]
*/
Elements *New_Ball(int label, int id, int x, int y) {
    ball *pDerivedObj = (ball *)malloc(sizeof(ball));
    Elements *pObj = New_Elements(label);

    pDerivedObj->id = id;
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->stat=0;

    // 根據 id 載入對應圖片
    char path[100];
    sprintf(path, "assets/image/ball%d.png", id);
    pDerivedObj->img = al_load_bitmap(path);
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);

    pDerivedObj->type = label;

    pDerivedObj->hitbox = New_Circle(
                                    pDerivedObj->x + pDerivedObj->width / 2,
                                    pDerivedObj->y + pDerivedObj->height / 2,
                                    min(pDerivedObj->width, pDerivedObj->height) / 2);

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Ball_update;
    pObj->Interact = Ball_interact;
    pObj->Draw = Ball_draw;
    pObj->Destroy = Ball_destroy;

    return pObj;
}

void Ball_update(Elements *self)
{
    // Ball 目前為靜態，不主動移動
    // 若被角色拿起移動，在外部修改其 x, y
}

void Ball_interact(Elements *self)
{
    //放沒放對的判斷放到hole那
    /*
    ball *Obj = ((ball *)(self->pDerivedObj));
    for (int j = 0; j < self->inter_len; j++)
    {
        int inter_label = self->inter_obj[j];
        ElementVec labelEle = _Get_label_elements(scene, inter_label);
        
        for (int i = 0; i < labelEle.len; i++)
        {
            Elements *target = labelEle.arr[i];
            // 如果互動對象是洞並重疊，進行配對判定
            hole *h = (hole *)(target->pDerivedObj);
            if (h->hitbox->overlap(h->hitbox, Obj->hitbox))
            {
                // 根據 id 是否配對成功，決定後續處理
                printf("Ball %d interacted with Hole %d\n", Obj->id, h->id);
            }
        }
    }
    */
}

void Ball_draw(Elements *self)
{
    ball *Obj = ((ball *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}

void Ball_destroy(Elements *self)
{
    ball *Obj = ((ball *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}