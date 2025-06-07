#ifndef questNode_H_INCLUDED
#define questNode_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [questNode object]
*/
typedef struct _questNode
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int change_scene;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} questNode;
Elements *New_questNode(int label, int x, int y, int change_scene, ALLEGRO_BITMAP *img);
void questNode_update(Elements *self);
void questNode_interact(Elements *self);
void questNode_draw(Elements *self);
void questNode_destroy(Elements *self);

#endif
