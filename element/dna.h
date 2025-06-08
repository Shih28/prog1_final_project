#ifndef dna_H_INCLUDED
#define dna_H_INCLUDED
#include "element.h"
#include "../shapes/Shape.h"
/*
   [dna object]
*/
typedef struct _dna
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of apple
    int type;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} dna;

Elements *New_dna(int label, int x, int y, int v);
void dna_update(Elements *self);
void dna_interact(Elements *self);
void dna_draw(Elements *self);
void dna_destroy(Elements *self);
bool check_match(dna *d, int keycode);

#endif