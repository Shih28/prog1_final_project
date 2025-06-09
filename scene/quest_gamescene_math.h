#ifndef questGameMath_H_INCLUDED
#define questGameMath_H_INCLUDED
#include "scene.h"

/*
   [game scene object]
*/
typedef enum QuestGameMathEle
{
    Hole_L=0,
    CharacterGauss_L=1,
    Ball_L=2,
} QuestGameMathEle;

typedef struct _questGameMath
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *formula_img[3];
    ALLEGRO_BITMAP *desc_imgs[3];

} questGameMath;
Scene *New_questGameMath(int label);
void questGameMath_update(Scene *self);
void questGameMath_draw(Scene *self);
void questGameMath_destroy(Scene *self);
void checkMatching(Scene *self);
int all_holes_have_balls(Scene *self);
extern int score_of_Math_quest;

#endif
