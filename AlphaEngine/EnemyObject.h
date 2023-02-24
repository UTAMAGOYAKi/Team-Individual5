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

public:
    Enemy() :name{ "" }, max_hp{ 0 }, hp{ 0 }, atk{ 0 }, pos{ 0.f,0.f }, texture{ nullptr } {};
    Enemy(enemy_types type, AEGfxTexture* input_texture) :name{ "" }, max_hp{ 0 }, hp{ 0 }, atk{ 0 }, pos{ 0.f,0.f }, texture{ input_texture }, alive{ true } {
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

    //Actions 
    //Setting position
    void set_position(AEVec2 input_pos);
    //Take Damage
    void take_damage(int val);

};

#endif // ENEMY_H