#include "global.h"
#include "shapes/Shape.h"
#include <stdbool.h>
// variables for global usage
const double FPS = 60.0;
const int WIDTH = 1920;
const int HEIGHT = 1280;
int window = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *fps = NULL;
ALLEGRO_TIMER *apple_timer = NULL;
ALLEGRO_TIMER *couple_timer = NULL;
ALLEGRO_TIMER *phys_gamescene_timer = NULL;
ALLEGRO_TIMER *lake_gamescene_timer = NULL;
ALLEGRO_TIMER *lifeSci_gamescene_timer = NULL;
int QuestComp[4]={0};

bool key_state[ALLEGRO_KEY_MAX] = {false};
bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
Point mouse;
bool debug_mode = true;
bool ALL_COMPLETE = false;
