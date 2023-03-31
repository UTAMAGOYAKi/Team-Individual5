
#ifndef Battle_system_h
#define Battle_system_h
#include "Buttons.h"
#include <string>

aabb* Battle_position_create_chara();
aabb* Battle_position_create_enemy_1();
aabb* Battle_position_create_enemy_2();

void Battle_position_delete(aabb* pos);// not implemented yet

void Battle_posistion_draw(aabb* pos, AEGfxVertexList* mesh); // for testing/knowing where it will be



#endif // !Battle_h



