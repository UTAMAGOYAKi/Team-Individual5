//---------------------------------------
//Set Spell Damage Values

//Base Damage
const int base_low = 2;
const int base_mid = 2;
const int base_high = 3;

//AOE Damage



#include "Spells.h"

//Number of spells that will be created
const int max_spells = 10;

//Declare textures for spells
AEGfxTexture* toxic_deluge{}, * inferno_blast{}, * umbral_tendrils{}, * maelstrom_surge{}, * venemous_bite{},
* shadow_cloak{}, * flame_burst{}, * rat_swarm{}, * bubonic_blaze{};

Spell* init_all_spells()
{
	AEVec2 cards;

	//Currently Textures are used as placeholder, ignore the meaning
	umbral_tendrils = AEGfxTextureLoad("Assets/spell_glyph.png");
	std::cout << "spell_g MemLoc: " << umbral_tendrils << std::endl;
	inferno_blast = AEGfxTextureLoad("Assets/not_fire.png");
	std::cout << "fire MemLoc: " << inferno_blast << std::endl;
	toxic_deluge = AEGfxTextureLoad("Assets/not_posion.png");
	std::cout << "poison MemLoc: " << toxic_deluge << std::endl;
	maelstrom_surge = AEGfxTextureLoad("Assets/not_burn.png");
	std::cout << "shame MemLoc: " << maelstrom_surge << std::endl;
	venemous_bite = AEGfxTextureLoad("Assets/venemous_bite.png");
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

	Spell* spellbook = new Spell[max_spells]{
		// Tier 3 spells
		Spell(TOXIC_DELUGE, 3, POISON, "Toxic Deluge",toxic_deluge,true, 2, 0, 1,0),
		Spell(INFERNO_BLAST, 3, FIRE, "Inferno Blast",maelstrom_surge,true, 2, 0, 1,0),
		Spell(UMBRAL_TENDRILS, 3, SHADOW, "Umbral Tendrils",inferno_blast,true, 2, 0, 1,0),
		Spell(MAELSTROM_SURGE, 3, WATER, "Maelstrom Surge",umbral_tendrils,true, 2, 0, 1,0),
		// Tier 2 spells
		Spell(VENOMOUS_BITE, 2, POISON, "Venomous Bite",venemous_bite,false, 3, 1, 5,2),
		Spell(SHADOW_CLOAK, 2, SHADOW, "Shadow Cloak",shadow_cloak,false, 3, 1, 5,0),
		Spell(FLAME_BURST, 2, FIRE, "Flame Burst",flame_burst,false, 3, 1, 5,0),
		// Tier 1 spells
		Spell(RAT_SWARM, 1, SHADOW, "Rat Swarm",rat_swarm,false, 5, 1, 5,1),
		Spell(BUBONIC_BLAZE, 1, FIRE, "Bubonic Blaze",bubonic_blaze,false, 5, 1, 5,5),
		// Invalid Spell
		Spell(INVALID_SPELL, 0, INVALID_ELEMENT, "",nullptr,false, 0, 0, 0,0),
	};

	AEVec2Zero(&cards);
	for (int i = 0; i <= max_spells - 1; i++) {
		//Set >tier 3 midpoint coords to 0
		if (spellbook[i].tier < 3) {
			spellbook[i].spell_dragdrop->moveto(cards);
			spellbook[i].spell_dragdrop->changeref(spellbook[i].id);
		}
	}
	return spellbook;
}

//destructor for the coordinates
Spell::~Spell()
{
	delete spell_dragdrop;
}

//Function that will set coords to a spell when called
void Spell::init_spells_draw(Spell& spell, AEVec2 coords)
{
	//Set spells boundingbox
	spell.spell_dragdrop->changeaabb(spell.card_width, spell.card_height);
	//Move spells to coords be drawn
	spell.spell_dragdrop->moveto(coords);
}


