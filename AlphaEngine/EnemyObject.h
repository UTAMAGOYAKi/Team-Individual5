#pragma once

//Unused currently
#include "Main.h"
#include "string"
#include "Buttons.h"

struct enemy {

    std::string name;
    int hp{};
    int max_hp{};
    int atk{};
    coord pos{};
    AEGfxTexture* texture;
};

enum enemy_types {
    base_rat,
    big_rat
};

enemy* create_enemy(enemy_types type, AEGfxTexture* texture);
void delete_enemy(enemy* ptr);