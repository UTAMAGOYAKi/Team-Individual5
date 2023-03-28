#include "Main.h"
#include "UI.h"

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

const float spell_menu_height = 164.0f;
const float spell_cap_width = 128.0f;
const float spell_pipe_overlap = 10;



AEMtx33 scale = { 0 };
AEMtx33 rotate = { 0 };
AEMtx33 translate = { 0 };
AEMtx33 transform = { 0 };

float rotation_about_time{};




void name_bar(std::string name, aabb place, s8 font)
{
	//remeber to check for centering offset %
}


void enemy_info(Enemy ref, s8 font, AEGfxVertexList* mesh)
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


void name_bar(std::string name, AEVec2 place, s8 font)
{
	AEGfxPrint(font, (s8*)name.c_str(), place.x / 640, (place.y / 360) - .35f, 1.0f, 1.0f, 1.0f, 1.0f);
	//remeber to check for centering offset %
}

void draw_crafting_table(AEGfxVertexList* mesh, craftingtable& crafting_table,particle_manager& particle_manager, particle (*callback)(AEVec2 pos), AEGfxTexture* table)
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
}

void draw_base_spell_slots(AEGfxVertexList* mesh, AEGfxTexture* base_spell, AEGfxTexture* base_spell_cap)
{

	//Draw Cap
	AEGfxTextureSet(base_spell_cap, (f32) - AEGetWindowWidth() / 2, (f32) AEGetWindowHeight() / 2);
	AEMtx33Trans(&translate, (f32)(AEGetWindowWidth() / 2) - (spell_cap_width/ 2), (f32)(-AEGetWindowHeight() / 2) + (spell_menu_height / 2));
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

void sub_menu_draw(AEGfxTexture* sub_menu, spell_book& spells, AEGfxVertexList* mesh, s8 font)
{
	// to ensure the sub_menu is on left 
	float tmpy = (float)AEGetWindowHeight();


	std::string sub_words[]{ "Known spell lists" };
	std::string tier_2[]{ "Tier 2:" };
	std::string tier_1[]{ "Tier 1:" };

	AEGfxTextureSet(sub_menu, 0, 0);
	AEMtx33Trans(&translate, -440, 100);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, 600, 500);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	AEGfxPrint(font, (s8*)sub_words[0].c_str(), -0.8f, 0.8f, 1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxPrint(font, (s8*)tier_2[0].c_str(), -0.8f, 0.70f, 1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxPrint(font, (s8*)tier_1[0].c_str(), -0.8f, 0.20f, 1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < max_spells - 1; i++)
	{
		if (spells.spell_array[i].unlocked == true && spells.spell_array[i].tier > tier3_last)
		{
			AEGfxTextureSet(spells.spell_array[i].texture, 0, 0);
			AEMtx33Trans(&translate, (f32)-590, (f32)300 - i * 50);
			AEMtx33Rot(&rotate, 0);
			AEMtx33Scale(&scale, 50, 50);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
			AEGfxPrint(font, (s8*)"=", ((-540.0f / 640.0f) * 1.0f), (((300 - i * 50) / 360.0f) * 1.0f - 0.025f), 1, 1.0f, 1.0f, 1.0f);
		}
	}
}

void level_transition(level_enum const& num) {
	/*const char* transition_text[] = { {"L"}, {"E"}, {"V"}, {"E"}, {"L"}, {":"} };
	const char* level_text = (num == level_1) ? "1" : (num == level_2) ? "2" : (num == level_3) ? "3" : "";
	for (int i{}; i < ARRAYSIZE(transition_text); ++i)
	{
		f32 middle = -(((float)strlen(transition_text[i]) / 2) / (AEGetWindowWidth() / FONT_SIZE));
		f32 textY = (float)((0 - i * linespace + scroll_time_current) / ((f32)AEGetWindowHeight() / 2));
		AEGfxPrint(font, (s8*)Credits[i], middle, textY, 1, 1, 1, 1);
	}*/
}
