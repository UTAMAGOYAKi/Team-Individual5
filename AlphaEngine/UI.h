#ifndef UI_h
#define UI_h
#include "Buttons.h"
#include "AEEngine.h"
#include "EnemyObject.h"
#include <string>
#include "Spells.h"






void player_hp_bar(player ref, AEVec2 pos, AEGfxVertexList* mesh);

void name_bar(std::string name, AEVec2 place, s8 font);
void name_bar(std::string name, aabb place, s8 font);

void enemy_info(Enemy enemy, s8 font, AEGfxVertexList* mesh);

void sub_menu_draw(AEGfxTexture* sub_menu, spell_book& spells, AEGfxVertexList* mesh, s8 font);

void draw_crafting_table( AEGfxVertexList* mesh, craftingtable& crafting_table, AEGfxTexture* table = nullptr );

void draw_base_spell_slots(AEGfxVertexList* mesh, AEGfxTexture * base_spell, AEGfxTexture * base_spell_cap);

void draw_unlocked_spell_slots(AEGfxVertexList* mesh, spell_book & spellbook, AEGfxTexture* unlocked_spell = nullptr);

#endif //UI_h



