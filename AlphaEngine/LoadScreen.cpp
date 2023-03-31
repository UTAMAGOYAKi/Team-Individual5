/******************************************************************************/
/*!
\file		LoadScreen.cpp
\author 	Liang HongJie
\par    	email: l.hongjie\@digipen.edu
\brief		Function definition for LoadScreen gamestate. (Digipen Logo)

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Main.h"

//Defines
AEGfxVertexList* pMesh_Loadscreen;
AEGfxTexture *load_screen;

float load_screen_time{};
const float load_screen_timer{ 3 };

/*
	Load function of loadscreen
*/
void LoadScreenLoad() {
	pMesh_Loadscreen = 0;
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f);
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f);
	pMesh_Loadscreen = AEGfxMeshEnd();

	load_screen = AEGfxTextureLoad("Assets/digilogo.png");
}

/*
	Init function of loadscreen
*/
void LoadScreenInit() {
	load_screen_time = load_screen_timer;
	click_offset = 0.1;
}

/*
	Update function of loadscreen
*/
void LoadScreenUpdate() {
	if (load_screen_time > 0) {
		load_screen_time -= (f32)g_dt;
	}
	if (load_screen_time <= 0 || AEInputCheckTriggered(AEVK_LBUTTON) && click_offset <= 0) {
		gGameStateNext = GS_MENU;
	}
	click_offset -= g_dt;
}

/*
	Draw function of loadscreen
*/
void LoadScreenDraw() {
	AEGfxSetBackgroundColor(.0f, .0f, .0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);


	if (load_screen_time >= (load_screen_timer / 2)) {
		AEGfxSetTransparency((load_screen_timer - load_screen_time) / (load_screen_timer / 2));
	}
	else {
		AEGfxSetTransparency(load_screen_time);
	}

	AEMtx33 scale{ 0 };
	AEMtx33 rotate{ 0 };
	AEMtx33 translate{ 0 };
	AEMtx33 transform{ 0 };

	AEGfxTextureSet(load_screen, 0, 0);
	AEMtx33Trans(&translate, 0, 0);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, 915, 287);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh_Loadscreen, AE_GFX_MDM_TRIANGLES);
}

/*
	Free function of loadscreen
*/
void LoadScreenFree() {}

/*
	Unload function of loadscreen
*/
void LoadScreenUnload() {
	AEGfxMeshFree(pMesh_Loadscreen);
	AEGfxTextureUnload(load_screen);
}
