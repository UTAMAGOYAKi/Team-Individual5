/******************************************************************************/
/*!
\file		UI.h
\author 	Liang HongJie(20%),
\par    	email: l.hongjie\@digipen.edu,
\brief		Some UI functions declared here as well as 

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

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

void draw_crafting_table( AEGfxVertexList* mesh, craftingtable& crafting_table, particle_manager& particle_manager, particle(*callback)(AEVec2 pos), AEGfxTexture* table = nullptr);

void draw_base_spell_slots(AEGfxVertexList* mesh, AEGfxTexture * base_spell, AEGfxTexture * base_spell_cap);

void draw_unlocked_spell_slots(AEGfxVertexList* mesh, spell_book & spellbook, AEGfxTexture* unlocked_spell = nullptr);

void level_transition(level_enum const& num, double const &time, std::string &tmp, bool &transition);

void text_buffer(std::string const& input_string, std::string& output_string, double time, int buffer_speed = 5);

extern float rotation_about_time;

#endif //UI_h



