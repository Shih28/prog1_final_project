#ifndef CHARACTERGAUSS_H_INCLUDED
#define CHARACTERGAUSS_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/algif.h"
#include <stdbool.h>

/*
   [CharacterGauss object]
*/
typedef enum CharacterGaussType
{
    STOP = 0,
    MOVE,
} CharacterGaussType;
typedef struct CharacterGauss
{
    int x, y;
    int width, height;              // the width and height of image
    bool dir;                       // true: face to right, false: face to left
    int state;                      // the state of CharacterGauss
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
    Shape *hitbox; // the hitbox of object
    Elements *carried_ball;//指向當前頂著的球
} CharacterGauss;
Elements *New_CharacterGauss(int label);
void CharacterGauss_update(Elements *self);
void CharacterGauss_interact(Elements *self);
void CharacterGauss_draw(Elements *self);
void CharacterGauss_destory(Elements *self);
void CharacterGauss_interact_ball(Elements *self, Elements *ball);
void CharacterGauss_interact_hole(Elements *self, Elements *hole);

#endif
