/******************************************************************************/
/*!
\file		UI.cpp
\author 	Liang HongJie(20%),Low Ee Loong (20%)
\par    	email: l.hongjie\@digipen.edu, eeloong.l\@digipen.edu
\brief		Some UI functions defined here.
			

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Main.h"

/*---------------------------------*/
//	Defines
//  All values tenative to changes
/*---------------------------------*/
const float hp_bar_height = 10.0f;
const float hp_bar_offset = 5.0f;
const float name_offset = 100.0f;

const float hp_bar_player_width = 10.0f;
const float hp_bar_enemy_width = 10.0f;
const float hp_bar_boss_width = 20.0f;

//Menu that spells sit on
const float spell_menu_height = 164.0f;
const float spell_cap_width = 128.0f;
const float spell_pipe_overlap = 10;


//Known Spell List Variables
/******************************************************************************/

//Known spell lists menu consts
const float known_spell_menu_x = -440;
const float known_spell_menu_y = 100;
const float known_spell_menu_width = 400;
const float known_spell_menu_height = 500;
const float known_spell_text_scale = 1.0f;
const float known_spell_text_RGBwhite = 1.0f;
const float known_spell_printtext_y_offset = 10.0f;

//Dynamically printed when called
//Rhs Spell Icon Spacing
const float known_spell_rhs_spacing = known_spell_spacing * 2 + known_spell_height * 2;
const float known_spell_plus_spacing = known_spell_spacing * 4;
/******************************************************************************/

AEMtx33 scale = { 0 };
AEMtx33 rotate = { 0 };
AEMtx33 translate = { 0 };
AEMtx33 transform = { 0 };

float rotation_about_time{};




//void name_bar(std::string name, aabb place)
//{
//	//remeber to check for centering offset %
//}


void enemy_info(Enemy ref, AEGfxVertexList* mesh)
{
	std::string tmp{ ref.get_name() };

	tmp.clear();
	if (ref.get_hp() >= 0)
	{
		tmp = std::to_string(ref.get_hp());
	}
	else
	{
		tmp += "0";
	}
	tmp += "/";
	tmp += std::to_string(ref.get_max_hp());
	if (ref.get_hp() > 0)
	{
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetTintColor(1.0f, .0f, .0f, 1.0f);
		AEMtx33Trans(&translate, ref.get_pos().x - (hp_bar_enemy_width * (((float)ref.get_max_hp() - (float)ref.get_hp()) / (float)ref.get_max_hp()) * 10) / 2, ref.get_pos().y - name_offset);
		AEMtx33Rot(&rotate, 0);
		AEMtx33Scale(&scale, hp_bar_enemy_width * ((float)ref.get_hp() / (float)ref.get_max_hp()) * 10, hp_bar_height);

		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	}

	//The rest requires referencing value to do a hp bar size
	//Request for enemy struct to carry Max_hp of enemy at creation as well
	AEGfxPrint(font, (s8*)ref.get_name().c_str(), (ref.get_pos().x / 640) + 0.025f, ref.get_pos().y - 0.25f, .50f, 1.0f, 1.0f, 1.0f);

	AEGfxPrint(font, (s8*)tmp.c_str(), (ref.get_pos().x / 640) - .05f, ref.get_pos().y - .25f, 0.5, 1.0f, 1.0f, 1.0f);

}

void player_hp_bar(player ref, AEVec2 pos, AEGfxVertexList* mesh)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTintColor(1.0f, .0f, .0f, 1.0f);
	AEMtx33Trans(&translate, pos.x - (hp_bar_enemy_width * (((float)ref.max_hp - (float)ref.hp) / (float)ref.max_hp) * 10) / 2, pos.y - name_offset);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, hp_bar_enemy_width * ((float)ref.hp / (float)ref.max_hp) * 10, hp_bar_height);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
}


void name_bar(std::string name, AEVec2 place)
{
	AEGfxPrint(font, (s8*)name.c_str(), place.x / 640, (place.y / 360) - .35f, 1.0f, 1.0f, 1.0f, 1.0f);
	//remeber to check for centering offset %
}

