#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "characterNewton.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include "../algif5/algif.h"
#include "../scene/quest_gamescene_phys.h"
#include "apple.h"
#include "../shapes/Shape.h"
#include "../shapes/Rectangle.h"
#include <stdio.h>
#include <stdbool.h>
/*
   [CharacterNewton function]
*/
Elements *New_CharacterNewton(int label)
{
    CharacterNewton *pDerivedObj = (CharacterNewton *)malloc(sizeof(CharacterNewton));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load CharacterNewton images
    char state_string[2][10] = {"stop", "move"};
    for (int i = 0; i < 2; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/char3_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }

    // initial the geometric information of CharacterNewton
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 300;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 60;
    pDerivedObj->v = 7;
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
    pObj->inter_obj[pObj->inter_len++] = AppleRight_L;
    pObj->inter_obj[pObj->inter_len++] = AppleWrong_L;
    
    // setting derived object function
    pObj->Draw = CharacterNewton_draw;
    pObj->Update = CharacterNewton_update;
    pObj->Interact = CharacterNewton_interact;
    pObj->Destroy = CharacterNewton_destory;
    return pObj;
}
void CharacterNewton_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    CharacterNewton *chara = ((CharacterNewton *)(self->pDerivedObj));
    if (chara->state == STOP)
    {
       if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            chara->state = MOVE;
        }
        else
        {
            chara->state = STOP;
        }
    }
    else if (chara->state == MOVE)
    {
        if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            CharacterNewton_update_position(self, -chara->v, 0);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            CharacterNewton_update_position(self, chara->v, 0);
            chara->state = MOVE;
        }
        // if (chara->gif_status[chara->state]->done)
        //     chara->state = STOP;
        if(key_state[ALLEGRO_KEY_A]==0 && 
           key_state[ALLEGRO_KEY_D]==0){
            chara->state=STOP;
        }
    }
    if(key_state[ALLEGRO_KEY_SPACE]){
        chara->v=10;
    }else{
        chara->v=7;
    }
}

void CharacterNewton_draw(Elements *self)
{
    // with the state, draw corresponding image
    CharacterNewton *chara = ((CharacterNewton *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? 0:ALLEGRO_FLIP_HORIZONTAL));
    }
}
void CharacterNewton_destory(Elements *self)
{
    CharacterNewton *Obj = ((CharacterNewton *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 2; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void CharacterNewton_update_position(Elements *self, int dx, int dy)
{
    CharacterNewton *chara = ((CharacterNewton *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void CharacterNewton_interact_apple(Elements *self, Elements *tar){
    CharacterNewton *chra = ((CharacterNewton*)self->pDerivedObj);
    apple *app = (apple*)tar->pDerivedObj;

    if(chra->hitbox->overlap(chra->hitbox, app->hitbox)){
        printf("HIT_apple");
        int add = (app->type==AppleRight_L)? 1:-1;
        score_of_phys_quest+=add;
        tar->dele=true;
    }
}

void CharacterNewton_interact(Elements *self) {
    for(int i=0; i<self->inter_len; i++){
        int inter_label = self->inter_obj[i];
        
        ElementVec labelEle = _Get_label_elements(scene, inter_label);
        for(int j=0; j<labelEle.len; j++){
            if(inter_label==AppleRight_L){
                CharacterNewton_interact_apple(self, labelEle.arr[j]);
            }
            else if(inter_label==AppleWrong_L){
                CharacterNewton_interact_apple(self, labelEle.arr[j]);
            }
            
        }
    }
}
        