// Returns true if spell can be unlocked
bool combine_spells(Spell* spellbook, int id1, int id2) {
	if (spellbook[id1].tier == 3 && spellbook[id2].tier == 3) {
		// combine tier 3 spells
		if (spellbook[id1].element == FIRE && spellbook[id2].element == SHADOW ||
			spellbook[id2].element == FIRE && spellbook[id1].element == SHADOW) {
			// combine inferno blast and umbral tendrils to create flame burst
			spellbook[FLAME_BURST].unlocked = true;
			return true;
		}
		else if (spellbook[id1].element == POISON && spellbook[id2].element == SHADOW ||
			spellbook[id2].element == POISON && spellbook[id1].element == SHADOW) {
			// combine toxic deluge and umbral tendrils to create venomous bite
			spellbook[VENOMOUS_BITE].unlocked = true;
			return true;
		}
		else if (spellbook[id1].element == WATER && spellbook[id2].element == SHADOW ||
			spellbook[id2].element == WATER && spellbook[id1].element == SHADOW) {
			// combine maelstrom surge and umbral tendrils to create shadow cloak
			spellbook[SHADOW_CLOAK].unlocked = true;;
			return true;

		}
		else {
			// invalid combination
			return false;
		}
	}
	else if (spellbook[id1].tier == 2 && spellbook[id2].tier == 2) {
		// combine tier 2 spells
		if (spellbook[id1].element == POISON && spellbook[id2].element == SHADOW ||
			spellbook[id2].element == POISON && spellbook[id1].element == SHADOW) {
			// combine shadow cloak and venemous bite to create rat swarm
			spellbook[RAT_SWARM].unlocked = true;;
			return true;
		}
		if (spellbook[id1].element == FIRE && spellbook[id2].element == POISON ||
			spellbook[id2].element == FIRE && spellbook[id1].element == POISON) {
			// combine flame burst and venemous bite to create bubonic blaze
			spellbook[BUBONIC_BLAZE].unlocked = true;
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


// Called when level ends etc.
void unload_spells(Spell* spellbook) {
	AEGfxTextureUnload(umbral_tendrils);
	AEGfxTextureUnload(inferno_blast);
	AEGfxTextureUnload(toxic_deluge);
	AEGfxTextureUnload(maelstrom_surge);
	AEGfxTextureUnload(venemous_bite);
	AEGfxTextureUnload(shadow_cloak);
	AEGfxTextureUnload(flame_burst);
	AEGfxTextureUnload(rat_swarm);
	AEGfxTextureUnload(bubonic_blaze);
	delete[] spellbook;
}

//Returns state of the crafting table
// State 1: When only 1 spell is input
// State 2: When 2 spells has been input but invalid combo
// State 3: When 2 spells has been input and spell is unloked
int craftingtable::crafting_table_update(Spell* spellbook, int spell_id)
{
	spellbook[spell_id].spell_dragdrop->mousechange(false);
	spellbook[spell_id].spell_dragdrop->moveto(this->table_dragdrop.getcoord());
	if (this->spell1_id == INVALID_SPELL) {
		this->spell1_id = spell_id;
		return 1;
	}
	else if (this->spell1_id != INVALID_SPELL && this->spell2_id == INVALID_SPELL) {
		this->spell2_id = spell_id;
		if (combine_spells(spellbook, this->spell1_id, this->spell2_id) == true) {
			spellbook[this->spell1_id].spell_dragdrop->resetaabb();
			spellbook[this->spell2_id].spell_dragdrop->resetaabb();
			this->spell1_id = INVALID_SPELL;
			this->spell2_id = INVALID_SPELL;
			return 2;
		}
		else {
			spellbook[this->spell1_id].spell_dragdrop->resetaabb();
			spellbook[this->spell2_id].spell_dragdrop->resetaabb();
			this->spell1_id = INVALID_SPELL;
			this->spell2_id = INVALID_SPELL;
			return 3;
		}
	}
	//spellbook[table.spell1_id].spell_dragdrop->resetaabb();
	//spellbook[table.spell2_id].spell_dragdrop->resetaabb();
	//table.spell1_id = INVALID_SPELL;
	//table.spell2_id = INVALID_SPELL;
	return 2;
}

dragdrop* craftingtable::get_dragdrop()
{
	return &(this->table_dragdrop);
}

void draw_all_spells(Spell* spellbook)
{
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
