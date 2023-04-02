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
#include <cmath>

//Declare textures for spells
AEGfxTexture* toxic_deluge{}, * inferno_blast{}, * umbral_tendrils{}, * maelstrom_surge{}, * venemous_bite{},
* shadow_cloak{}, * flame_burst{}, * rat_swarm{}, * bubonic_blaze{};




//Know Spell Coords Counter
//Increases the known spell y coords everytime
//player discovers a new spell
float known_spell_multiplier_two = known_spell_height;
float known_spell_multiplier_one = known_spell_height;

//Animation Variable
f64 animation_timer{};
AEVec2 animation_pos{};

spell_book init_all_spells()
{
	spell_book x;

	//Currently Textures are used as placeholder, ignore the meaning
	umbral_tendrils = AEGfxTextureLoad("Assets/Art/Card-Sprite-umbral.png");
	inferno_blast = AEGfxTextureLoad("Assets/Art/Card-Sprite-Inferno-Blast.png");
	toxic_deluge = AEGfxTextureLoad("Assets/Art/Card-Sprite-Toxic-Deluge.png");
	maelstrom_surge = AEGfxTextureLoad("Assets/Art/Card-Sprite-Maelstrom.png");
	venemous_bite = AEGfxTextureLoad("Assets/Art/Card-Sprite-Venemous.png");
	shadow_cloak = AEGfxTextureLoad("Assets/Art/Card-Sprite-shadow-cloak.png");
	flame_burst = AEGfxTextureLoad("Assets/Art/Card-Sprite-flame-burst.png");
	rat_swarm = AEGfxTextureLoad("Assets/Art/Card-Sprite-Rat-Swarm.png");
	bubonic_blaze = AEGfxTextureLoad("Assets/Art/Card-Sprite-Bubonic-Blaze.png");

	// +1 due to invalid spell
	spell* spellbook = new spell[max_spells + 1]{
		// Tier 3 spells
		spell(spells::TOXIC_DELUGE, tier3_last, POISON, "Toxic Deluge",toxic_deluge,true, base_low, NILL),
		spell(spells::INFERNO_BLAST,tier3_last, FIRE, "Inferno Blast",inferno_blast,true, base_low, NILL),
		spell(spells::UMBRAL_TENDRILS, tier3_last, SHADOW, "Umbral Tendrils",umbral_tendrils,true,base_low, NILL),
		spell(spells::MAELSTROM_SURGE, tier3_last, WATER, "Maelstrom Surge",maelstrom_surge,true,base_low, NILL),
		// Tier 2 spells
		spell(spells::VENOMOUS_BITE, tier2_last, POISON, "Venomous Bite",venemous_bite,false, base_mid,LINGERING),
		spell(spells::SHADOW_CLOAK, tier2_last, SHADOW, "Shadow Cloak",shadow_cloak,false, base_mid, STUN),
		spell(spells::FLAME_BURST, tier2_last, FIRE, "Flame Burst",flame_burst,false, base_mid, AOE),
		// Tier aoe_low spells
		spell(spells::RAT_SWARM, tier1_last, SHADOW, "Rat Swarm",rat_swarm,false, base_high,STUN),
		spell(spells::BUBONIC_BLAZE,tier1_last, FIRE, "Bubonic Blaze",bubonic_blaze,false, base_high,LINGERING),
		// Invalid Spell
		spell(spells::INVALID_SPELL,spells::INVALID_SPELL , INVALID_ELEMENT, "",nullptr, false,NULL,NILL)
	};
	x.spell_array = spellbook;
	return x;
}

spell::~spell()
{
	delete spell_dragdrop;
}


