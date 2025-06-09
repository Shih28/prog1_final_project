#ifndef physEndscene_H_INCLUDED
#define physEndscene_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include "scene.h"
/*
   [physEndscene object]
*/
typedef struct _physEndscene
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *img;
    char score[15];
}physEndscene;
Scene *New_physEndscene(int label);
void physEndscene_update(Scene *self);
void physEndscene_draw(Scene *self);
void physEndscene_destroy(Scene *self);

#endif
