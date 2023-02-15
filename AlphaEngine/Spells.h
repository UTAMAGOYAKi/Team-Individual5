#pragma once
#include "Elements.h"
#include <string>

enum Spells {
    // Tier 3
    TOXIC_DELUGE,
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



class Spell{
public:
    Spell(int id, int tier, int element, std::string spell_name, int base_damage, int AOE_damage, int lingeringDamage) :
    id(id), tier(tier),element(element),spell_name(spell_name), base_damage(base_damage), AOE_damage(AOE_damage), lingeringDamage(lingeringDamage){};
    // Tags
    int id = INVALID_SPELL;
    int tier = 0;
    int element = INVALID_ELEMENT;
    std::string spell_name = "";
    //Damage
    int base_damage = 0;
    int AOE_damage = 0;
    int lingeringDamage = 0;
};

