#pragma once

//Unused currently
#include <iostream>
#include <string.h>

struct enemy {
    
    std::string name;
    int hp{};
    int atk{};
    float pos_x;
    float pos_y;

};

enum enemy_types {
    base_rat,
    big_rat
};
#pragma once