void spell::reset_spell()
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
				spell_array[i].list_spell_coords.y += known_spell_multiplier_two;
				known_spell_multiplier_two -= known_spell_height;

			}
			else if (spell_array[i].tier == tier1_last) {
				spell_array[i].list_spell_coords.y += known_spell_multiplier_one;
				known_spell_multiplier_one -= known_spell_height;
			}
			spell_array[i].discovered = true;
		}
		//Testing Spell Animations
		/*if (spell_array[i].unlocked == true && spell_array[i].animation == false && spell_array[i].tier != tier3_last) {
			spell_array[i].animation = true;
		}*/
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
			AEMtx33Scale(&scale, this->spell_array[i].card_width * this->spell_array[i].spell_scale, this->spell_array[i].card_height * this->spell_array[i].spell_scale);
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
			this->spell_array[(int)spells::FLAME_BURST].animation = true;
			this->spell_array[(int)spells::FLAME_BURST].unlocked = true;
			return true;
		}
		else if (this->spell_array[(int)id1].element == POISON && this->spell_array[(int)id2].element == SHADOW ||
			this->spell_array[(int)id2].element == POISON && this->spell_array[(int)id1].element == SHADOW) {
			// combine toxic deluge and umbral tendrils to create venomous bite
			if (this->spell_array[(int)spells::VENOMOUS_BITE].unlocked) {
				return false;
			}
			this->spell_array[(int)spells::VENOMOUS_BITE].animation = true;
			this->spell_array[(int)spells::VENOMOUS_BITE].unlocked = true;
			return true;
		}
		else if (this->spell_array[(int)id1].element == WATER && this->spell_array[(int)id2].element == SHADOW ||
			this->spell_array[(int)id2].element == WATER && this->spell_array[(int)id1].element == SHADOW) {
			// combine maelstrom surge and umbral tendrils to create shadow cloak

			if (this->spell_array[(int)spells::SHADOW_CLOAK].unlocked) {
				return false;
			}
			this->spell_array[(int)spells::SHADOW_CLOAK].animation = true;
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
			this->spell_array[(int)spells::RAT_SWARM].animation = true;
			this->spell_array[(int)spells::RAT_SWARM].unlocked = true;
			return true;
		}
		if (this->spell_array[(int)id1].element == FIRE && this->spell_array[(int)id2].element == POISON ||
			this->spell_array[(int)id2].element == FIRE && this->spell_array[(int)id1].element == POISON) {
			// combine flame burst and venemous bite to create bubonic blaze

			if (this->spell_array[(int)spells::BUBONIC_BLAZE].unlocked) {
				return false;
			}
			this->spell_array[(int)spells::BUBONIC_BLAZE].animation = true;
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
	AEVec2Set(&cards, (f32)-(AEGetWindowWidth() / 2) + spell_starting_x_buffer, -((f32)-(AEGetWindowHeight() / 2) + spell_starting_y_buffer));

	//All Tier 3 spells
	for (int i = (int)first_spell; i <= (int)tier3_last; ++i) {
		this->spell_array[i].spell_dragdrop->moveto(cards);
		this->spell_array[i].spell_dragdrop->set_origin();
		cards.x += card_width_const + spell_buffer;
	}
	cards.x += spell_tier_buffer;
	//All Tier 2 spells
	for (int i = (int)tier3_last + 1; i <= (int)tier2_last; ++i) {
		this->spell_array[i].list_spell_coords.x = (AEGetWindowWidth() * known_spell_x) / 2;
		this->spell_array[i].list_spell_coords.y = (AEGetWindowHeight() * known_spell_two_y) / 2 - known_spell_height - known_spell_ybuffer;

		this->spell_array[i].spell_dragdrop->moveto(cards);
		this->spell_array[i].spell_dragdrop->set_origin();
		cards.x += card_width_const + spell_buffer;
	}
	cards.x += spell_tier_buffer;
	//All Tier 1 spells
	for (int i = (int)tier2_last + 1; i <= (int)tier1_last; ++i) {
		this->spell_array[i].list_spell_coords.x = AEGetWindowWidth() * known_spell_x / 2;
		this->spell_array[i].list_spell_coords.y = (AEGetWindowHeight() * known_spell_one_y) / 2 - known_spell_height - known_spell_ybuffer;

		this->spell_array[i].spell_dragdrop->moveto(cards);
		this->spell_array[i].spell_dragdrop->set_origin();
		cards.x += card_width_const + spell_buffer;
	}

	for (int i = 0; i <= this->array_size - 1; i++) {
		this->spell_array[i].spell_dragdrop->changeaabb(card_width_const, card_height_const);
	}
}

//Testing Animations:

void spell_book::crafting_fly()
{

	for (int i = 0; i < max_spells; i++) {
		if (this->spell_array[i].animation == true) {
			animation_timer += g_dt; // update time using global delta time variable
			AEVec2 zero{};
			AEVec2Zero(&zero);
			this->spell_array[i].spell_dragdrop->moveto(zero);
			if (animation_timer <= animation_time_total) {
				//Animation sequence starts here...
				//Card size expand sequence
				if (animation_timer <= animation_time_total * animation_scalein_ratio) {
					f64 current_time{animation_timer};
					f32 start_value = this->spell_array[i].spell_scale;
					f32 end_value = animation_size_max;
					f64 total_time = animation_time_total * animation_scalein_ratio;
					f64 t = current_time / total_time;
					this->spell_array[i].spell_scale = (f32) smooth_stepinout_lerp(start_value, end_value, t);
				}
				//Card size shrink sequence & fly
				else if (animation_timer < animation_time_total * animation_fly_ratio) {
					f64 current_time{ animation_timer };
					current_time -= animation_time_total * animation_scalein_ratio;
					f32 start_value_shrink = this->spell_array[i].spell_scale;
					f32 end_value_shrink = spell_scale_const;
					AEVec2 start_value = zero;
					AEVec2 end_value = midpoint(this->spell_array[i].spell_dragdrop->getcoord().s1, this->spell_array[i].spell_dragdrop->getcoord().s2);
					f64 total_time = animation_time_total * animation_fly_ratio;
					f64 t = current_time / total_time;
					animation_pos.x = (f32) smooth_stepinout_lerp(start_value.x, end_value.x, t);
					animation_pos.y = (f32)smooth_stepinout_lerp(start_value.y, end_value.y, t);
					this->spell_array[i].spell_scale = (f32)smooth_stepinout_lerp(start_value_shrink, end_value_shrink, t);
					this->spell_array[i].spell_dragdrop->moveto(animation_pos);
				}
				else {
					this->spell_array[i].spell_scale = spell_scale_const;
					animation_pos = zero;
					this->spell_array[i].spell_dragdrop->resetaabb();
					animation_timer = NULL;
					this->spell_array[i].animation = false;
				}
			}
		}
	}

}

f64 smooth_step(f32 edge0, f32 edge1, f32 x) {
	x =  AEClamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
	return x * x * (3 - 2 * x);
}

// interpolate between two values with smooth step lerp
f64 smooth_stepinout_lerp(f32 startValue, f32 endValue, f64 t) {

	f64 smoothT = smooth_step(0.0f, 1.0f, (f32) t); // smoothstep in
	f64 smoothInverseT = smooth_step(0.0f, 1.0f, (f32)(1.0f - t)); // smoothstep out
	return startValue * smoothInverseT + endValue * smoothT;
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