void draw_crafting_table(AEGfxVertexList* mesh, craftingtable& crafting_table, particle_manager& particle_manager, particle(*callback)(AEVec2 pos), AEGfxTexture* table)
{
	rotation_about_time = (timer <= 0) ? 0 : rotation_about_time;


	AEVec2 table_coord = { crafting_table.get_dragdrop()->getcoord().mid.x, crafting_table.get_dragdrop()->getcoord().mid.y };
	// Creating particles
	if (timer != rotation_about_time)
		create_particle(particle_manager.particle_vector, particle_manager.max_capacity, table_coord, enemy_take_damage_particle);
	// Drawing textures
	AEGfxTextureSet(table, crafting_table.get_dragdrop()->getcoord().mid.x, crafting_table.get_dragdrop()->getcoord().mid.y);
	AEMtx33Trans(&translate, crafting_table.get_dragdrop()->getcoord().mid.x, crafting_table.get_dragdrop()->getcoord().mid.y);
	AEMtx33Rot(&rotate, rotation_about_time);
	AEMtx33Scale(&scale, table_width_const, table_height_const);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	UNREFERENCED_PARAMETER(callback);
}

void draw_base_spell_slots(AEGfxVertexList* mesh, AEGfxTexture* base_spell, AEGfxTexture* base_spell_cap)
{

	//Draw Cap
	AEGfxTextureSet(base_spell_cap, (f32)-AEGetWindowWidth() / 2, (f32)AEGetWindowHeight() / 2);
	AEMtx33Trans(&translate, (f32)(AEGetWindowWidth() / 2) - (spell_cap_width / 2), (f32)(-AEGetWindowHeight() / 2) + (spell_menu_height / 2));
	AEMtx33Rot(&rotate, NULL);
	AEMtx33Scale(&scale, spell_cap_width, spell_menu_height);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	//Draw Mid Pipe
	AEGfxTextureSet(base_spell, (f32)-AEGetWindowWidth() / 2, (f32)AEGetWindowHeight() / 2);
	AEMtx33Trans(&translate, -(spell_cap_width - spell_pipe_overlap), (-AEGetWindowHeight() / 2) + (spell_menu_height / 2));
	AEMtx33Rot(&rotate, NULL);
	AEMtx33Scale(&scale, (f32)AEGetWindowWidth(), spell_menu_height);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

}

void draw_unlocked_spell_slots(AEGfxVertexList* mesh, spell_book& spellbook, AEGfxTexture* unlocked_spell)
{
	assert((spellbook.array_size <= max_spells) || (spellbook.array_size >= (size_t)first_spell));
	for (int i = 0; i <= spellbook.array_size - 1; i++) {
		AEVec2 spell_mid = midpoint(spellbook.spell_array[i].spell_dragdrop->getcoord().s1, spellbook.spell_array[i].spell_dragdrop->getcoord().s2);
		AEGfxTextureSet(unlocked_spell, 0, 0);
		AEMtx33Trans(&translate, spell_mid.x, -spell_mid.y);
		AEMtx33Rot(&rotate, NULL);
		AEMtx33Scale(&scale, card_width_const + 20, card_height_const + 20);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	}
}

