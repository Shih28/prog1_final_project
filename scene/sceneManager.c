#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "quest_gamescene_phys.h"
#include "quest_gamescene_math.h"
#include "quest_gamescene_lifeSci.h"
#include "quest_gamescene_lake.h"

#include "lakeEndscene.h"
#include "physEndscene.h"
#include "mathEndscene.h"
#include "life_sciend.h"
#include "quest_menu.h"
#include "finalEndscene.h"

Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        scene = New_gamescene(GameScene_L);
        break;
    case quest_menu_phys_L:
        scene = New_quest_menu(quest_menu_phys_L, quest_gameScene_phys_L, al_load_bitmap("assets/image/phys_intro.png"));
        break;
    case quest_menu_math_L:
        scene = New_quest_menu(quest_menu_math_L, Math_gamescene_L, al_load_bitmap("assets/image/math_intro.png"));
        break;
    case quest_menu_lifeSci_L:
        scene = New_quest_menu(quest_menu_lifeSci_L, quest_gameScene_lifeSci_L,al_load_bitmap("assets/image/life_sci_1.png"));
        break;
    case quest_menu_lake_L:
        scene = New_quest_menu(quest_menu_lake_L, quest_gameScene_lake_L,al_load_bitmap("assets/image/lake_intro.png"));
        break;
    case Intro_1_L:
        scene = New_quest_menu(Intro_1_L, Intro_2_L,al_load_bitmap("assets/image/intro_1.png"));
        break;
    case Intro_2_L:
        scene = New_quest_menu(Intro_2_L, Intro_3_L,al_load_bitmap("assets/image/intro_2.png"));
        break;
    case Intro_3_L:
        scene = New_quest_menu(Intro_3_L, Intro_4_L,al_load_bitmap("assets/image/intro_3.png"));
        break;
    case Intro_4_L:
        scene = New_quest_menu(Intro_4_L, GameScene_L,al_load_bitmap("assets/image/intro_4.png"));
        break;
    
    case outro_1_L:
        scene = New_quest_menu(outro_1_L, outro_2_L,al_load_bitmap("assets/image/end_0.png"));
        break;
    case outro_2_L:
        scene = New_quest_menu(outro_2_L, Final_endscene_L,al_load_bitmap("assets/image/end_1.png"));
        break;
    
    case quest_gameScene_phys_L:
        scene = New_questGamePhys(quest_gameScene_phys_L);
        break;
    case Math_gamescene_L:
        scene = New_questGameMath(Math_gamescene_L);
        break;
    case quest_gameScene_lifeSci_L:
        scene = New_questLifeSci(quest_gameScene_lifeSci_L);
        break;
    case quest_gameScene_lake_L:
        scene = New_questGameLake(quest_gameScene_lake_L);
        break;
    case Lake_endscene_L:
        scene = New_lakeEndscene(Lake_endscene_L);
        break;
    case Phys_endscene_L:
        scene = New_physEndscene(Phys_endscene_L);
        break;
    case LifeSci_endscene_L:
        scene = New_life_sciend(LifeSci_endscene_L);
        break;
    case Math_endscene_L:
        scene = New_mathEndscene(Math_endscene_L);
        break;
    case Final_endscene_L:
        scene = New_finalEndscene(Final_endscene_L);
        break;
  
    
    default:
        break;
    }
}
