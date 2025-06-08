#ifndef apple_H_INCLUDED
#define apple_H_INCLUDED
#include "element.h"
#include "../shapes/Shape.h"
/*
   [apple object]
*/
typedef struct _apple
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of apple
    int type;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} apple;

Elements *New_apple(int label, int x, int y, int v, int type);
void apple_update(Elements *self);
void apple_interact(Elements *self);
void apple_draw(Elements *self);
void apple_destory(Elements *self);
void _apple_update_position(Elements *self, int dx, int dy);
void _apple_interact_Floor(Elements *self);

#endif
