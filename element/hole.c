#include "hole.h"
#include "ball.h"
#include "characterGauss.h"
#include "../shapes/Circle.h"
#include "../scene/quest_gamescene_math.h"
#include "../scene/sceneManager.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <stdio.h>

/*
   [Hole Function Implementation]
*/

Elements *New_hole(int label, int x, int y, int id) {
    hole *pDerivedObj = (hole *)malloc(sizeof(hole));
    Elements *pObj = New_Elements(label);

    pDerivedObj->id = id;
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->correct = 0; // 尚未配對成功
    pDerivedObj->ball_in_hole = NULL;  // 初始化為無球

    // 載入圖像
    pDerivedObj->img = al_load_bitmap("assets/image/hole.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);

    pDerivedObj->type = label;

    pDerivedObj->hitbox = New_Circle(
        pDerivedObj->x + pDerivedObj->width / 2,
        pDerivedObj->y + pDerivedObj->height / 2,
        min(pDerivedObj->width, pDerivedObj->height) / 2
    );

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = hole_update;
    pObj->Interact = hole_interact;
    pObj->Draw = hole_draw;
    pObj->Destroy = hole_destroy;

    return pObj;
}

void hole_update(Elements *self) {
    //不會主動變化
}

void hole_interact(Elements *self) {
    hole *h = (hole *)(self->pDerivedObj);

    // 檢查所有 ball
    ElementVec balls = _Get_label_elements(scene, Ball_L);

    for (int i = 0; i < balls.len; i++) {
        Elements *ballEle = balls.arr[i];
        ball *b = (ball *)(ballEle->pDerivedObj);

        // 檢查是否重疊，且不是被頂著的球
        if (h->hitbox->overlap(h->hitbox, b->hitbox)) {

            // 檢查是否有頂著這顆球
            bool carried = false;
            ElementVec others = _Get_all_elements(scene);
            for (int j = 0; j < others.len; j++) {
                Elements *e = others.arr[j];
                if (e->label == CharacterGauss_L) {
                    CharacterGauss *g = (CharacterGauss *)(e->pDerivedObj);
                    if (g->carried_ball == ballEle) {
                        carried = true;
                        break;
                    }
                }
            }

            if (!carried) {
                h->ball_in_hole = ballEle;
                if (b->id == h->id) {
                    if (!h->correct) {
                        h->correct = 1;
                        printf("correct! Ball %d -> Hole %d\n", b->id, h->id);
                    }
                } else {
                    if (h->correct) {
                        h->correct = 0;
                        printf("wrong! Ball %d -> Hole %d (covered)\n", b->id, h->id);
                    } else {
                        printf("wrong!Ball %d -> Hole %d\n", b->id, h->id);
                    }
                }
            }
        }
    }
}

void hole_draw(Elements *self) {
    hole *Obj = (hole *)(self->pDerivedObj);
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);

    // 若已經正確配對，可以畫個提示
    if (Obj->correct) {
        al_draw_circle(Obj->x + Obj->width / 2, Obj->y + Obj->height / 2, 10, al_map_rgb(0, 255, 0), 3);
    }
}

void hole_destroy(Elements *self) {
    hole *Obj = (hole *)(self->pDerivedObj);
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}