void draw_spellbook(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 trans, AEVec2 scal) {
	AEGfxTextureSet(texture, 0, 0);
	AEMtx33Trans(&translate, trans.x, -trans.y);
	AEMtx33Scale(&scale, scal.x, scal.y);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void sub_menu_draw(AEGfxTexture* sub_menu, spell_book& spells, AEGfxVertexList* mesh)
{
	// to ensure the sub_menu is on left 
	/*float tmpy = (float)AEGetWindowHeight();*/

	std::string sub_words[]{ "Known spell list" };
	std::string tier_2[]{ "Tier 2:" };
	std::string tier_1[]{ "Tier 1:" };

	AEGfxTextureSet(sub_menu, NULL, NULL);
	AEMtx33Trans(&translate, known_spell_menu_x ,known_spell_menu_y );
	AEMtx33Rot(&rotate, NULL);
	AEMtx33Scale(&scale, known_spell_menu_width, known_spell_menu_height);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	AEGfxPrint(font, (s8*)sub_words[0].c_str(), known_spell_x, known_spell_title_y, known_spell_text_scale, known_spell_text_RGBwhite, known_spell_text_RGBwhite, known_spell_text_RGBwhite);

	AEGfxPrint(font, (s8*)tier_2[0].c_str(), known_spell_x, known_spell_two_y, known_spell_text_scale, known_spell_text_RGBwhite, known_spell_text_RGBwhite, known_spell_text_RGBwhite);

	AEGfxPrint(font, (s8*)tier_1[0].c_str(), known_spell_x, known_spell_one_y, known_spell_text_scale, known_spell_text_RGBwhite, known_spell_text_RGBwhite, known_spell_text_RGBwhite);

	for (int i = 0; i < max_spells ; i++)
	{
		if (spells.spell_array[i].discovered == true && spells.spell_array[i].tier > tier3_last)
		{
			if (spells.spell_array[i].tier == tier2_last) {
				switch (spells.spell_array[i].element) {
				case POISON:
					draw_combination(venemous_bite_icon, umbral_tendrils_icon,toxic_deluge_icon,  spells.spell_array[i].known_spell_coords, mesh);
					break;
				case FIRE:
					draw_combination(flame_burst_icon, umbral_tendrils_icon,inferno_blast_icon, spells.spell_array[i].known_spell_coords, mesh);
					break;				
				case SHADOW:
					draw_combination(shadow_cloak_icon, umbral_tendrils_icon, maelstrom_surge_icon, spells.spell_array[i].known_spell_coords, mesh);
					break;
				}
			}
			if (spells.spell_array[i].tier == tier1_last) {
				switch (spells.spell_array[i].element) {
				case SHADOW:
					draw_combination(rat_swarm_icon, venemous_bite_icon, shadow_cloak_icon, spells.spell_array[i].known_spell_coords, mesh);
					break;
				case FIRE:
					draw_combination(bubonic_blaze_icon, flame_burst_icon, venemous_bite_icon, spells.spell_array[i].known_spell_coords, mesh);
					break;
				}
			}
		}
	}
}

/*
	\breif 
		function prints text while during transition
	\param num [in]
		value of level cleared
	\param time [in]
		time since transition started, time has to be positive and increasing.
	\param tmp [in,out]
		for this function, to input an empty string, transitioning text will be buffered onto this string before printing
	\param transition [in,out]
		function will change the state of transition after it's done.
*/
void level_transition(level_enum const& num, double const &time, std::string &tmp, bool &transition) {
	int i{ 0 };
	const int transition_speed = 5;
	std::string addtext{ "LEVEL: " };
	addtext += static_cast<char>(static_cast<int>(num) + '1');


	text_buffer(addtext, tmp, time);

	if (time > 0) {
		i = (int)(time * transition_speed);
	}

	if (i > addtext.size() && transition)
		transition = false;

	f32 middle = -(((float)strlen(tmp.c_str()) / 2) / (AEGetWindowWidth() / FONT_SIZE));
	f32 textY = 0;
	AEGfxPrint(font, (s8*)tmp.c_str(), middle, textY, 1, 1, 1, 1);

}

/*
	\brief
		function buffers input_string into output_string, it does not print stuff
	\param input_string
		read only string variable to buffer from
	\param output_string
		string variable to add onto
	\param time
		time provided by user strictly needs to start from 0, time provided needs to be always positive in value.
	\param buffer_speed
		speed at which the text buffers, default at 5.
*/
void text_buffer(std::string const& input_string, std::string& output_string, double time, int buffer_speed) {
	int i{ 0 };
	const int text_speed{ buffer_speed };
	if (time > 0) {
		i = (int)(time * text_speed);
	}

	if (i < input_string.size() && output_string[i] != input_string[i]) {
		output_string += input_string[i];
	}

	if (i > input_string.size()) {
		output_string += ' ';
	}
}


void draw_combination(AEGfxTexture* equals, AEGfxTexture* lhs, AEGfxTexture* rhs, AEVec2& coords, AEGfxVertexList* mesh)
{
	//Returned Spell Icon
	AEGfxTextureSet(equals, NULL, NULL);
	AEMtx33Trans(&translate, coords.x, coords.y);
	AEMtx33Rot(&rotate, NULL);
	AEMtx33Scale(&scale,known_spell_height, known_spell_height);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	//LHS Spell Icon
	AEGfxTextureSet(lhs, NULL, NULL);
	AEMtx33Trans(&translate, coords.x + known_spell_spacing + known_spell_height , coords.y);
	AEMtx33Rot(&rotate, NULL);
	AEMtx33Scale(&scale, known_spell_height, known_spell_height);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	
	//Rhs Spell Icon
	AEGfxTextureSet(rhs, NULL, NULL);
	AEMtx33Trans(&translate, coords.x + known_spell_rhs_spacing , coords.y);
	AEMtx33Rot(&rotate, NULL);
	AEMtx33Scale(&scale, known_spell_height, known_spell_height);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	//Text printing
	AEGfxPrint(font, (s8*)"=", ((coords.x + known_spell_spacing) *2/ AEGetWindowWidth()) , ((coords.y - known_spell_printtext_y_offset)*2 / AEGetWindowHeight()) , known_spell_text_scale, known_spell_text_RGBwhite, known_spell_text_RGBwhite, known_spell_text_RGBwhite);
	AEGfxPrint(font, (s8*)"+", ((coords.x + known_spell_plus_spacing) *2 / AEGetWindowWidth()), ((coords.y - known_spell_printtext_y_offset) * 2 / AEGetWindowHeight()), known_spell_text_scale, known_spell_text_RGBwhite, known_spell_text_RGBwhite, known_spell_text_RGBwhite);
}
