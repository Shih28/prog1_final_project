#ifndef lakeEndscene_H_INCLUDED
#define lakeEndscene_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include "scene.h"
/*
   [lakeEndscene object]
*/
typedef struct _lakeEndscene
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *img;
    char score[15];

}lakeEndscene;
Scene *New_lakeEndscene(int label);
void lakeEndscene_update(Scene *self);
void lakeEndscene_draw(Scene *self);
void lakeEndscene_destroy(Scene *self);

#endif
