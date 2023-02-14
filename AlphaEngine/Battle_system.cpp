
#include "Battle_system.h"
AEMtx33 scale_battle = { 0 };
AEMtx33 rotate_battle = { 0 };
AEMtx33 translate_battle = { 0 };
AEMtx33 transform_battle = { 0 };

aabb* Battle_position_create_chara()
{
	//hard coded for now, due to testing and time 

	aabb* chara_pos{ new aabb };

	chara_pos->tr.x = -150.0;
	chara_pos->tr.y = 25.0;
	chara_pos->s1 = chara_pos->tr;

	chara_pos->bl.x = -250.0;
	chara_pos->bl.y = 15.0;
	chara_pos->s2 = chara_pos->bl;

	chara_pos->mid = midpoint(*chara_pos);

	return chara_pos;
}

aabb* Battle_position_create_enemy_1()
{
	//hard coded for now, due to testing and time 

	aabb* chara_pos{ new aabb };

	chara_pos->tr.x = 150.0;
	chara_pos->tr.y = 25.0;
	chara_pos->s1 = chara_pos->tr;

	chara_pos->bl.x = 50.0;
	chara_pos->bl.y = 15.0;
	chara_pos->s2 = chara_pos->bl;

	chara_pos->mid = midpoint(*chara_pos);

	return chara_pos;
}

aabb* Battle_position_create_enemy_2()
{
	//hard coded for now, due to testing and time 

	aabb* chara_pos{ new aabb };

	chara_pos->tr.x = 300.0;
	chara_pos->tr.y = 25.0;
	chara_pos->s1 = chara_pos->tr;

	chara_pos->bl.x = 200.0;
	chara_pos->bl.y = 15.0;
	chara_pos->s2 = chara_pos->bl;

	chara_pos->mid = midpoint(*chara_pos);

	return chara_pos;
}


void Battle_posistion_draw(aabb* pos, AEGfxVertexList* mesh) // for testing/knowing where it will be
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	AEMtx33Trans(&translate_battle, pos->mid.x, pos->mid.y);
	AEMtx33Rot(&rotate_battle, PI);
	AEMtx33Scale(&scale_battle, -20.f, 20.f);
	AEMtx33Concat(&transform_battle, &rotate_battle, &scale_battle);
	AEMtx33Concat(&transform_battle, &translate_battle, &transform_battle);
	AEGfxSetTransform(transform_battle.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}
