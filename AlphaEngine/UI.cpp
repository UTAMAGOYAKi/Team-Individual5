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

extern s8 font;	//to be changed in the future? Dependent on how it font will be connected

void enemy_info(enemy ref)
{
	std::string tmp{ ref.name };

	AEGfxPrint(font, (s8*)tmp.c_str(), ref.pos_x, ref.pos_y+name_offset, 0.0f, 0.0f, 0.0f, 0.0f);
	tmp.clear();
	tmp = std::to_string(ref.hp);
	//The rest requires referencing value to do a hp bar size
	//Request for enemy struct to carry Max_hp of enemy at creation as well


}

void player_hp_bar(int hp, aabb play_pos)
{
	//format for player?
}


void name_bar(std::string name, coord place)
{
	AEGfxPrint(font, (s8*)name.c_str(), place.x, place.y + name_offset, 0.0f, 0.0f, 0.0f, 0.0f);
	//remeber to check for centering offset %
}

void name_bar(std::string name, aabb place)
{
	AEGfxPrint(font, (s8*)name.c_str(), place.mid.x, place.mid.y, 0.0f, 0.0f, 0.0f, 0.0f);
	//remeber to check for centering offset %
}



void pause_menu_draw(AEGfxTexture* menu, AEGfxTexture* buttons)
{
	//AEGfxGetWindowHeight(); doess not work, remember to bring up for the documentation
	float tmpx = AEGetWindowWidth(); // to ensure the pause menu is centred 
	float tmpy = AEGetWindowHeight();


}
