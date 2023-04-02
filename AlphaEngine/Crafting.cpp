/******************************************************************************/
/*!
\file		Crafting.cpp
\project	Alchemice
\author 	Low Ee Loong
\par    	email: eeloong.l\@digipen.edu
\brief		Function declaration for Game as well as define Enum used within Game loop

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/


#include "Main.h"

craftingtable::craftingtable()
{
	//Set Table aabb
	AEVec2 zero;
	AEVec2Zero(&zero);
	AEVec2Set(&zero, 1, 1);
	table_dragdrop.moveto(zero);
	table_dragdrop.changeaabb(table_width, table_height);
	two_spell_flag = false;
}

void craftingtable::crafting_table_snap(spell_book& spellbook, spells spell_id)
{
	assert((spellbook.array_size <= max_spells) || (spellbook.array_size >= (size_t)first_spell));
	//Only run when crafting table is empty
	if (this->spell1_id == spells::INVALID_SPELL && two_spell_flag == false && spellbook.spell_array[(int)spell_id].animation == false) {
		spellbook.spell_array[(int)spell_id].spell_dragdrop->mousechange(false);
		spellbook.spell_array[(int)spell_id].spell_dragdrop->moveto(this->table_dragdrop.getcoord());
		spellbook.spell_array[(int)spell_id].spell_dragdrop->move(crafting_table_buffer, 0);
		this->spell1_id = spell_id;
	}
	else if (this->spell1_id != spells::INVALID_SPELL && this->spell2_id == spells::INVALID_SPELL && spellbook.spell_array[(int)spell_id].animation == false) {
		spellbook.spell_array[(int)spell_id].spell_dragdrop->mousechange(false);
		spellbook.spell_array[(int)spell_id].spell_dragdrop->moveto(this->table_dragdrop.getcoord());
		spellbook.spell_array[(int)spell_id].spell_dragdrop->move(-crafting_table_buffer, 0);
		two_spell_flag = true;
		this->spell2_id = spell_id;
	}
	//Player dropped spell outside reset everything
	else
	{
		spellbook.spell_array[(int)this->spell1_id].spell_dragdrop->mousechange(false);
		spellbook.spell_array[(int)this->spell2_id].spell_dragdrop->mousechange(false);
		spellbook.spell_array[(int)this->spell1_id].spell_dragdrop->resetaabb();
		spellbook.spell_array[(int)this->spell2_id].spell_dragdrop->resetaabb();
		this->spell1_id = spells::INVALID_SPELL;
		this->spell2_id = spells::INVALID_SPELL;
		two_spell_flag = false;
	}
}

int craftingtable::crafting_table_update(spell_book& spellbook)
{
	timer += g_dt;

	if (timer >= crafting_time_buffer) {
		if (this->spell1_id >= first_spell && this->spell1_id <= last_spell &&
			this->spell2_id >= first_spell && this->spell2_id <= last_spell) {
			if (spellbook.combine_spells(this->spell1_id, this->spell2_id)) {
				spellbook.spell_array[(int)this->spell1_id].spell_dragdrop->resetaabb();
				spellbook.spell_array[(int)this->spell2_id].spell_dragdrop->resetaabb();
				if (spellbook.spell_array[(int)this->spell1_id].tier > tier3_last) {
					spellbook.spell_array[(int)this->spell1_id].unlocked = false;
					spellbook.spell_array[(int)this->spell1_id].animation = false;
				}
				if (spellbook.spell_array[(int)this->spell2_id].tier > tier3_last) {
					spellbook.spell_array[(int)this->spell2_id].unlocked = false;
					spellbook.spell_array[(int)this->spell2_id].animation = false;
				}
				this->spell1_id = spells::INVALID_SPELL;
				this->spell2_id = spells::INVALID_SPELL;
				timer = NULL;
				two_spell_flag = false;
				spellbook.set_discovered();
				return 2;
			}
			else {
				spellbook.spell_array[(int)this->spell1_id].spell_dragdrop->resetaabb();
				spellbook.spell_array[(int)this->spell2_id].spell_dragdrop->resetaabb();
				this->spell1_id = spells::INVALID_SPELL;
				this->spell2_id = spells::INVALID_SPELL;
				timer = NULL;
				two_spell_flag = false;
				return 3;
			}
		}
	}
	return 1;
}

spells craftingtable::get_spell1()
{
	return spell1_id;
}

void craftingtable::reset_spells()
{
	spell1_id = spells::INVALID_SPELL;
	spell2_id = spells::INVALID_SPELL;
}

spells craftingtable::get_spell2()
{
	return spell2_id;
}

void craftingtable::set_flag(bool quantum)
{
	two_spell_flag = quantum;
}

bool craftingtable::get_flag()
{
	return two_spell_flag;
}

dragdrop* craftingtable::get_dragdrop()
{
	return &(this->table_dragdrop);
}
