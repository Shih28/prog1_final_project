#ifndef finalEndscene_H_INCLUDED
#define finalEndscene_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include "scene.h"
/*
   [finalEndscene object]
*/
typedef struct _finalEndscene
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *img;
    
    int title_x, title_y;
}finalEndscene;
Scene *New_finalEndscene(int label);
void finalEndscene_update(Scene *self);
void finalEndscene_draw(Scene *self);
void finalEndscene_destroy(Scene *self);

#endif
