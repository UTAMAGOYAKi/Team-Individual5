#pragma once
#include "ingredients.h"
#include <string>


enum Spells {
    STEAM_TORNADO,
    THUNDERSTRIKE,
    POISONOUS_INFERNO,
    ICE_AVALANCHE,
    ELECTRIC_TEMPEST,
    STEAM_BLAST,
    VENOM_SHOCK,
    INFERNO,
    ICE_NOVA,
    ICE_STORM,
    BURN,
    INVALID
};

struct structspells {
    int id = 0;
    std::string name = "";
};

std::string return_name(Spells id);
Spells create_spell(ingredients ingredient1, ingredients ingredient2, ingredients ingredient3 = NILL);