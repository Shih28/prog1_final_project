#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include <stdio.h>
#include <allegro5/allegro.h>
#define GAME_TERMINATE -1
#include "shapes/Point.h"
#define debug(x)                                                            \
    if (x)                                                                  \
    {                                                                       \
        printf("check at line number %d in file %s\n", __LINE__, __FILE__); \
    }
#define MAX_ELEMENT 100
#define min(x, y) ((x) > (y) ? (y) : (x))
#define max(x, y) ((x) < (y) ? (y) : (x))
// note that you can't assign initial value for extern variable!
extern const double FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern int window;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES];
extern Point mouse;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_TIMER *fps;
extern ALLEGRO_TIMER *apple_timer;
extern ALLEGRO_TIMER *phys_gamescene_timer;
extern ALLEGRO_TIMER *lake_gamescene_timer;
extern ALLEGRO_TIMER *couple_timer;
extern ALLEGRO_TIMER *lifeSci_gamescene_timer;
typedef enum QuestComplete{
    QuestLake_L,
    QuestPhys_L,
    QuestMath_L,
    QuestLifeSci_L
}QuestComplete;
extern int QuestComp[4];
extern bool ALL_COMPLETE;
extern bool debug_mode;

#endif
