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
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *img;
    char score[15];
    int title_x, title_y;
}lakeEndscene;
Scene *New_lakeEndscene(int label);
void lakeEndscene_update(Scene *self);
void lakeEndscene_draw(Scene *self);
void lakeEndscene_destroy(Scene *self);

#endif
