#include "dna.h"
#include "questNode.h"
#include "../shapes/Circle.h"
#include "../scene/quest_gamescene_lifeSci.h" // for element label
#include "../scene/sceneManager.h" // for scene variable
/*
   [dna function]
*/
Elements *New_dna(int label, int x, int y, int v)
{
    dna *pDerivedObj = (dna *)malloc(sizeof(dna));
    Elements *pObj = New_Elements(0);
    // 隨機產生 1~4 整數，代表 A, T, C, G
    int base_type = (rand() % 4);
    
    char img_path[50];
    
    switch(base_type)
    {
        case 0: sprintf(img_path,"assets/image/dna_a.png"); break;
        case 1: sprintf(img_path,"assets/image/dna_t.png"); break;
        case 2: sprintf(img_path,"assets/image/dna_c.png"); break;
        case 3: sprintf(img_path,"assets/image/dna_g.png"); break;
        printf("Failed to load image: %s\n", img_path);
    }
    // setting derived object member
    pDerivedObj->img = al_load_bitmap(img_path);//
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = 400;
    pDerivedObj->v = v;
    pDerivedObj->type = base_type;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
   
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = dna_update;
    pObj->Interact = dna_interact;
    pObj->Draw = dna_draw;
    pObj->Destroy = dna_destroy;
    pObj->label = label; // 記得要設 label

    return pObj;
}
void dna_update(Elements *self)
{
    dna *Obj = (dna *)(self->pDerivedObj);
    Obj->x += Obj->v;

    // 加入 cos 波動的 y 座標
    double amplitude = 100.0;  // 波動幅度
    double frequency = 0.01;  // 波動頻率
    int base_y = 300;         // 原始 y 基準線

    Obj->y = base_y + amplitude * cos(frequency * Obj->x);

    // 更新 hitbox 位置
    Obj->hitbox->update_center_x(Obj->hitbox, Obj->v);
    Obj->hitbox->update_center_y(Obj->hitbox, Obj->y + Obj->height / 2);

    // 移動出畫面右邊，刪除
    if (Obj->x > 1920) // 假設螢幕寬度1920
    {
        self->dele = true;
        printf("dna element deleted\n");
    }
}


extern int current_keycode; // 來自主事件迴圈的輸入

void dna_interact(Elements *self)
{
    if (current_keycode == -1)
        return; // 沒有輸入

    // 找出場景中所有 DNA 元素（同 label）
    ElementVec dnas = _Get_label_elements(scene, self->label);
    
    // 找出最右邊的 DNA（最大 x）
    Elements* target_dna = NULL;
    int max_x = -1;
    for (int i = 0; i < dnas.len; i++) {
        dna* obj = (dna*)(dnas.arr[i]->pDerivedObj);
        if (!dnas.arr[i]->dele && obj->x > max_x) {
            max_x = obj->x;
            target_dna = dnas.arr[i];
        }
    }
    //printf("dna_interact: self label=%d, x=%d, max_x=%d\n", self->label, ((dna*)self->pDerivedObj)->x, max_x);

    if (self != target_dna) return;

    // 若有找到
    if (target_dna) {
        dna* obj = (dna*)(target_dna->pDerivedObj);

        if (check_match(obj, current_keycode)) {
            // 配對成功
            target_dna->dele = true;
            score += 10;
            current_keycode = -1;
        } 

        // 一次處理一個輸入，所以清空
        current_keycode = -1;
    }
}


void dna_draw(Elements *self)
{
    /*
    if (!Obj->img) {
    fprintf(stderr, "❗ERROR: DNA bitmap is NULL at draw time\n");
    return; // 不畫，避免當機
    }
    */
    dna *Obj = (dna *)(self->pDerivedObj);
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}

bool check_match(dna *d, int keycode) {
    // type: 1=A, 2=T, 3=C, 4=G
    // 對應配對按鍵：
    // A - T: 鍵盤 T (ALLEGRO_KEY_T)
    // C - G: 鍵盤 G (ALLEGRO_KEY_G)

    switch (d->type) {
        case 0: // A
            return keycode == ALLEGRO_KEY_T;
        case 1: // T
            return keycode == ALLEGRO_KEY_A;
        case 2: // C
            return keycode == ALLEGRO_KEY_G;
        case 3: // G
            return keycode == ALLEGRO_KEY_C;
        default:
            return false;
    }
}
void dna_destroy(Elements *self)
{
    dna *Obj = (dna *)(self->pDerivedObj);
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}