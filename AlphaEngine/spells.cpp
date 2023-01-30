#include "spells.h"
#include "Ingredients.h"

structspells availablespell[12]{ STEAM_TORNADO,"STEAM_TORNADO", THUNDERSTRIKE,"THUNDERSTRIKE", POISONOUS_INFERNO ,"POISONOUS_INFERNO",
ICE_AVALANCHE ,"ICE_AVALANCHE",ELECTRIC_TEMPEST,"ELECTRIC_TEMPEST",STEAM_BLAST ,"STEAM_BLAST",VENOM_SHOCK ,"VENOM_SHOCK",
INFERNO ,"INFERNO",ICE_NOVA ,"ICE_NOVA",ICE_STORM ,"ICE_STORM", BURN ,"BURN" };


Spells create_spell(ingredients ingredient1, ingredients ingredient2, ingredients ingredient3) {
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
	if (ingredient1 == FIRE && ingredient2 == POISON) return BURN;
	return INVALID;
}


std::string returnname(Spells id) {
	return availablespell[id].name;
}