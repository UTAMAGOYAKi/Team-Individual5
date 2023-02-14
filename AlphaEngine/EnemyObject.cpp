#include "EnemyObject.h"

//Unused currently
enemy* create_enemy(enemy_types type) {
    enemy* new_enemy{ new enemy };
    new_enemy->name;

    switch (type)
    {
    case base_rat:
        new_enemy->name = "Rat";
        new_enemy->atk = 10;
        new_enemy->max_hp = 10;
        new_enemy->hp = new_enemy->max_hp; //Initialized hp will be same as max_hp;
        new_enemy->texture = AEGfxTextureLoad("Assets/rat_Piskel.png");
        break;

    case big_rat:
        new_enemy->name = "Big Rat";
        new_enemy->atk = 15;
        new_enemy->max_hp = 15;
        new_enemy->hp = new_enemy->max_hp;
        new_enemy->texture = AEGfxTextureLoad("Assets/rat_Piskel.png");
        break;

    default:
        break;
    }
    return new_enemy;
}

void delete_enemy(enemy* enemy_ptr) {
    delete enemy_ptr;
}