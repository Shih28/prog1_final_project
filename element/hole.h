#ifndef HOLE_H_INCLUDED
#define HOLE_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include "../algif5/algif.h"
#include "../shapes/Circle.h"
#include "element.h"
#include <stdbool.h>

typedef struct _hole {
    int x, y;
    int width, height;
    int id;                    // 用於比對配對
    int correct;
    ALLEGRO_BITMAP *img;
    Shape *hitbox;
    int type;                  // 對應 label
    Elements *ball_in_hole; // 指向目前在坑中的球，若無則為 NULL
} hole;

Elements *New_hole(int label, int x, int y, int id);
void hole_update(Elements *self);
void hole_draw(Elements *self);
void hole_interact(Elements *self);
void hole_destroy(Elements *self);

#endif
