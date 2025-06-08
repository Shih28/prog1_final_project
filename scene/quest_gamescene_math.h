#ifndef questGameMath_H_INCLUDED
#define questGameMath_H_INCLUDED
#include "scene.h"

/*
   [game scene object]
*/
typedef enum QuestGameMathEle
{
    Ball_L=0,
    Hole_L=1,
    CharacterGauss_L=2
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
int checkMatching(Scene *self);

#endif
