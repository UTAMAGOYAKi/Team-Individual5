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

//void name_bar(int hp, aabb place);

//void status_effect_ui(enemy ?);

// How do we plan to assign textures to buttons
//void button_draw();

//void pause_menu_draw(AEGfxTexture* menu, AEGfxTexture* buttons, AEGfxVertexList* mesh, s8 font);

void sub_menu_draw(AEGfxTexture* sub_menu, Spell spells[], AEGfxVertexList* mesh, s8 font);

void draw_crafting_table( AEGfxVertexList* mesh,AEGfxTexture* table = nullptr );


#endif //UI_h



