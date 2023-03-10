#include "Spells.h"

//---------------------------------------
//Set Spell Damage Values

//Base Damage
const int base_low = 2;
const int base_mid = 3;
const int base_high = 5;

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




//Declare textures for spells
AEGfxTexture* toxic_deluge{}, * inferno_blast{}, * umbral_tendrils{}, * maelstrom_surge{}, * venemous_bite{},
* shadow_cloak{}, * flame_burst{}, * rat_swarm{}, * bubonic_blaze{};

spell_book init_all_spells()
{
	AEVec2 cards;
	spell_book x;

	//Currently Textures are used as placeholder, ignore the meaning
	umbral_tendrils = AEGfxTextureLoad("Assets/Card-Sprite-umbral.png");
	std::cout << "spell_g MemLoc: " << umbral_tendrils << std::endl;
	inferno_blast = AEGfxTextureLoad("Assets/Card-Sprite-Inferno-Blast.png");
	std::cout << "fire MemLoc: " << inferno_blast << std::endl;
	toxic_deluge = AEGfxTextureLoad("Assets/not_posion.png");
	std::cout << "poison MemLoc: " << toxic_deluge << std::endl;
	maelstrom_surge = AEGfxTextureLoad("Assets/Card-Sprite-Maelstrom.png");
	std::cout << "shame MemLoc: " << maelstrom_surge << std::endl;
	venemous_bite = AEGfxTextureLoad("Assets/Card-Sprite-Venemous.png");
	std::cout << "venemous_bite MemLoc: " << venemous_bite << std::endl;
	shadow_cloak = AEGfxTextureLoad("Assets/shadow_cloak.png");
	std::cout << "shadow_cloak MemLoc: " << shadow_cloak << std::endl;
	flame_burst = AEGfxTextureLoad("Assets/flame_burst.png");
	std::cout << "flame_burst MemLoc: " << flame_burst << std::endl;
	rat_swarm = AEGfxTextureLoad("Assets/rat_swarm.png");
	std::cout << "rat_swarm MemLoc: " << rat_swarm << std::endl;
	bubonic_blaze = AEGfxTextureLoad("Assets/bubonic_blaze.png");
	std::cout << "bubonic_blaze MemLoc: " << bubonic_blaze << std::endl;
	std::cout << "Creating All " << max_spells << " Spells" << std::endl;

	// +1 due to invalid spell
	Spell* spellbook = new Spell[max_spells + 1]{
		// Tier 3 spells
		Spell(spells::TOXIC_DELUGE, tier3_last, POISON, "Toxic Deluge",toxic_deluge,true, base_low, NULL, lingering_low,NULL),
		Spell(spells::INFERNO_BLAST,tier3_last, FIRE, "Inferno Blast",inferno_blast,true, base_low, NULL, lingering_low,NULL),
		Spell(spells::UMBRAL_TENDRILS, tier3_last, SHADOW, "Umbral Tendrils",umbral_tendrils,true, base_low, NULL, lingering_low,NULL),
		Spell(spells::MAELSTROM_SURGE, tier3_last, WATER, "Maelstrom Surge",maelstrom_surge,true, base_low, NULL, lingering_low,NULL),
		// Tier 2 spells
		Spell(spells::VENOMOUS_BITE, tier2_last, POISON, "Venomous Bite",venemous_bite,false, base_mid, aoe_low, lingering_mid,lingering_rounds_mid),
		Spell(spells::SHADOW_CLOAK, tier2_last, SHADOW, "Shadow Cloak",shadow_cloak,false, base_mid, aoe_low, lingering_mid,NULL),
		Spell(spells::FLAME_BURST, tier2_last, FIRE, "Flame Burst",flame_burst,false, base_mid, aoe_low, lingering_mid,NULL),
		// Tier aoe_low spells
		Spell(spells::RAT_SWARM, tier1_last, SHADOW, "Rat Swarm",rat_swarm,false, base_high, aoe_low,lingering_high,lingering_rounds_mid),
		Spell(spells::BUBONIC_BLAZE,tier1_last, FIRE, "Bubonic Blaze",bubonic_blaze,false, base_high, aoe_low, lingering_high,lingering_rounds_mid),
		// Invalid Spell
		Spell(spells::INVALID_SPELL,spells::INVALID_SPELL , INVALID_ELEMENT, "",nullptr,false, NULL, NULL, NULL,NULL),
	};

	x.spell_array = spellbook;

	AEVec2Zero(&cards);
	for (int i = 0; i <= max_spells; i++) {
		//Set >tier 3 midpoint coords to 0
		if (x.spell_array[i].tier > tier3_last) {
			x.spell_array[i].spell_dragdrop->moveto(cards);
			x.spell_array[i].spell_dragdrop->changeref((int)x.spell_array[i].id);
		}
	}

	return x;
}

