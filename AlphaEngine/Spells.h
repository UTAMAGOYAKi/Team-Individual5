#pragma once
#include "Main.h"
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
	TOXIC_DELUGE =0 ,
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

//Table Widths and Heights
enum class crafting {
	ONE_SPELL = 1,
	INVALID_COMBO,
	SUCCESFUL_COMBO
};

enum special {
	NILL = 0,
	STUN,
	LINGERING,
	AOE,
};

//Spells Bounds
//Based on tier & max and min
const enum spells first_spell = spells::TOXIC_DELUGE;
const enum spells tier3_last = spells::MAELSTROM_SURGE;
const enum spells tier2_last = spells::FLAME_BURST;
const enum spells tier1_last = spells::BUBONIC_BLAZE;
const enum spells last_spell = spells::BUBONIC_BLAZE;

//Declare total number of spells that can be created
//including invalid spells
const size_t max_spells = 9;

//---------------------------------------
//Set Spell Damage Values

//Base Damage
const int base_low = 1;
const int base_mid = 3;
const int base_high = 8;

//AOE Damage
const int aoe_low = 1;
const int aoe_mid = 2;
const int aoe_high = 3;

//Lingering Damage 
const int lingering_low = 1;
const int lingering_mid = 2;
const int lingering_high = 3;

//Lingering Rounds
const int lingering_rounds_mid = 2;

//Crafting Table properties
const float table_width_const = 180;
const float table_height_const = 180;
//Spell Properties
const float card_width_const = 102.0f;
const float card_height_const = 128.0f;
//Space between crafting table centre and spell centre when crafting
const float crafting_table_buffer = (table_width_const / 4);

//Buffer Float
const float crafting_time_buffer = 1.2f;

//Individual Spell x coord buffer
const int spell_buffer = 20;

//Spell X coord tier buffer
const int spell_tier_buffer = 40;

// crafting table timer for combination spell delay
extern f64 timer;


//A single spell object
struct Spell {
	Spell(spells id, spells tier, int element, std::string spell_name, AEGfxTexture* texture, bool unlocked, int base_damage, int special) :
		id(id), tier(tier), element(element), spell_name(spell_name), texture(texture), unlocked(unlocked), base_damage(base_damage), effects(special)
		/*aoe_damage(AOE_damage), lingering_damage(lingering_damage), lingering_rounds(lingering_rounds)* || int AOE_damage, int lingering_damage, int lingering_rounds*/ {

		//Creates new dragdrop object for collision
		spell_dragdrop = new dragdrop;
	};
	~Spell();
	// Tags
	spells id = spells::INVALID_SPELL;
	spells tier{};
	int element = INVALID_ELEMENT;
	std::string spell_name = "";
	bool discovered = false;
	bool unlocked = false;
	//Damage
	int base_damage = 0;
	int effects;

	//Draw Info
	AEGfxTexture* texture;
	dragdrop* spell_dragdrop{};

	//Known Spell list Coords
	AEVec2 known_spell_coords{};

	// card size
	const float			card_width = card_width_const;
	const float			card_height = card_height_const;

	//Reset a spells customisable stuff / variables
	void reset_spell();
};

struct spell_book {

	spell_book() = default;

	//Copy Assignment
	spell_book(spell_book const& rhs);

	//Sets the first unlock flag of the spell that got unlocked
	void set_discovered();

	//Equal Operator
	spell_book& operator=(spell_book const& rhs);

	//swap function
	void swap(spell_book& rhs);

	Spell* spell_array = nullptr;
	size_t array_size = max_spells ;
};

class craftingtable {
public:

	void crafting_table_snap(spell_book& spellbook, spells spell_id);

	//Returns 1 when crafting table is in buffer time (crafting)
	//Returns 2 when crafting table unlocked a spell succesfully
	//Returns 3 when invalid combination
	//Only to be called when two spells are input (see two_spells_flag)
	int crafting_table_update(spell_book& spellbook);
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

	//Set 2 spell flag to true or false
	void set_flag(bool);
	//Get status of flag
	bool get_flag();
private:
	const float table_width{ table_width_const };
	const float table_height{ table_height_const };
	//Spell 1 hold
	spells spell1_id = spells::INVALID_SPELL;

	//Spell 2 hold
	spells spell2_id = spells::INVALID_SPELL;

	//Crafting table snap
	dragdrop table_dragdrop{};

	// Two Spell Flag
	bool two_spell_flag;
};



// Create array of all spells
spell_book init_all_spells();


// Returns true if spell has been unlocked 
bool combine_spells(spell_book& spellbook, spells id1, spells id2);

// Called when level ends etc.
void unload_spells(spell_book& spellbook);

void draw_all_spells(spell_book& spellbook, AEGfxVertexList* pMesh);

void draw_spell_combination(spell_book& spellbook, AEGfxVertexList* pMesh);

//Set all Spells AABB and Coords when called
void init_spells_coords(spell_book& spellbook);