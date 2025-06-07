#ifndef questGameLake_H_INCLUDED
#define questGameLake_H_INCLUDED
#include "scene.h"

/*
   [game scene object]
*/
typedef enum QuestGameLakeEle
{
    Couple_L,
    Bat_L
} QuestGameLakeEle;

typedef struct _questGame4
{
    ALLEGRO_BITMAP *background;

} questGameLake;
Scene *New_questGameLake(int label);
void questGameLake_update(Scene *self);
void questGamelake_draw(Scene *self);
void questGameLake_destroy(Scene *self);
extern int score_of_lake_quest;

#endif