Spell::~Spell()
{
	delete spell_dragdrop;
}

void Spell::init_spells_draw(Spell& spell, AEVec2 coords)
{
	//Set spells boundingbox
	spell.spell_dragdrop->changeaabb(spell.card_width, spell.card_height);
	//Move spells to coords be drawn
	spell.spell_dragdrop->moveto(coords);
}

void Spell::reset_spell()
{
	unlocked = false;
	delete spell_dragdrop;
	spell_dragdrop = new dragdrop;
}


bool combine_spells(spell_book& spellbook, spells id1, spells id2) {
	assert(spellbook.array_size <= max_spells);
	assert(spellbook.array_size >= (size_t)first_spell);
	if (spellbook.spell_array[(int)id1].tier == tier3_last && spellbook.spell_array[(int)id2].tier == tier3_last) {
		// combine tier 3 spells
		if (spellbook.spell_array[(int)id1].element == FIRE && spellbook.spell_array[(int)id2].element == SHADOW ||
			spellbook.spell_array[(int)id2].element == FIRE && spellbook.spell_array[(int)id1].element == SHADOW) {
			// combine inferno blast and umbral tendrils to create flame burst
			spellbook.spell_array[(int)spells::FLAME_BURST].unlocked = true;
			return true;
		}
		else if (spellbook.spell_array[(int)id1].element == POISON && spellbook.spell_array[(int)id2].element == SHADOW ||
			spellbook.spell_array[(int)id2].element == POISON && spellbook.spell_array[(int)id1].element == SHADOW) {
			// combine toxic deluge and umbral tendrils to create venomous bite
			spellbook.spell_array[(int)spells::VENOMOUS_BITE].unlocked = true;
			return true;
		}
		else if (spellbook.spell_array[(int)id1].element == WATER && spellbook.spell_array[(int)id2].element == SHADOW ||
			spellbook.spell_array[(int)id2].element == WATER && spellbook.spell_array[(int)id1].element == SHADOW) {
			// combine maelstrom surge and umbral tendrils to create shadow cloak
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
			spellbook.spell_array[(int)spells::RAT_SWARM].unlocked = true;;
			return true;
		}
		if (spellbook.spell_array[(int)id1].element == FIRE && spellbook.spell_array[(int)id2].element == POISON ||
			spellbook.spell_array[(int)id2].element == FIRE && spellbook.spell_array[(int)id1].element == POISON) {
			// combine flame burst and venemous bite to create bubonic blaze
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


int craftingtable::crafting_table_update(spell_book& spellbook, spells spell_id)
{
	assert((spellbook.array_size <= max_spells) || (spellbook.array_size >= (size_t)first_spell));
	spellbook.spell_array[(int)spell_id].spell_dragdrop->mousechange(false);
	spellbook.spell_array[(int)spell_id].spell_dragdrop->moveto(this->table_dragdrop.getcoord());
	if (this->spell1_id == spells::INVALID_SPELL) {
		this->spell1_id = spell_id;
		return 1;
	}
	else if (this->spell1_id != spells::INVALID_SPELL && this->spell2_id == spells::INVALID_SPELL) {
		this->spell2_id = spell_id;
		if (combine_spells(spellbook, this->spell1_id, this->spell2_id) == true) {
			spellbook.spell_array[(int)this->spell1_id].spell_dragdrop->resetaabb();
			spellbook.spell_array[(int)this->spell2_id].spell_dragdrop->resetaabb();
			this->spell1_id = spells::INVALID_SPELL;
			this->spell2_id = spells::INVALID_SPELL;
			return 3;
		}
		else {
			spellbook.spell_array[(int)this->spell1_id].spell_dragdrop->resetaabb();
			spellbook.spell_array[(int)this->spell2_id].spell_dragdrop->resetaabb();
			this->spell1_id = spells::INVALID_SPELL;
			this->spell2_id = spells::INVALID_SPELL;
			return 2;
		}
	}
	return 2;
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

craftingtable::craftingtable()
{
	//Set Table aabb
	AEVec2 zero;
	AEVec2Zero(&zero);
	AEVec2Set(&zero, 1, 1);
	table_dragdrop.moveto(zero);
	table_dragdrop.changeaabb(table_width, table_height);
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

spell_book::spell_book(spell_book const& rhs)
{
	//std::copy(rhs.spell_array, rhs.spell_array + (rhs.array_size-1), this->spell_array);
	this->spell_array = rhs.spell_array;
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
