#include "UI.h"



/*---------------------*/
//	Defines
/*---------------------*/

const float hp_bar_height = 2.0f;
const float hp_bar_player_width = 10.0f;
const float hp_bar_enemy_width = 10.0f;
const float hp_bar_boss_width = 20.0f;

extern s8 font;	//to be changed in the future? Dependent on how it font will be connected

void enemy_info(enemy ref)
{
	s8* text;


	AEGfxPrint(font, text	,ref.pos_x,ref.pos_y	,0.0f	,0.0f,0.0f,0.0f);

}
