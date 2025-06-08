#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include "../algif5/algif.h"
#include "element.h"
#include "../shapes/Circle.h"
#include "hole.h"
#include <stdbool.h>
typedef struct _ball {
    int x, y;
    int width, height;
    int id;              // 配對判斷
    int stat;            // 判斷有沒有被拿起來(0:在洞裡 || 1：gauss拿著)
    ALLEGRO_BITMAP *img;
    Shape *hitbox;
    int type;
} ball;

// 建立球元素（生成 Elements 並設為 Ball）
Elements *New_Ball(int label, int id, int x, int y);
void Ball_update(Elements *self);
void Ball_draw(Elements *self);
void Ball_interact(Elements *self);
void Ball_destroy(Elements *self);
void CharacterGauss_update_position(Elements *self, int dx, int dy);
#endif
