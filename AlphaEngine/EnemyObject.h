#pragma once

//Unused currently
#include "Main.h"
#include "string"
#include "Buttons.h"
#include <AEVec2.h>

struct enemy {

    std::string name;
    int hp{};
    int max_hp{};
    int atk{};
    AEVec2 pos{};
    AEGfxTexture* texture;
};

enum enemy_types {
    base_rat,
    big_rat
};

enemy* create_enemy(enemy_types type, AEGfxTexture* texture);
void delete_enemy(enemy* ptr);