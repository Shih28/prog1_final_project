#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "characterGauss.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include "../algif5/algif.h"    
#include "ball.h"
#include "hole.h"
#include "../scene/quest_gamescene_math.h"
#include "../shapes/Shape.h"
#include <stdio.h>
#include <stdbool.h>
/*
   [CharacterGauss function]
*/
Elements *New_CharacterGauss(int label)
{
    CharacterGauss *pDerivedObj = (CharacterGauss *)malloc(sizeof(CharacterGauss));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load CharacterGauss images
    char state_string[2][10] = {"stop", "move"};
    for (int i = 0; i < 2; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/char3_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    

    // initial the geometric information of CharacterGauss
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 300;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 60;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pDerivedObj->carried_ball = NULL;
    pObj->pDerivedObj = pDerivedObj;

    //setting interact objects
    pObj->inter_obj[pObj->inter_len++] = Ball_L;
    pObj->inter_obj[pObj->inter_len++] = Hole_L;
    
    // setting derived object function
    pObj->Draw = CharacterGauss_draw;
    pObj->Update = CharacterGauss_update;
    pObj->Interact = CharacterGauss_interact;
    pObj->Destroy = CharacterGauss_destory;
    return pObj;
}
void CharacterGauss_update_position(Elements *self, int dx, int dy)
{
    CharacterGauss *chara = ((CharacterGauss *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
    if (chara->carried_ball){
        ball *b = (ball *)(chara->carried_ball->pDerivedObj);
        b->x += dx;
        b->y += dy;
        b->hitbox->update_center_x(b->hitbox, dx);
        b->hitbox->update_center_y(b->hitbox, dy);
    }
}
void CharacterGauss_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    CharacterGauss *chara = ((CharacterGauss *)(self->pDerivedObj));
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
            CharacterGauss_update_position(self, -7, 0);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            CharacterGauss_update_position(self, 7, 0);
            chara->state = MOVE;
        }
        else
        {
            chara->state=STOP;
        }
        if (chara->gif_status[chara->state]->done)
            chara->state = STOP;
    }
}
void CharacterGauss_draw(Elements *self)
{
    // with the state, draw corresponding image
    CharacterGauss *chara = ((CharacterGauss *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? 0:ALLEGRO_FLIP_HORIZONTAL));
    }
}
void CharacterGauss_destory(Elements *self)
{
    CharacterGauss *Obj = ((CharacterGauss *)(self->pDerivedObj));
    for (int i = 0; i < 2; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void CharacterGauss_interact_ball(Elements *self, Elements *inputBall) {
    CharacterGauss *ch = (CharacterGauss *)(self->pDerivedObj);
    ball *b = (ball *)(inputBall->pDerivedObj);

    if (ch->carried_ball == NULL && key_state[ALLEGRO_KEY_F] && ch->hitbox->overlap(ch->hitbox, b->hitbox)) {
        ch->carried_ball = inputBall;
        key_state[ALLEGRO_KEY_F]=0;
        printf("Picked up a ball!\n");
    }
}

void CharacterGauss_interact_hole(Elements *self, Elements *inputHole) {
    CharacterGauss *chara = (CharacterGauss *)(self->pDerivedObj);
    hole *h = (hole *)(inputHole->pDerivedObj);
    // printf("hole: %d\n", chara->hitbox->overlap(chara->hitbox, h->hitbox));

    if (key_state[ALLEGRO_KEY_F] && chara->hitbox->overlap(chara->hitbox, h->hitbox)) {

        // 取得坑的中心點位置
        int hole_cx = h->x + h->width / 2;
        int hole_cy = h->y + h->height / 2;
        key_state[ALLEGRO_KEY_F]=0;

        // 若坑裡有球，讓它回到角色頭上
        if (h->ball_in_hole != NULL) {
            Elements *prev_ball = h->ball_in_hole;
            ball *pb = (ball *)(prev_ball->pDerivedObj);
            // 設定新位置：角色頭頂
            pb->x = chara->x + chara->width / 2 - pb->width / 2;
            pb->y = chara->y;
            // 更新 hitbox
            pb->hitbox->update_center_x(pb->hitbox, pb->x + pb->width / 2);
            pb->hitbox->update_center_y(pb->hitbox, pb->y + pb->height / 2);

        }
        if(chara->carried_ball!=NULL){
            // 把角色頭上的球放進坑裡
            ball *cb = (ball *)(chara->carried_ball->pDerivedObj);
            cb->x = hole_cx - cb->width / 2;
            cb->y = hole_cy - cb->height / 2;
            cb->hitbox->update_center_x(cb->hitbox, cb->x + cb->width / 2);
            cb->hitbox->update_center_y(cb->hitbox, cb->y + cb->height / 2);
        }
        

        // 完成交換
        Elements *tmp = h->ball_in_hole;
        h->ball_in_hole = chara->carried_ball;
        chara->carried_ball = tmp;
    }
    
}


void CharacterGauss_interact(Elements *self) {
    for(int i=0; i<self->inter_len; i++){
        int inter_label = self->inter_obj[i];
        
        ElementVec labelEle = _Get_label_elements(scene, inter_label);
        for(int j=0; j<labelEle.len; j++){
            if(inter_label==Ball_L){
                CharacterGauss_interact_ball(self, labelEle.arr[j]);
            }
            else if(inter_label==Hole_L){
                CharacterGauss_interact_hole(self, labelEle.arr[j]);
            }
            
        }
    }
}
        
