#pragma once

//Unused currently
#include "Main.h"
#include "string"

struct enemy {

    std::string name;
    int hp{};
    int max_hp{};
    int atk{};
    float pos_x;
    float pos_y;
    AEGfxTexture* texture;
};

enum enemy_types {
    base_rat,
    big_rat
};

enemy* create_enemy(enemy_types type);
void delete_enemy(enemy* enemy_ptr);