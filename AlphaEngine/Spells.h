#pragma once
#include "Elements.h"
#include "Buttons.h"
#include "AEengine.h"
#include <iostream>
#include <string>

enum Spells {
	// Tier 3
	TOXIC_DELUGE,
	INFERNO_BLAST,
	UMBRAL_TENDRILS,
	MAELSTROM_SURGE,
	// Tier 2
	VENOMOUS_BITE,
	SHADOW_CLOAK,
	FLAME_BURST,
	// Tier 1
	RAT_SWARM,
	BUBONIC_BLAZE,
	// Invalid
	INVALID_SPELL
};

extern const int max_spells;


class Spell {
public:
	Spell(int id, int tier, int element, std::string spell_name, AEGfxTexture* texture, bool unlocked, int base_damage, int AOE_damage, int lingeringDamage) :
		id(id), tier(tier), element(element), spell_name(spell_name), texture(texture), unlocked(unlocked), base_damage(base_damage), AOE_damage(AOE_damage), lingeringDamage(lingeringDamage) {
		AEVec2* new_coords = new AEVec2;
		coords = new_coords;
	};
	~Spell();
	// Tags
	int id = INVALID_SPELL;
	int tier = 0;
	int element = INVALID_ELEMENT;
	std::string spell_name = "";
	bool unlocked = false;
	//Damage
	int base_damage = 0;
	int AOE_damage = 0;
	int lingeringDamage = 0;
	//Draw Info
	AEGfxTexture* texture;
	AEVec2* coords{};

	void init_spells_draw(Spell& spell, AEVec2 coord);
};



// Create array of all spells
Spell* init_allspells();


// Returns true if spell can be unlocked (Not Implemented)
bool combineSpells(Spell* spellbook, int id1, int id2);

// Called when level ends etc.
void unload_spells(Spell* spellbook);