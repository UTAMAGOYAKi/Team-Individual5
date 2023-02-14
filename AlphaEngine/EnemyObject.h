#pragma once

//Unused currently
#include <iostream>
#include <string.h>

struct enemy {
    
    std::string name;
    int hp{};
    int max_hp{};
    int atk{};
    int battle_pos; //The position it is in the battle system;
};

enum enemy_types {
    base_rat,
    big_rat
};

enemy* create_enemy(enemy_types type);