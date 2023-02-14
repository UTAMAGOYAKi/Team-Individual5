#include "EnemyObject.h"

//Unused currently
enemy* create_enemy(enemy_types type, AEGfxTexture* texture) {
    enemy* new_enemy{ new enemy };
    new_enemy->name;

    switch (type)
    {
    case base_rat:
        new_enemy->name = "Rat";
        new_enemy->atk = 10;
        new_enemy->max_hp = 10;
        new_enemy->hp = new_enemy->max_hp; //Initialized hp will be same as max_hp;
        new_enemy->texture = texture;
        break;

    case big_rat:
        new_enemy->name = "Big Rat";
        new_enemy->atk = 15;
        new_enemy->max_hp = 15;
        new_enemy->hp = new_enemy->max_hp;
        new_enemy->texture = texture;
        break;

    default:
        break;
    }
    return new_enemy;
}

void delete_enemy(enemy* enemy_ptr) {
    //AEGfxTextureUnload(enemy_ptr->texture);
    delete enemy_ptr;
}