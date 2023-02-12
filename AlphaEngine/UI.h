



#ifndef UI_h
#define UI_h
#include "Buttons.h"
#include "AEEngine.h"
#include "EnemyObject.h"

struct button
{
	dragdrop* box;
	int ref;
	AEGfxTexture* mesh;
};

 


void enemy_info(enemy ref);

void player_hp_bar(int hp);

void name_bar(int hp, coord place);

void name_bar(int hp, aabb place);

//void status_effect_ui(enemy ?);

void button_draw();









#endif // !1



