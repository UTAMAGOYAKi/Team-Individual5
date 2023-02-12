#include "EnemyObject.h"

//Unused currently
enemy* create_enemy(std::string name, enemy_types type) {
    enemy* new_enemy{ new enemy };
    new_enemy->name;

    switch (type)
    {
    case base_rat:
        new_enemy->atk = 10;
        new_enemy->hp = 10;
        break;

    case big_rat:
        new_enemy->atk = 15;
        new_enemy->hp = 15;
        break;

    default:
        break;
    }
    return new_enemy;
}

void delete_enemy(enemy* enemy_ptr) {
    delete enemy_ptr;
}