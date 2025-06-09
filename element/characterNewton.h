#ifndef CHARATER_H_INCLUDED
#define CHARATER_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/algif.h"
#include <stdbool.h>

/*
   [CharacterNewton object]
*/
typedef enum CharacterNewtonType
{
    STOP = 0,
    MOVE,
} CharacterNewtonType;
typedef struct CharacterNewton
{
    int x, y;
    int width, height;              // the width and height of image
    bool dir;                       // true: face to right, false: face to left
    int state;                      // the state of CharacterNewton
    int v;
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
    Shape *hitbox; // the hitbox of object
} CharacterNewton;
Elements *New_CharacterNewton(int label);
void CharacterNewton_update(Elements *self);
void CharacterNewton_interact(Elements *self);
void CharacterNewton_draw(Elements *self);
void CharacterNewton_destory(Elements *self);
void CharacterNewton_update_position(Elements *self, int dx, int dy);
void CharacterNewton_interact_questNode(Elements *self, Elements *tar, int type);

#endif
