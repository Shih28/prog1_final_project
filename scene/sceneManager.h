#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include "scene.h"
extern Scene *scene;
typedef enum SceneType
{
    Menu_L = 0,
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
    Math_endscene_L
    
} SceneType;
void create_scene(SceneType);

#endif