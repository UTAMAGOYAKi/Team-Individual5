#include "Main.h"

/*---------------------------------*/
//	Defines
//  All values tenative to changes
/*---------------------------------*/

const float hp_bar_height	= 10.0f;
const float hp_bar_offset	= 5.0f;
const float name_offset		= 100.0f;

const float hp_bar_player_width = 10.0f;
const float hp_bar_enemy_width = 10.0f;
const float hp_bar_boss_width = 20.0f;


AEMtx33 scale = { 0 };
AEMtx33 rotate = { 0 };
AEMtx33 translate = { 0 };
AEMtx33 transform = { 0 };

//Crafting Table 


void name_bar(std::string name, aabb place, s8 font)
{
	//remeber to check for centering offset %
}


void enemy_info(Enemy ref, s8 font, AEGfxVertexList* mesh)
{
	std::string tmp{ ref.get_name()};

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
	if(ref.get_hp() >0)
	{
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetTintColor(1.0f, .0f, .0f, 1.0f);
		AEMtx33Trans(&translate, ref.get_pos().x - (hp_bar_enemy_width * (((float)ref.get_max_hp() - (float)ref.get_hp()) / (float)ref.get_max_hp()) * 10) / 2, ref.get_pos().y - name_offset);
		AEMtx33Rot(&rotate, PI);
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
	AEMtx33Trans(&translate,pos.x - (hp_bar_enemy_width * (((float)ref.max_hp - (float)ref.hp) / (float)ref.max_hp) * 10) / 2, pos.y - name_offset);
	AEMtx33Rot(&rotate, PI);
	AEMtx33Scale(&scale, hp_bar_enemy_width * ((float)ref.hp / (float)ref.max_hp) * 10, hp_bar_height);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
}


void name_bar(std::string name, AEVec2 place,s8 font)
{
	AEGfxPrint(font, (s8*)name.c_str(), place.x / 640, (place.y/360)-.35f, 1.0f, 1.0f, 1.0f, 1.0f);
	//remeber to check for centering offset %
}

void draw_crafting_table( AEGfxVertexList* mesh, craftingtable& crafting_table, AEGfxTexture* table = nullptr ) {
	// Drawing textures
	AEGfxTextureSet(table, crafting_table.get_dragdrop()->getcoord().mid.x, crafting_table.get_dragdrop()->getcoord().mid.y);
	AEMtx33Trans(&translate, crafting_table.get_dragdrop()->getcoord().mid.x, crafting_table.get_dragdrop()->getcoord().mid.y);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, table_width_const, table_height_const);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void sub_menu_draw(AEGfxTexture* sub_menu, spell_book& spells, AEGfxVertexList* mesh, s8 font)
{
	// to ensure the sub_menu is on left 
	float tmpy = (float)AEGetWindowHeight();


	std::string sub_words[]{ "Known spell lists" };
	AEGfxTextureSet(sub_menu, 0, 0);
	AEMtx33Trans(&translate, -440, 100);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, 600, 500);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	AEGfxPrint(font, (s8*)sub_words[0].c_str(), -0.8f, 0.8f, 1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < max_spells-1; i++) 
	{
		if (spells.spell_array[i].unlocked == true && spells.spell_array[i].tier > tier3_last)
		{
			AEGfxTextureSet(spells.spell_array[i].texture, 0, 0);
			AEMtx33Trans(&translate,(f32) - 590, (f32)300 - i * 50);
			AEMtx33Rot(&rotate, 0);
			AEMtx33Scale(&scale, 50, 50);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
			AEGfxPrint(font, (s8*)"=", ((-540.0f / 640.0f) * 1.0f), (((300 - i * 50) / 360.0f) * 1.0f-0.025f), 1, 1.0f, 1.0f, 1.0f);
		}
	}
}
