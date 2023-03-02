#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

//Unused currently
#include "Main.h"
#include "string"
#include "Buttons.h"
#include <AEVec2.h>

#define TOTAL_ENEMY 3

enum enemy_types {
    base_rat,
    big_rat
};

class Enemy {
private:
    std::string name;
    int max_hp;
    int hp;
    int atk;
    AEVec2 pos;
    AEGfxTexture* texture;
    bool alive; //Dead = 0; Alive = 1;
    int size; //pixel size
    aabb enemy_aabb;
    int frame_num = 0;
    float frame_time = 0.6667;
    float frame_timer = frame_timer;

public:
    Enemy() : name{ "" }, max_hp{ 0 }, hp{ 0 }, atk{ 0 }, pos{ 0.f,0.f }, texture{ nullptr }, alive{ 1 }, size{ 0 }, enemy_aabb{ CreateAABB() } {};
    Enemy(enemy_types type, AEGfxTexture* input_texture) :name{ "" }, max_hp{ 0 }, hp{ 0 }, atk{ 0 }, pos{ 0.f,0.f }, texture{ input_texture }, alive{ true }, size{ 128 } {
        switch (type)
        {
        case base_rat:
            name = "Rat";
            atk = 2;
            max_hp = 10;
            hp = max_hp; //Initialized hp will be same as max_hp;

            break;

        case big_rat:
            name = "Big Rat";
            atk = 5;
            max_hp = 15;
            hp = max_hp;
            break;

        default:
            name = "Rat";
            atk = 10;
            max_hp = 10;
            hp = max_hp; //Initialized hp will be same as max_hp;
            break;
        }
    };//two argument constructor

    ~Enemy() {}; //deconstructor

    //Member functions

    //Used to retrieve data from class
    std::string get_name();
    int get_max_hp();
    int get_hp();
    int get_atk();
    AEVec2 get_pos();
    AEGfxTexture* get_texture();
    bool is_alive();
    int get_frame_num();

    //Actions 
    //Setting position and sets aabb
    void set_position(AEVec2 input_pos);
    //Take Damage
    void take_damage(int val);
    void set_frame_num(int);

    void update_animation(float dt);


};

//Animations
//Loading of Animations
//AEGfxTexture blast[3] = { *AEGfxTextureLoad("Assets/blast1.png"), *AEGfxTextureLoad("Assets/blast2.png"), *AEGfxTextureLoad("Assets/blast3.png") };

//void blast_animation(AEGfxVertexList* pMesh,Enemy enemy, AEGfxTexture blast[],int frame) {
//    float frame_time{1};
//    float curr_time{frame_time};
//
//    AEMtx33 scale{ 0 };
//    AEMtx33 rotate{ 0 };
//    AEMtx33 translate{ 0 };
//    AEMtx33 transform{ 0 };
//    
//    for (int i{}; i < frame; i++) {
//        AEGfxTextureSet(&blast[i], 0, 0);
//        AEMtx33Trans(&translate, (f32)(enemy.get_pos().x), (f32)(enemy.get_pos().y));
//        AEMtx33Rot(&rotate, 0);
//        AEMtx33Scale(&scale, 100.f, 100.f);
//        AEMtx33Concat(&transform, &rotate, &scale);
//        AEMtx33Concat(&transform, &translate, &transform);
//        AEGfxSetTransform(transform.m);
//        AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
//
//        //timer
//        while (curr_time) {
//            curr_time -= (f32)AEFrameRateControllerGetFrameTime();
//        }
//        curr_time = frame_time;
//    }
//}


#endif // ENEMY_H