#include "Spells.h"
#include "UI.h"
//Declare textures for spells
AEGfxTexture* toxic_deluge{}, * inferno_blast{}, * umbral_tendrils{}, * maelstrom_surge{}, * venemous_bite{},
* shadow_cloak{}, * flame_burst{}, * rat_swarm{}, * bubonic_blaze{};

f64 timer{};

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


	// Set all spells coords

	//Starting coords for all spells
	//AEVec2Zero(&cards);


	x.spell_array = spellbook;

	return x;
}

Spell::~Spell()
{
	delete spell_dragdrop;
}

void init_spells_coords(spell_book& spellbook)
{
	assert(spellbook.array_size <= max_spells);
	assert(spellbook.array_size >= (size_t)first_spell);
	AEVec2 cards;
	AEVec2Set(&cards, (f32)-(AEGetWindowWidth() / 2) + 80, -((f32)-(AEGetWindowHeight() / 2) + 82));

	//All Tier 3 spells
	for (int i = (int)first_spell; i <= (int)tier3_last; ++i) {
		spellbook.spell_array[i].spell_dragdrop->moveto(cards);
		spellbook.spell_array[i].spell_dragdrop->set_origin();
		cards.x += card_width_const + spell_buffer;
	}
	cards.x += spell_tier_buffer;
	//All Tier 2 spells
	for (int i = (int)tier3_last + 1; i <= (int)tier2_last; ++i) {
		spellbook.spell_array[i].known_spell_coords.x = (AEGetWindowWidth() * known_spell_x) / 2;
		spellbook.spell_array[i].known_spell_coords.y = (AEGetWindowHeight() * known_spell_two_y) / 2 - known_spell_height - known_spell_ybuffer;

		spellbook.spell_array[i].spell_dragdrop->moveto(cards);
		spellbook.spell_array[i].spell_dragdrop->set_origin();
		cards.x += card_width_const + spell_buffer;
	}
	cards.x += spell_tier_buffer;
	//All Tier 1 spells
	for (int i = (int)tier2_last + 1; i <= (int)tier1_last; ++i) {
		spellbook.spell_array[i].known_spell_coords.x = AEGetWindowWidth() * known_spell_x / 2;
		spellbook.spell_array[i].known_spell_coords.y = (AEGetWindowHeight() * known_spell_one_y) / 2 - known_spell_height - known_spell_ybuffer;

		spellbook.spell_array[i].spell_dragdrop->moveto(cards);
		spellbook.spell_array[i].spell_dragdrop->set_origin();
		cards.x += card_width_const + spell_buffer;
	}

	for (int i = 0; i <= spellbook.array_size - 1; i++) {
		spellbook.spell_array[i].spell_dragdrop->changeaabb(card_width_const, card_height_const);
	}
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

bool combine_spells(spell_book& spellbook, spells id1, spells id2) {
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
			spellbook.spell_array[(int)spells::SHADOW_CLOAK].unlocked = true;
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


void unload_spells(spell_book& spellbook) {
	AEGfxTextureUnload(umbral_tendrils);
	AEGfxTextureUnload(inferno_blast);
	AEGfxTextureUnload(toxic_deluge);
	AEGfxTextureUnload(maelstrom_surge);
	AEGfxTextureUnload(venemous_bite);
	AEGfxTextureUnload(shadow_cloak);
	AEGfxTextureUnload(flame_burst);
	AEGfxTextureUnload(rat_swarm);
	AEGfxTextureUnload(bubonic_blaze);
	delete[] spellbook.spell_array;
}


void craftingtable::crafting_table_snap(spell_book& spellbook, spells spell_id)
{
	assert((spellbook.array_size <= max_spells) || (spellbook.array_size >= (size_t)first_spell));
	//Only run when crafting table is empty
	if (this->spell1_id == spells::INVALID_SPELL && two_spell_flag == false) {
		spellbook.spell_array[(int)spell_id].spell_dragdrop->mousechange(false);
		spellbook.spell_array[(int)spell_id].spell_dragdrop->moveto(this->table_dragdrop.getcoord());
		spellbook.spell_array[(int)spell_id].spell_dragdrop->move(crafting_table_buffer, 0);
		this->spell1_id = spell_id;
	}
	else if (this->spell1_id != spells::INVALID_SPELL && this->spell2_id == spells::INVALID_SPELL) {
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
			if (combine_spells(spellbook, this->spell1_id, this->spell2_id)) {
				spellbook.spell_array[(int)this->spell1_id].spell_dragdrop->resetaabb();
				spellbook.spell_array[(int)this->spell2_id].spell_dragdrop->resetaabb();
				if (spellbook.spell_array[(int)this->spell1_id].tier > tier3_last)
					spellbook.spell_array[(int)this->spell1_id].unlocked = false;
				if (spellbook.spell_array[(int)this->spell2_id].tier > tier3_last)
					spellbook.spell_array[(int)this->spell2_id].unlocked = false;
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

dragdrop* craftingtable::get_dragdrop()
{
	return &(this->table_dragdrop);
}

void draw_all_spells(spell_book& spellbook, AEGfxVertexList* pMesh)
{
	assert((spellbook.array_size <= max_spells) || (spellbook.array_size >= (size_t)first_spell));
	AEMtx33 scale{ };
	AEMtx33 rotate{  };
	AEMtx33 translate{  };
	AEMtx33 transform{  };
	for (int i = 0; i <= spellbook.array_size - 1; i++) {
		if (spellbook.spell_array[i].unlocked == true) {
			AEGfxTextureSet(spellbook.spell_array[i].texture, 0, 0);
			AEMtx33Trans(&translate, spellbook.spell_array[i].spell_dragdrop->getcoord().mid.x, -spellbook.spell_array[i].spell_dragdrop->getcoord().mid.y);
			AEMtx33Rot(&rotate, 0);
			AEMtx33Scale(&scale, spellbook.spell_array[i].card_width, spellbook.spell_array[i].card_height);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		}
	}
}

void draw_spell_combination(spell_book& spellbook, AEGfxVertexList* pMesh)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////for (int i = 0; i < max_spells - 1; i++)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	if (spells.spell_array[i].unlocked == true && spells.spell_array[i].tier > tier3_last)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		AEGfxTextureSet(spells.spell_array[i].texture, 0, 0);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		AEMtx33Trans(&translate, (f32)-590, (f32)300 - i * 50);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		AEMtx33Rot(&rotate, 0);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		AEMtx33Scale(&scale, 50, 50);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		AEMtx33Concat(&transform, &rotate, &scale);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		AEMtx33Concat(&transform, &translate, &transform);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		AEGfxSetTransform(transform.m);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		AEGfxpMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		AEGfxPrint(font, (s8*)"+", ((-540.0f / 640.0f) * 1.0f), (((300 - i * 50) / 360.0f) * 1.0f - 0.025f), 1, 1.0f, 1.0f, 1.0f);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////}
}

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
