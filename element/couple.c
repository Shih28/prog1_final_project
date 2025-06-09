#include "couple.h"
#include "bat.h"
#include "../shapes/Point.h"
#include "../shapes/Circle.h"
#include "../scene/quest_gamescene_lake.h" // for element label
#include "../scene/sceneManager.h" // for scene variable
#define MAX_NUM_OF_PIC 15
/*
   [couple function]
*/

char pic[MAX_NUM_OF_PIC][2][50] = { //which photo, status, lenth of directory
    {"assets/image/coup_1.png", "assets/image/hit_1.png"},
    {"assets/image/coup_2.png", "assets/image/hit_2.png"},
    {"assets/image/coup_3.png", "assets/image/hit_3.png"},
    {"assets/image/coup_4.png", "assets/image/hit_4.png"},
    {"assets/image/coup_5.png", "assets/image/hit_5.png"},
    {"assets/image/coup_6.png", "assets/image/hit_6.png"},
    {"assets/image/coup_7.png", "assets/image/hit_7.png"},
    {"assets/image/coup_8.png", "assets/image/hit_8.png"},
    {"assets/image/coup_9.png", "assets/image/hit_9.png"},
    {"assets/image/coup_10.png", "assets/image/hit_10.png"},
    {"assets/image/coup_11.png", "assets/image/hit_11.png"},
    {"assets/image/coup_12.png", "assets/image/hit_12.png"},
    {"assets/image/coup_13.png", "assets/image/hit_13.png"},
    {"assets/image/coup_14.png", "assets/image/hit_14.png"},
    {"assets/image/coup_15.png", "assets/image/hit_15.png"}
};

Elements *New_couple(int label, int x, int y, int type)
{
    couple *pDerivedObj = (couple *)malloc(sizeof(couple));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap(pic[type][0]);
    pDerivedObj->type = type;
    // printf("creating couple.... type: %d, img: %s\n", pDerivedObj->type, pic[pDerivedObj->type][0]);
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->delay_count=0;
    pDerivedObj->appear_time_count=0;
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    
    pDerivedObj->status = 0;//haven't been hit
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
   
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = couple_update;
    pObj->Interact = couple_interact;
    pObj->Draw = couple_draw;
    pObj->Destroy = couple_destory;

    return pObj;
}
void couple_update(Elements *self)
{
    couple *Obj = ((couple *)(self->pDerivedObj));
    Obj->img=al_load_bitmap(pic[Obj->type][Obj->status]);
    // printf("updating .... type: %d, img: %s\n", Obj->type, pic[Obj->type][Obj->status]);
 
    Obj->appear_time_count++;
    if(Obj->hitbox->overlap(New_Point(mouse.x, mouse.y), Obj->hitbox) && mouse_state[1] && Obj->status==0){
        Obj->status=1;
        Obj->appear_time_count=0;
        if(Obj->delay_count==0) score_of_lake_quest++;
    }
    if(Obj->status==1) Obj->delay_count++;
    if(Obj->delay_count>=30) self->dele=true;
    if(Obj->appear_time_count>=70) self->dele=true;
}


void couple_interact(Elements *self)
{
    for (int j = 0; j < self->inter_len; j++)
    {
        int inter_label = self->inter_obj[j];
        ElementVec labelEle = _Get_label_elements(scene, inter_label);
        
        for (int i = 0; i < labelEle.len; i++)
        {
        }
    }
}

void couple_draw(Elements *self)
{
    couple *Obj = ((couple *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
   
}
void couple_destory(Elements *self)
{
    couple *Obj = ((couple *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    al_stop_timer(couple_timer);
    al_stop_timer(lake_gamescene_timer);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
