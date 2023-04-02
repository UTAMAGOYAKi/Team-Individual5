/******************************************************************************/
/*!
\file		UI.h
\author 	Liang HongJie(20%), Low Ee Loong (40%), Daniel Tee (40%)
\par    	email: l.hongjie\@digipen.edu, eeloong.l\@digipen.edu, m.tee\@digipen.edu
\brief		Some UI functions declared here.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef UI_h
#define UI_h


extern float rotation_about_time;


//Known Spell List Variables
/******************************************************************************/
//Textures for spell icons (Used in known spells)
extern AEGfxTexture* toxic_deluge_icon, * inferno_blast_icon, * umbral_tendrils_icon, * maelstrom_surge_icon, * venemous_bite_icon,
* shadow_cloak_icon, * flame_burst_icon, * rat_swarm_icon, * bubonic_blaze_icon;
//Know spells width & height 
const float known_spell_height = 50.f;
const float known_spell_ybuffer = 30.f;
//Position of known spell menu headers
const float known_spell_x = -0.9f;
const float known_spell_title_y = 0.8f;
const float known_spell_two_y = 0.7f;
const float known_spell_one_y = 0.1f;
const float known_spell_spacing = 30.f;


/******************************************************************************/

//Element Icons
extern AEGfxTexture* fire_icon, * water_icon, * poison_icon, * shadow_icon;

void player_hp_bar(player ref, AEVec2 pos, AEGfxVertexList* mesh);

void name_bar(std::string name, AEVec2 place);

//void name_bar(std::string name, aabb place);

void enemy_info(Enemy enemy, AEGfxVertexList* mesh);

void sub_menu_draw(AEGfxTexture* sub_menu, spell_book& spells, AEGfxVertexList* mesh);

void draw_crafting_table(AEGfxVertexList* mesh, craftingtable& crafting_table, particle_manager& particle_manager, particle(*callback)(AEVec2 pos), AEGfxTexture* table = nullptr);

void draw_base_spell_slots(AEGfxVertexList* mesh, AEGfxTexture* base_spell, AEGfxTexture* base_spell_cap);

void draw_unlocked_spell_slots(AEGfxVertexList* mesh, spell_book& spellbook, AEGfxTexture* unlocked_spell = nullptr);

void draw_spellbook(AEGfxVertexList* mesh, AEGfxTexture* texture, AEVec2 trans, AEVec2 scal);

void level_transition(level_enum const& num, double const &time, std::string &tmp, bool &transition);

void text_buffer(std::string const& input_string, std::string& output_string, double time, int buffer_speed = 5);

void draw_combination(AEGfxTexture* equals, AEGfxTexture* lhs, AEGfxTexture* rhs, AEVec2& coords, AEGfxVertexList* mesh);


#endif //UI_h



