#pragma once
#include "Elements.h"
#include "Buttons.h"
#include "AEengine.h"
#include <iostream>
#include <string>
#include <limits>

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

enum class crafting {
	ONE_SPELL = 1,
	INVALID_COMBO,
	SUCCESFUL_COMBO
};

extern const int max_spells;



struct Spell {
	Spell(int id, int tier, int element, std::string spell_name, AEGfxTexture* texture, bool unlocked, int base_damage,
		int AOE_damage, int lingering_damage, int lingering_rounds) :
		id(id), tier(tier), element(element), spell_name(spell_name), texture(texture), unlocked(unlocked), base_damage(base_damage),
		aoe_damage(AOE_damage), lingering_damage(lingering_damage), lingering_rounds(lingering_rounds) {
		dragdrop* new_dragdrop = new dragdrop;
		spell_dragdrop = new_dragdrop;
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
	int aoe_damage = 0;
	int lingering_damage = 0;
	int lingering_rounds = 0;
	//Draw Info
	AEGfxTexture* texture;
	dragdrop* spell_dragdrop{};
	// card size
	const float			card_width = 100.0f;
	const float			card_height = 100.0f;

	//Set a Spells' AABB and Coords when called
	void init_spells_draw(Spell& spell, AEVec2 coord);

	//Reset a spells customisable stuff / variables
	void reset_spell();
};

class craftingtable {
public:
	//Returns state of the crafting table
	// State 1: When only 1 spell is input
	// State 2: When 2 spells has been input but invalid combo
	// State 3: When 2 spells has been input and spell is unlocked
	int crafting_table_update(Spell* spellbook, int spell_id);

	//Returns a pointer to the crafting table's dragdrop object
	dragdrop* get_dragdrop();
	//Default Ctor
	craftingtable();

	//Get Spell1 id
	int get_spell1();
	//Set Spell1 id
	void reset_spells();
	//Get Spell2 id
	int get_spell2();
private:
	const float table_width{ 128 };
	const float table_height{ 128 };
	//Spell 1 hold
	int spell1_id = INVALID_SPELL;

	//Spell 2 hold
	int spell2_id = INVALID_SPELL;

	//Crafting table snap
	dragdrop table_dragdrop{};
};

// Create array of all spells
Spell* init_all_spells();


// Returns true if spell has been unlocked 
bool combine_spells(Spell* spellbook, int id1, int id2);

// Called when level ends etc.
void unload_spells(Spell* spellbook);

void draw_all_spells(Spell* spellbook);



