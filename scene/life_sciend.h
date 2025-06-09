#ifndef life_sciend_H_INCLUDED
#define life_sciend_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include "scene.h"
/*
   [lakeEndscene object]
*/
typedef struct _life_sciend
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *img;
    //char score[15];
}life_sciend;
Scene *New_life_sciend(int label);
void life_sciend_update(Scene *self);
void life_sciend_draw(Scene *self);
void life_sciend_destroy(Scene *self);

#endif
