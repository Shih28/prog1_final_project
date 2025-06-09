#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include "scene.h"
extern Scene *scene;
typedef enum SceneType
{
    Menu_L = 0,
    Intro_1_L,
    Intro_2_L,
    Intro_3_L,
    Intro_4_L,
    GameScene_L,
    quest_menu_phys_L,
    quest_menu_math_L,
    quest_menu_lifeSci_L,
    quest_menu_lake_L,
    quest_gameScene_phys_L,
    Math_gamescene_L,
    quest_gameScene_lifeSci_L,
    quest_gameScene_lake_L,
    Lake_endscene_L,
    Phys_endscene_L,
    Final_endscene_L,
    LifeSci_endscene_L,
    Math_endscene_L,
    outro_1_L,
    outro_2_L
    
} SceneType;
void create_scene(SceneType);

#endif