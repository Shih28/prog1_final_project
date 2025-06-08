#ifndef couple_H_INCLUDED
#define couple_H_INCLUDED
#include "element.h"
#include "../shapes/Shape.h"
/*
   [couple object]
*/
typedef struct _couple
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int status;             // status
    int delay_count; //fps
    int appear_time_count;//fps
    int type;               //which photo
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} couple;

Elements *New_couple(int label, int x, int y, int type);
void couple_update(Elements *self);
void couple_interact(Elements *self);
void couple_draw(Elements *self);
void couple_destory(Elements *self);

#endif
