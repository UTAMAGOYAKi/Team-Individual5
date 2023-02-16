#pragma once
#include "Ingredients.h"
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

std::string returnname(Spells id );
Spells createSpell(Ingredients ingredient1, Ingredients ingredient2, Ingredients ingredient3 = NILL );
