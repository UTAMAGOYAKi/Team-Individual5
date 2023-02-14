#include "UI.h"



/*---------------------------------*/
//	Defines
//  All values tenative to changes
/*---------------------------------*/

const float hp_bar_height	= 2.0f;
const float hp_bar_offset	= 5.0f;
const float name_offset		= 2.0f;

const float hp_bar_player_width = 10.0f;
const float hp_bar_enemy_width = 10.0f;
const float hp_bar_boss_width = 20.0f;


AEMtx33 scale = { 0 };
AEMtx33 rotate = { 0 };
AEMtx33 translate = { 0 };
AEMtx33 transform = { 0 };

void enemy_info(enemy ref, s8 font)
{
	std::string tmp{ ref.name };

	//AEGfxPrint(font, (s8*)tmp.c_str(), ref.pos_x, ref.pos_y+name_offset, 0.0f, 0.0f, 0.0f, 0.0f);
	tmp.clear();
	tmp = std::to_string(ref.hp);
	//The rest requires referencing value to do a hp bar size
	//Request for enemy struct to carry Max_hp of enemy at creation as well


}

void player_hp_bar(int hp, aabb play_pos)
{
	//format for player?
}


void name_bar(std::string name, coord place,s8 font)
{
	AEGfxPrint(font, (s8*)name.c_str(), place.x, place.y + name_offset, 0.0f, 0.0f, 0.0f, 0.0f);
	//remeber to check for centering offset %
}

void name_bar(std::string name, aabb place, s8 font)
{
	AEGfxPrint(font, (s8*)name.c_str(), place.mid.x, place.mid.y, 0.0f, 0.0f, 0.0f, 0.0f);
	//remeber to check for centering offset %
}



void pause_menu_draw(AEGfxTexture* menu, AEGfxTexture* buttons, AEGfxVertexList* mesh, s8 font)
{
	//AEGfxGetWindowHeight(); doess not work, remember to bring up for the documentation
	float tmpx = AEGetWindowWidth(); // to ensure the pause menu is centred 
	float tmpy = AEGetWindowHeight();

	std::string menu_words[]{ "Resume","Options","Exit" };

	AEGfxTextureSet(menu, 0, 0);
	AEMtx33Trans(&transform, tmpx, tmpy);
	AEMtx33Rot(&rotate, PI);
	AEMtx33Scale(&scale, 1.0f, 1.0f);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	tmpy = AEGfxGetWinMaxY();

	for(int i =0; i < 3;i++)	//Resume, Options, Exit
	{
		AEGfxTextureSet(buttons, 0, 0);
		AEMtx33Trans(&transform, tmpx, tmpy - (150.f*(float)i));
		AEMtx33Rot(&rotate, PI);
		AEMtx33Scale(&scale, 1.0f, 1.0f);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

		AEGfxPrint(font, (s8*)menu_words[i].c_str(), tmpx, tmpy - (150.f * (float)i), 0.0f, 0.0f, 0.0f, 0.0f);

	}
}



void sub_menu_draw(AEGfxTexture* sub_menu, AEGfxTexture* spells[], int num_known,int known_spells[], AEGfxVertexList* mesh, s8 font)
{
	// to ensure the sub_menu is on left 
	float tmpy = AEGetWindowHeight();

	std::string sub_words[]{ "Known spell lists"};

	AEGfxTextureSet(sub_menu, 0, 0);
	AEMtx33Trans(&transform, 0.0f, tmpy);
	AEMtx33Rot(&rotate, PI);
	AEMtx33Scale(&scale, 1.0f, 1.0f);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	AEGfxPrint(font, (s8*)sub_words[0].c_str(), 0, tmpy - (150.f), 0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < num_known; i++)
	{
		//switch (known_spells[i])
		//{
		//case STEAM_TORNADO://or whatever spell format used

		//break;

		//}

		//using combination reference
		// draw related spell


	}


}





