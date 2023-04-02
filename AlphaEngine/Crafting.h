/******************************************************************************/
/*!
\file		Crafting.h
\project	Alchemice
\author 	Low Ee Loong
\par    	email: eeloong.l\@digipen.edu
\brief		Function declaration for Game as well as define Enum used within Game loop

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once

//Table Widths and Heights
//Crafting Table properties
const float table_width_const = 180;
const float table_height_const = 180;
//Space between crafting table centre and spell centre when crafting
const float crafting_table_buffer = (table_width_const / 4);

//Buffer Float for crafting table effects/ delay
const float crafting_time_buffer = 1.0f;




struct spell_book;
enum class spells;

enum class crafting {
	ONE_SPELL = 1,
	INVALID_COMBO,
	SUCCESFUL_COMBO
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