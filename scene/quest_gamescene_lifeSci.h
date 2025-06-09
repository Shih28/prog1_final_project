#ifndef questLifeSci_H_INCLUDED
#define questLifeSci_H_INCLUDED
#include "scene.h"

extern int combo;
extern int current_keycode;

/*
   [game scene object]
*/
typedef enum QuestLifeSciEle
{
    dna_L
} QuestLifeSciEle;

typedef struct _questLifeSci
{
    ALLEGRO_BITMAP *background;

} questLifeSci;
Scene *New_questLifeSci(int label);
void questLifeSci_update(Scene *self);
void questLifeSci_draw(Scene *self);
void questLifeSci_destroy(Scene *self);
extern int score_of_lifeSci;

#endif