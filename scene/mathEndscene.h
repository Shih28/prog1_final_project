#ifndef mathEndscene_H_INCLUDED
#define mathEndscene_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include "scene.h"
/*
   [mathEndscene object]
*/
typedef struct _mathEndscene
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *img;
    char score[15];
    int title_x, title_y;
}mathEndscene;
Scene *New_mathEndscene(int label);
void mathEndscene_update(Scene *self);
void mathEndscene_draw(Scene *self);
void mathEndscene_destroy(Scene *self);

#endif
