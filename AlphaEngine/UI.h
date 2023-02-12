



#ifndef UI_h
#define UI_h
#include "Buttons.h"
#include "AEEngine.h"
#include "EnemyObject.h"
#include <string>
#include "Spells.h"


 


void enemy_info(enemy ref);

void player_hp_bar(int hp, aabb play_pos);

void name_bar(std::string name, coord place);
void name_bar(std::string name, aabb place);

//void name_bar(int hp, aabb place);

//void status_effect_ui(enemy ?);

// How do we plan to assign textures to buttons
//void button_draw();

void pause_menu_draw(AEGfxTexture* menu, AEGfxTexture* buttons, AEGfxVertexList* menu_mesh, AEGfxVertexList* button_mesh);

void sub_menu_draw(AEGfxTexture* sub_menu, AEGfxTexture* spells[], int known_spells);






#endif //UI_h



