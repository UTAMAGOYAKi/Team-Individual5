#include "Spells.h"

//Number of spells that will be created
const int max_spells = 10;

//Textures for spells
AEGfxTexture* toxic_deluge{}, * inferno_blast{}, * umbral_tendrils{}, * maelstrom_surge{};

Spell* init_allspells()
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


	std::cout << "Creating All " << max_spells << " Spells" << std::endl;
	Spell* spellbook = new Spell[max_spells]{
		// Tier 3 spells
		Spell(TOXIC_DELUGE, 3, POISON, "Toxic Deluge",toxic_deluge,false, 2, 0, 1),
		Spell(INFERNO_BLAST, 3, FIRE, "Inferno Blast",maelstrom_surge,true, 2, 0, 1),
		Spell(UMBRAL_TENDRILS, 3, SHADOW, "Umbral Tendrils",inferno_blast,false, 2, 0, 1),
		Spell(MAELSTROM_SURGE, 3, WATER, "Maelstrom Surge",umbral_tendrils,true, 2, 0, 1),
		// Tier 2 spells
		Spell(VENOMOUS_BITE, 2, POISON, "Venomous Bite",umbral_tendrils,false, 5, 1, 5),
		Spell(SHADOW_CLOAK, 2, SHADOW, "Shadow Cloak",umbral_tendrils,false, 5, 1, 5),
		Spell(FLAME_BURST, 2, FIRE, "Flame Burst",umbral_tendrils,true, 5, 1, 5),
		// Tier 1 spells
		Spell(RAT_SWARM, 1, SHADOW, "Rat Swarm",umbral_tendrils,false, 5, 1, 5),
		Spell(BUBONIC_BLAZE, 1, FIRE, "Bubonic Blaze",umbral_tendrils,false, 5, 1, 5),
		// Invalid Spell
		Spell(INVALID_SPELL, 0, INVALID_ELEMENT, "",umbral_tendrils,false, 0, 0, 0),
	};

	AEVec2Zero(&cards);
	for (int i = 0; i <= max_spells -1; i++) {
		//Set all midpoint coords to 0
		spellbook[i].spell_dragdrop->moveto(cards);
		//Set all spell boundingboxes
		spellbook[i].spell_dragdrop->changeaabb(spellbook[i].card_width, spellbook[i].card_height);
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
	spell.spell_dragdrop->moveto(coords);
}


// Returns true if spell can be unlocked (Not Implemented)
bool combineSpells(Spell* spellbook, int id1, int id2) {
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
	AEGfxTextureUnload(toxic_deluge);
	AEGfxTextureUnload(inferno_blast);
	AEGfxTextureUnload(umbral_tendrils);
	AEGfxTextureUnload(maelstrom_surge);
	delete[] spellbook;
}