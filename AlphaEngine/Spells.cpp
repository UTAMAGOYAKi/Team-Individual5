/******************************************************************************/
/*!
\file		Spells.cpp
\project	Alchemice
\author 	Low Ee Loong
\par    	email: eeloong.l\@digipen.edu
\brief		This file declares a spell_book object that contains a 
			spell array of spell objects.


Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "Main.h"

//Declare textures for spells
AEGfxTexture* toxic_deluge{}, * inferno_blast{}, * umbral_tendrils{}, * maelstrom_surge{}, * venemous_bite{},
* shadow_cloak{}, * flame_burst{}, * rat_swarm{}, * bubonic_blaze{};


//Know Spell Coords Counter
//Increases the known spell y coords everytime
//player discovers a new spell
float known_spell_multiplier_two = known_spell_height;
float known_spell_multiplier_one = known_spell_height;

spell_book init_all_spells()
{

	spell_book x;

	//Currently Textures are used as placeholder, ignore the meaning
	umbral_tendrils = AEGfxTextureLoad("Assets/Card-Sprite-umbral.png");
	std::cout << "spell_g MemLoc: " << umbral_tendrils << std::endl;
	inferno_blast = AEGfxTextureLoad("Assets/Card-Sprite-Inferno-Blast.png");
	std::cout << "fire MemLoc: " << inferno_blast << std::endl;
	toxic_deluge = AEGfxTextureLoad("Assets/Card-Sprite-Toxic-Deluge.png");
	std::cout << "poison MemLoc: " << toxic_deluge << std::endl;
	maelstrom_surge = AEGfxTextureLoad("Assets/Card-Sprite-Maelstrom.png");
	std::cout << "shame MemLoc: " << maelstrom_surge << std::endl;
	venemous_bite = AEGfxTextureLoad("Assets/Card-Sprite-Venemous.png");
	std::cout << "venemous_bite MemLoc: " << venemous_bite << std::endl;
	shadow_cloak = AEGfxTextureLoad("Assets/Card-Sprite-shadow-cloak.png");
	std::cout << "shadow_cloak MemLoc: " << shadow_cloak << std::endl;
	flame_burst = AEGfxTextureLoad("Assets/Card-Sprite-flame-burst.png");
	std::cout << "flame_burst MemLoc: " << flame_burst << std::endl;
	rat_swarm = AEGfxTextureLoad("Assets/Card-Sprite-Rat-Swarm.png");
	std::cout << "rat_swarm MemLoc: " << rat_swarm << std::endl;
	bubonic_blaze = AEGfxTextureLoad("Assets/Card-Sprite-Bubonic-Blaze.png");
	std::cout << "bubonic_blaze MemLoc: " << bubonic_blaze << std::endl;
	std::cout << "Creating All " << max_spells << " Spells" << std::endl;

	// +1 due to invalid spell
	Spell* spellbook = new Spell[max_spells + 1]{
		// Tier 3 spells
		Spell(spells::TOXIC_DELUGE, tier3_last, POISON, "Toxic Deluge",toxic_deluge,true, base_low, NILL),
		Spell(spells::INFERNO_BLAST,tier3_last, FIRE, "Inferno Blast",inferno_blast,true, base_low, NILL),
		Spell(spells::UMBRAL_TENDRILS, tier3_last, SHADOW, "Umbral Tendrils",umbral_tendrils,true,base_low, NILL),
		Spell(spells::MAELSTROM_SURGE, tier3_last, WATER, "Maelstrom Surge",maelstrom_surge,true,base_low, NILL),
		// Tier 2 spells
		Spell(spells::VENOMOUS_BITE, tier2_last, POISON, "Venomous Bite",venemous_bite,false, base_mid,LINGERING),
		Spell(spells::SHADOW_CLOAK, tier2_last, SHADOW, "Shadow Cloak",shadow_cloak,false, base_mid, STUN),
		Spell(spells::FLAME_BURST, tier2_last, FIRE, "Flame Burst",flame_burst,false, base_mid, AOE),
		// Tier aoe_low spells
		Spell(spells::RAT_SWARM, tier1_last, SHADOW, "Rat Swarm",rat_swarm,false, base_high,STUN),
		Spell(spells::BUBONIC_BLAZE,tier1_last, FIRE, "Bubonic Blaze",bubonic_blaze,false, base_high,LINGERING),
		// Invalid Spell
		Spell(spells::INVALID_SPELL,spells::INVALID_SPELL , INVALID_ELEMENT, "",nullptr, false,NULL,NILL)
	};

	x.spell_array = spellbook;

	return x;
}

Spell::~Spell()
{
	delete spell_dragdrop;
}


void Spell::reset_spell()
{
	unlocked = false;
	delete spell_dragdrop;
	spell_dragdrop = new dragdrop;
}

bool draw_spell_combination(spell_book& spellbook, spells id1, spells id2) {
	assert(spellbook.array_size <= max_spells);
	assert(spellbook.array_size >= (size_t)first_spell);
	if (spellbook.spell_array[(int)id1].tier == tier3_last && spellbook.spell_array[(int)id2].tier == tier3_last) {
		// combine tier 3 spells
		if (spellbook.spell_array[(int)id1].element == FIRE && spellbook.spell_array[(int)id2].element == SHADOW ||
			spellbook.spell_array[(int)id2].element == FIRE && spellbook.spell_array[(int)id1].element == SHADOW) {
			// combine inferno blast and umbral tendrils to create flame burst
			if (spellbook.spell_array[(int)spells::FLAME_BURST].unlocked) {
				return false;
			}
			spellbook.spell_array[(int)spells::FLAME_BURST].unlocked = true;
			return true;
		}
		else if (spellbook.spell_array[(int)id1].element == POISON && spellbook.spell_array[(int)id2].element == SHADOW ||
			spellbook.spell_array[(int)id2].element == POISON && spellbook.spell_array[(int)id1].element == SHADOW) {
			// combine toxic deluge and umbral tendrils to create venomous bite
			if (spellbook.spell_array[(int)spells::VENOMOUS_BITE].unlocked) {
				return false;
			}
			spellbook.spell_array[(int)spells::VENOMOUS_BITE].unlocked = true;
			return true;
		}
		else if (spellbook.spell_array[(int)id1].element == WATER && spellbook.spell_array[(int)id2].element == SHADOW ||
			spellbook.spell_array[(int)id2].element == WATER && spellbook.spell_array[(int)id1].element == SHADOW) {
			// combine maelstrom surge and umbral tendrils to create shadow cloak

			if (spellbook.spell_array[(int)spells::SHADOW_CLOAK].unlocked) {
				return false;
			}

			spellbook.spell_array[(int)spells::SHADOW_CLOAK].unlocked = true;;
			return true;

		}
		else {
			// invalid combination
			return false;
		}
	}
	else if (spellbook.spell_array[(int)id1].tier == tier2_last && spellbook.spell_array[(int)id2].tier == tier2_last) {
		// combine tier 2 spells
		if (spellbook.spell_array[(int)id1].element == POISON && spellbook.spell_array[(int)id2].element == SHADOW ||
			spellbook.spell_array[(int)id2].element == POISON && spellbook.spell_array[(int)id1].element == SHADOW) {
			// combine shadow cloak and venemous bite to create rat swarm

			if (spellbook.spell_array[(int)spells::RAT_SWARM].unlocked) {
				return false;
			}

			spellbook.spell_array[(int)spells::RAT_SWARM].unlocked = true;
			return true;
		}
		if (spellbook.spell_array[(int)id1].element == FIRE && spellbook.spell_array[(int)id2].element == POISON ||
			spellbook.spell_array[(int)id2].element == FIRE && spellbook.spell_array[(int)id1].element == POISON) {
			// combine flame burst and venemous bite to create bubonic blaze

			if (spellbook.spell_array[(int)spells::BUBONIC_BLAZE].unlocked) {
				return false;
			}

			spellbook.spell_array[(int)spells::BUBONIC_BLAZE].unlocked = true;
			return true;
		}
		else {
			// invalid combination
			return false;
		}
	}
	else {
		// invalid combination
		return false;
	}
}

spell_book::spell_book(spell_book const& rhs)
{
	this->spell_array = rhs.spell_array;
}

void spell_book::set_discovered()
{
	for (int i = 0; i <= array_size - 1; i++) {
		if (spell_array[i].unlocked == true && spell_array[i].discovered == false) {
			if (spell_array[i].tier == tier2_last) {
				spell_array[i].known_spell_coords.y += known_spell_multiplier_two;
				known_spell_multiplier_two -= known_spell_height;
			}
			else if (spell_array[i].tier == tier1_last) {
				spell_array[i].known_spell_coords.y += known_spell_multiplier_one;
				known_spell_multiplier_one -= known_spell_height;
			}
			spell_array[i].discovered = true;
		}
	}
}

spell_book& spell_book::operator=(spell_book const& rhs)
{
	spell_book tmp{ rhs };
	this->swap(tmp);
	return *this;
}

void spell_book::swap(spell_book& rhs)
{
	std::swap(this->spell_array, rhs.spell_array);
	std::swap(this->array_size, rhs.array_size);
}

void spell_book::draw_all_spells(AEGfxVertexList* pMesh)
{
	assert((this->array_size <= max_spells) || (this->array_size >= (size_t)first_spell));
	AEMtx33 scale{ };
	AEMtx33 rotate{  };
	AEMtx33 translate{  };
	AEMtx33 transform{  };
	for (int i = 0; i <= this->array_size - 1; i++) {
		if (this->spell_array[i].unlocked == true) {
			AEGfxTextureSet(this->spell_array[i].texture, 0, 0);
			AEMtx33Trans(&translate, this->spell_array[i].spell_dragdrop->getcoord().mid.x, -this->spell_array[i].spell_dragdrop->getcoord().mid.y);
			AEMtx33Rot(&rotate, 0);
			AEMtx33Scale(&scale, this->spell_array[i].card_width, this->spell_array[i].card_height);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		}
	}
}

bool spell_book::combine_spells(spells id1, spells id2)
{
	assert(this->array_size <= max_spells);
	assert(this->array_size >= (size_t)first_spell);
	if (this->spell_array[(int)id1].tier == tier3_last && this->spell_array[(int)id2].tier == tier3_last) {
		// combine tier 3 spells
		if (this->spell_array[(int)id1].element == FIRE && this->spell_array[(int)id2].element == SHADOW ||
			this->spell_array[(int)id2].element == FIRE && this->spell_array[(int)id1].element == SHADOW) {
			// combine inferno blast and umbral tendrils to create flame burst
			if (this->spell_array[(int)spells::FLAME_BURST].unlocked) {
				return false;
			}
			this->spell_array[(int)spells::FLAME_BURST].unlocked = true;
			return true;
		}
		else if (this->spell_array[(int)id1].element == POISON && this->spell_array[(int)id2].element == SHADOW ||
			this->spell_array[(int)id2].element == POISON && this->spell_array[(int)id1].element == SHADOW) {
			// combine toxic deluge and umbral tendrils to create venomous bite
			if (this->spell_array[(int)spells::VENOMOUS_BITE].unlocked) {
				return false;
			}
			this->spell_array[(int)spells::VENOMOUS_BITE].unlocked = true;
			return true;
		}
		else if (this->spell_array[(int)id1].element == WATER && this->spell_array[(int)id2].element == SHADOW ||
			this->spell_array[(int)id2].element == WATER && this->spell_array[(int)id1].element == SHADOW) {
			// combine maelstrom surge and umbral tendrils to create shadow cloak

			if (this->spell_array[(int)spells::SHADOW_CLOAK].unlocked) {
				return false;
			}
			this->spell_array[(int)spells::SHADOW_CLOAK].unlocked = true;
			return true;
		}
		else {
			// invalid combination
			return false;
		}
	}
	else if (this->spell_array[(int)id1].tier == tier2_last && this->spell_array[(int)id2].tier == tier2_last) {
		// combine tier 2 spells
		if (this->spell_array[(int)id1].element == POISON && this->spell_array[(int)id2].element == SHADOW ||
			this->spell_array[(int)id2].element == POISON && this->spell_array[(int)id1].element == SHADOW) {
			// combine shadow cloak and venemous bite to create rat swarm

			if (this->spell_array[(int)spells::RAT_SWARM].unlocked) {
				return false;
			}

			this->spell_array[(int)spells::RAT_SWARM].unlocked = true;
			return true;
		}
		if (this->spell_array[(int)id1].element == FIRE && this->spell_array[(int)id2].element == POISON ||
			this->spell_array[(int)id2].element == FIRE && this->spell_array[(int)id1].element == POISON) {
			// combine flame burst and venemous bite to create bubonic blaze

			if (this->spell_array[(int)spells::BUBONIC_BLAZE].unlocked) {
				return false;
			}

			this->spell_array[(int)spells::BUBONIC_BLAZE].unlocked = true;
			return true;
		}
		else {
			// invalid combination
			return false;
		}
	}
	else {
		// invalid combination
		return false;
	}
}

void spell_book::init_spells_coords()
{
	assert(this->array_size <= max_spells);
	assert(this->array_size >= (size_t)first_spell);
	AEVec2 cards;
	AEVec2Set(&cards, (f32)-(AEGetWindowWidth() / 2) + 80, -((f32)-(AEGetWindowHeight() / 2) + 82));

	//All Tier 3 spells
	for (int i = (int)first_spell; i <= (int)tier3_last; ++i) {
		this->spell_array[i].spell_dragdrop->moveto(cards);
		this->spell_array[i].spell_dragdrop->set_origin();
		cards.x += card_width_const + spell_buffer;
	}
	cards.x += spell_tier_buffer;
	//All Tier 2 spells
	for (int i = (int)tier3_last + 1; i <= (int)tier2_last; ++i) {
		this->spell_array[i].known_spell_coords.x = (AEGetWindowWidth() * known_spell_x) / 2;
		this->spell_array[i].known_spell_coords.y = (AEGetWindowHeight() * known_spell_two_y) / 2 - known_spell_height - known_spell_ybuffer;

		this->spell_array[i].spell_dragdrop->moveto(cards);
		this->spell_array[i].spell_dragdrop->set_origin();
		cards.x += card_width_const + spell_buffer;
	}
	cards.x += spell_tier_buffer;
	//All Tier 1 spells
	for (int i = (int)tier2_last + 1; i <= (int)tier1_last; ++i) {
		this->spell_array[i].known_spell_coords.x = AEGetWindowWidth() * known_spell_x / 2;
		this->spell_array[i].known_spell_coords.y = (AEGetWindowHeight() * known_spell_one_y) / 2 - known_spell_height - known_spell_ybuffer;

		this->spell_array[i].spell_dragdrop->moveto(cards);
		this->spell_array[i].spell_dragdrop->set_origin();
		cards.x += card_width_const + spell_buffer;
	}

	for (int i = 0; i <= this->array_size - 1; i++) {
		this->spell_array[i].spell_dragdrop->changeaabb(card_width_const, card_height_const);
	}
}

void spell_book::unload_spells()
{
	AEGfxTextureUnload(umbral_tendrils);
	AEGfxTextureUnload(inferno_blast);
	AEGfxTextureUnload(toxic_deluge);
	AEGfxTextureUnload(maelstrom_surge);
	AEGfxTextureUnload(venemous_bite);
	AEGfxTextureUnload(shadow_cloak);
	AEGfxTextureUnload(flame_burst);
	AEGfxTextureUnload(rat_swarm);
	AEGfxTextureUnload(bubonic_blaze);
	delete[] this->spell_array;
}
