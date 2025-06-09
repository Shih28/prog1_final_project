#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "charater.h"
#include "projectile.h"
#include "../element/questNode.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include "../algif5/algif.h"
#include "../scene/gamescene.h"
#include "../shapes/Shape.h"
#include "../shapes/Rectangle.h"
#include <stdio.h>
#include <stdbool.h>
/*
   [Character function]
*/
Elements *New_Character(int label)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[2][10] = {"stop", "move"};
    for (int i = 0; i < 2; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/char2_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }


    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 750;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 60;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;

    //setting interact objects
    pObj->inter_obj[pObj->inter_len++]=questNode_L;
    pObj->inter_obj[pObj->inter_len++]=questNode2_L;
    pObj->inter_obj[pObj->inter_len++]=questNode3_L;
    pObj->inter_obj[pObj->inter_len++]=questNode4_L;
    

    // setting derived object function
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}
void Character_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Character *chara = ((Character *)(self->pDerivedObj));
    if (chara->state == STOP)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_W])
        {
            _Character_update_position(self, 0, -5);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_S])
        {
            _Character_update_position(self, 0, 5);
            chara->state = MOVE;
        }
        else
        {
            chara->state = STOP;
        }
    }
    else if (chara->state == MOVE)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            _Character_update_position(self, -7, 0);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_W])
        {
            _Character_update_position(self, 0, -7);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_S])
        {
            _Character_update_position(self, 0, 7);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            _Character_update_position(self, 7, 0);
            chara->state = MOVE;
        }
        // if (chara->gif_status[chara->state]->done)
        //     chara->state = STOP;
        if(key_state[ALLEGRO_KEY_A]==0 && 
           key_state[ALLEGRO_KEY_W]==0 &&
           key_state[ALLEGRO_KEY_D]==0 &&
           key_state[ALLEGRO_KEY_S]==0){
            chara->state=STOP;
        }
    }
    
}
void Character_draw(Elements *self)
{
    // with the state, draw corresponding image
    Character *chara = ((Character *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? 0:ALLEGRO_FLIP_HORIZONTAL));
    }
    // al_draw_rectangle(chara->x, chara->y, chara->x+chara->width, chara->y+chara->height, al_map_rgb(255,255,255), 1);
}
void Character_destory(Elements *self)
{
    Character *Obj = ((Character *)(self->pDerivedObj));
    for (int i = 0; i < 2; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Character_update_position(Elements *self, int dx, int dy)
{
    Character *chara = ((Character *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void character_interact_questNode(Elements *self, Elements *tar){
    Character *chra = ((Character*)self->pDerivedObj);
    questNode *qn = ((questNode*)tar->pDerivedObj);

    if(chra->hitbox->overlap(chra->hitbox, qn->hitbox)){
        printf("HIT");
        scene->scene_end=true;
        window=qn->change_scene;
    }
}

void Character_interact(Elements *self) {
    for(int i=0; i<self->inter_len; i++){
        int inter_label = self->inter_obj[i];
        
        ElementVec labelEle = _Get_label_elements(scene, inter_label);
        for(int j=0; j<labelEle.len; j++){
            if(inter_label==questNode_L){
                character_interact_questNode(self, labelEle.arr[j]);
            }
            else if(inter_label==questNode2_L){
                character_interact_questNode(self, labelEle.arr[j]);
            }
            else if(inter_label==questNode3_L){
                character_interact_questNode(self, labelEle.arr[j]);
            }
            else if(inter_label==questNode4_L){
                character_interact_questNode(self, labelEle.arr[j]);
            }
            
        }
    }
}
        
