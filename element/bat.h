#ifndef bat_H_INCLUDED
#define bat_H_INCLUDED
#include "element.h"
#include "../shapes/Shape.h"
/*
   [bat object]
*/
typedef struct _bat
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int status;             // status
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} bat;

Elements *New_bat(int label);
void bat_update(Elements *self);
void bat_interact(Elements *self);
void bat_draw(Elements *self);
void bat_destory(Elements *self);

#endif
