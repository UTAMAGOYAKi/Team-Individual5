/******************************************************************************/
/*!
\file		GameOver.cpp
\author 	Liang HongJie
\par    	email: l.hongjie\@digipen.edu
\brief		Function definition for GameOver gamestate.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "main.h"

//Define variable used in GameOver gamestate
AEGfxVertexList* pMesh_GameOver;
AEGfxTexture *Gameover_screen, *Victory_screen;

/*
	Load function of GameOver
*/
void GameOverLoad() {
	pMesh_GameOver = 0;
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f);
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f);
	pMesh_GameOver = AEGfxMeshEnd();

	Gameover_screen = AEGfxTextureLoad("Assets/GameOver_Text.png");
	Victory_screen = AEGfxTextureLoad("Assets/Victory_Text.png");
}


/*
	Init function of GameOver
*/
void GameOverInit() {
	click_offset = 0.1;
}


/*
	Update function of GameOver
*/
void GameOverUpdate() {
	if ((AEInputCheckTriggered(AEVK_LBUTTON) && click_offset <= 0)) {
		gGameStateNext = GS_MENU;
	}

	click_offset -= g_dt * FRAMERATE;
}


/*
	Draw function of GameOver
*/
void GameOverDraw() {
	AEGfxSetBackgroundColor(.0f, .0f, .0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	AEMtx33 scale{ 0 };
	AEMtx33 rotate{ 0 };
	AEMtx33 translate{ 0 };
	AEMtx33 transform{ 0 };

	AEGfxTextureSet(Gameover_screen, 0, 0);
	AEMtx33Trans(&translate, 0, 0);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, (f32)AEGetWindowWidth(), (f32)AEGetWindowHeight());
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh_GameOver, AE_GFX_MDM_TRIANGLES);
}


/*
	Load function of GameOver
*/
void VictoryDraw() {
	AEGfxSetBackgroundColor(.0f, .0f, .0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	AEMtx33 scale{ 0 };
	AEMtx33 rotate{ 0 };
	AEMtx33 translate{ 0 };
	AEMtx33 transform{ 0 };

	AEGfxTextureSet(Victory_screen, 0, 0);
	AEMtx33Trans(&translate, 0, 0);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, (f32)AEGetWindowWidth(), (f32)AEGetWindowHeight());
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh_GameOver, AE_GFX_MDM_TRIANGLES);
}


/*
	Free function of GameOver
*/
void GameOverFree() {}


/*
	Unload function of GameOver
*/
void GameOverUnload() {
	AEGfxMeshFree(pMesh_GameOver);
	AEGfxTextureUnload(Gameover_screen);
	AEGfxTextureUnload(Victory_screen);
}