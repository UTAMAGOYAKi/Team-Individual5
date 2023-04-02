/******************************************************************************/
/*!
\file		Spells.h
\project	Alchemice
\author 	Low Ee Loong
\par    	email: eeloong.l\@digipen.edu
\brief		This file defines a spell_book object that contains a
			spell array of spell objects.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once

#include "Main.h"

enum class spells
{
	// Tier 3
	TOXIC_DELUGE = 0,
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

//Spell Properties
const float card_width_const = 102.0f;
const float card_height_const = 128.0f;
const f32 spell_scale_const = 1;

//Individual Spell x coord buffer
const int spell_buffer = 20;

//Spell X coord tier buffer
const int spell_tier_buffer = 40;

//Starting Spell Pos Buffers
const f32 spell_starting_x_buffer = 80;
const f32 spell_starting_y_buffer = 82;

//Animation Constants
const f64 animation_time_total = 4;
const f64 animation_scalein_ratio = 0.30;
const f64 animation_fly_ratio = 0.70;
const f32 animation_size_max = 1.8f;


//A single spell object
struct spell {
	spell(spells id, spells tier, int element, std::string spell_name, AEGfxTexture* texture, bool unlocked, int base_damage, int special) :
		id(id), tier(tier), element(element), spell_name(spell_name), texture(texture), unlocked(unlocked), base_damage(base_damage), effects(special)
		/*aoe_damage(AOE_damage), lingering_damage(lingering_damage), lingering_rounds(lingering_rounds)* || int AOE_damage, int lingering_damage, int lingering_rounds*/ {

		//Creates new dragdrop object for collision
		spell_dragdrop = new dragdrop;
	};
	~spell();
	// Tags
	spells id = spells::INVALID_SPELL;
	spells tier{};
	int element = INVALID_ELEMENT;
	std::string spell_name = "";

	//Function Flags
	bool discovered = false;
	bool unlocked = false;
	bool animation = false;

	//Spell Scale
	f32 spell_scale = spell_scale_const;

	//Damage
	int base_damage = 0;
	int effects;

	//Draw Info
	AEGfxTexture* texture;
	dragdrop* spell_dragdrop{};

	//Known Spell list Coords
	AEVec2 list_spell_coords{};

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

	//Draws Every Single Spell in a given spellbook
	void draw_all_spells(AEGfxVertexList* pMesh);

	// Returns true if spell has been unlocked 
	bool combine_spells(spells id1, spells id2);

	//Testing Animations (might not work in time)
	void crafting_fly();

	//Set all Spells AABB and Coords when called
	void init_spells_coords();

	// Called when level ends etc.
	void unload_spells();

	spell* spell_array = nullptr;
	size_t array_size = max_spells;
};

// Create array of all spells
spell_book init_all_spells();

//TestingAnimations Might Not Work In Time
f64 smooth_step(f32 edge0, f32 edge1, f32 x);

f64 smooth_stepinout_lerp(f32 startValue, f32 endValue, f64 t);