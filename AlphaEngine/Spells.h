#pragma once
#include "Elements.h"
#include "Buttons.h"
#include "AEengine.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <assert.h>

enum class spells {
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

//Spells Bounds
//Based on tier & max and min
const enum spells first_spell = spells::TOXIC_DELUGE;
const enum spells tier3_last = spells::MAELSTROM_SURGE;
const enum spells tier2_last = spells::FLAME_BURST;
const enum spells tier1_last = spells::BUBONIC_BLAZE;
const enum spells last_spell = spells::BUBONIC_BLAZE;

enum class crafting {
	ONE_SPELL = 1,
	INVALID_COMBO,
	SUCCESFUL_COMBO
};


//Declare total number of spells that can be created
//including invalid spells
const size_t max_spells = 9;



//A single spell object
struct Spell {
	Spell(spells id, spells tier, int element, std::string spell_name, AEGfxTexture* texture, bool unlocked, int base_damage,
		int AOE_damage, int lingering_damage, int lingering_rounds) :
		id(id), tier(tier), element(element), spell_name(spell_name), texture(texture), unlocked(unlocked), base_damage(base_damage),
		aoe_damage(AOE_damage), lingering_damage(lingering_damage), lingering_rounds(lingering_rounds) {

		//Creates new dragdrop object for collision
		spell_dragdrop = new dragdrop;
	};
	~Spell();
	// Tags
	spells id = spells::INVALID_SPELL;
	spells tier{};
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
	const float			card_width = 102.0f;
	const float			card_height = 128.0f;

	//Set a Spells' AABB and Coords when called
	void init_spells_draw(Spell& spell, AEVec2 coord);

	//Reset a spells customisable stuff / variables
	void reset_spell();
};

struct spell_book {

	spell_book() = default;

	//Copy Assignment
	spell_book(spell_book const& rhs);

	//Equal Operator
	spell_book& operator=(spell_book const& rhs);

	//swap function
	void swap(spell_book& rhs);

	Spell* spell_array = nullptr;
	size_t array_size = max_spells;
};

class craftingtable {
public:
	//Returns state of the crafting table
	// State 1: When only 1 spell is input
	// State 2: When 2 spells has been input but invalid combo
	// State 3: When 2 spells has been input and spell is unlocked
	int crafting_table_update(spell_book& spellbook, spells spell_id);

	//Returns a pointer to the crafting table's dragdrop object
	dragdrop* get_dragdrop();
	//Default Ctor
	craftingtable();

	//Get Spell1 id
	spells get_spell1();
	//Set Spell1 id
	void reset_spells();
	//Get Spell2 id
	spells get_spell2();
private:
	const float table_width{ 128 };
	const float table_height{ 128 };
	//Spell 1 hold
	spells spell1_id = spells::INVALID_SPELL;

	//Spell 2 hold
	spells spell2_id = spells::INVALID_SPELL;

	//Crafting table snap
	dragdrop table_dragdrop{};
};



// Create array of all spells
spell_book init_all_spells();


// Returns true if spell has been unlocked 
bool combine_spells(spell_book& spellbook, spells id1, spells id2);

// Called when level ends etc.
void unload_spells(spell_book& spellbook);

void draw_all_spells(spell_book& spellbook, AEGfxVertexList* pMesh);



