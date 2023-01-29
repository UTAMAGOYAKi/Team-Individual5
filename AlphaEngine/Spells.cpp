#include "Spells.h"
#include "Ingredients.h"



std::vector<Ingredients> unlockedIngredients;

void unlockIngredient(Ingredients ingredient) { 
    unlockedIngredients.push_back(ingredient);
}

Spells createSpell(Ingredients ingredient1, Ingredients ingredient2, Ingredients ingredient3) {
    if (ingredient1 == FIRE && ingredient2 == WATER && ingredient3 == WIND) return STEAM_TORNADO;
    if (ingredient1 == WATER && ingredient2 == ELECTRIC && ingredient3 == WIND) return THUNDERSTRIKE;
    if (ingredient1 == POISON && ingredient2 == FIRE && ingredient3 == WIND) return POISONOUS_INFERNO;
    if (ingredient1 == FREEZE && ingredient2 == WATER && ingredient3 == POISON) return ICE_AVALANCHE;
    if (ingredient1 == ELECTRIC && ingredient2 == FREEZE && ingredient3 == POISON) return ELECTRIC_TEMPEST;
    if (ingredient1 == FIRE && ingredient2 == WATER) return STEAM_BLAST;
    if (ingredient1 == ELECTRIC && ingredient2 == POISON) return VENOM_SHOCK;
    if (ingredient1 == FIRE && ingredient2 == ELECTRIC) return INFERNO;
    if (ingredient1 == WATER && ingredient2 == FREEZE) return ICE_NOVA;
    if (ingredient1 == ELECTRIC && ingredient2 == FREEZE) return ICE_STORM;
    return INVALID;
}

