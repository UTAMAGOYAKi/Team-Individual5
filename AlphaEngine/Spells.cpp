#include "Spells.h"
<<<<<<< HEAD
#include "Ingredients.h"

structspells availablespell[12]{ STEAM_TORNADO,"STEAM_TORNADO", THUNDERSTRIKE,"THUNDERSTRIKE", POISONOUS_INFERNO ,"POISONOUS_INFERNO",
ICE_AVALANCHE ,"ICE_AVALANCHE",ELECTRIC_TEMPEST,"ELECTRIC_TEMPEST",STEAM_BLAST ,"STEAM_BLAST",VENOM_SHOCK ,"VENOM_SHOCK",
INFERNO ,"INFERNO",ICE_NOVA ,"ICE_NOVA",ICE_STORM ,"ICE_STORM", BURN ,"BURN" };
=======
#include "Elements.h"

constexpr auto max_spells = 10;
>>>>>>> parent of db7ccc0 (Integrated Spell Objects to game)

Spell available_spells[max_spells] = {
	// Tier 3 spells
	Spell(TOXIC_DELUGE, 3, POISON, "Toxic Deluge", 2, 0, 1),
	Spell(INFERNO_BLAST, 3, FIRE, "Inferno Blast", 2, 0, 1),
	Spell(UMBRAL_TENDRILS, 3, SHADOW, "Umbral Tendrils", 2, 0, 1),
	Spell(MAELSTROM_SURGE, 3, WATER, "Maelstrom Surge", 2, 0, 1),
	// Tier 2 spells
	Spell(VENOMOUS_BITE, 2, POISON, "Venomous Bite", 5, 1, 5),
	Spell(SHADOW_CLOAK, 2, SHADOW, "Shadow Cloak", 5, 1, 5),
	Spell(FLAME_BURST, 2, FIRE, "Flame Burst", 5, 1, 5),
	// Tier 1 spells
	Spell(RAT_SWARM, 1, SHADOW, "Rat Swarm", 5, 1, 5),
	Spell(BUBONIC_BLAZE, 1, FIRE, "Bubonic Blaze", 5, 1, 5),
	// Invalid Spell
	Spell(INVALID_SPELL, 0, INVALID_ELEMENT, "", 0, 0, 0),
};

<<<<<<< HEAD
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
	if (ingredient1 == FIRE && ingredient2 == POISON) return BURN;
	return INVALID;
}


std::string returnname(Spells id) {
	return availablespell[id].name;
}
=======
Spell& combineSpells(Spell& spell1, Spell& spell2) {
	if (spell1.tier == 3 && spell2.tier == 3) {
		// combine tier 3 spells
		if (spell1.element == FIRE && spell2.element == SHADOW ||
			spell2.element == FIRE && spell1.element == SHADOW) {
			// combine inferno blast and umbral tendrils to create flame burst
			return available_spells[FLAME_BURST];
		}
		else if (spell1.element == POISON && spell2.element == SHADOW ||
			spell2.element == POISON && spell1.element == SHADOW) {
			// combine toxic deluge and umbral tendrils to create venomous bite
			return available_spells[VENOMOUS_BITE];
		}
		else if (spell1.element == WATER && spell2.element == SHADOW ||
			spell2.element == WATER && spell1.element == SHADOW) {
			// combine maelstrom surge and umbral tendrils to create shadow cloak
			return available_spells[SHADOW_CLOAK];
		}
		else {
			// invalid combination
			return available_spells[INVALID_SPELL];
		}
	}
	else if (spell1.tier == 2 && spell2.tier == 2) {
		// combine tier 2 spells
		if (spell1.element == POISON && spell2.element == SHADOW ||
			spell2.element == POISON && spell1.element == SHADOW) {
			// combine shadow cloak and venemous bite to create rat swarm
			return available_spells[RAT_SWARM];
		}
		if (spell1.element == FIRE && spell2.element == POISON ||
			spell2.element == FIRE && spell1.element == POISON) {
			// combine flame burst and venemous bite to create bubonic blaze
			return available_spells[BUBONIC_BLAZE];
		}
		else {
			// invalid combination
			return available_spells[INVALID_SPELL];
		}
	}
	else {
		// invalid combination
		return available_spells[INVALID_SPELL];
	}
}


>>>>>>> parent of db7ccc0 (Integrated Spell Objects to game)

