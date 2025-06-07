#ifndef QUEST_MENU_1_H_INCLUDED
#define QUEST_MENU_1_H_INCLUDED
#include "scene.h"

/*
   [game scene object]
*/
typedef enum QuestMenuEletype
{
    StartButton_L
} QuestMenuEletype;

typedef struct _quest_1_menu
{
    ALLEGRO_BITMAP *background;
    int next_scene;

} quest_menu;
Scene *New_quest_menu(int label, int next_scene, ALLEGRO_BITMAP *img);
void quest_menu_update(Scene *self);
void quest_menu_draw(Scene *self);
void quest_menu_destroy(Scene *self);

#endif
