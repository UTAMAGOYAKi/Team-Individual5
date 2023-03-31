/******************************************************************************/
/*!
\file		Tutorial.cpp
\project	Alchemice
\author 	Liang HongJie
\par    	email: l.hongjie\@digipen.edu
\brief		Function definitions for Tutorial gamestate. 

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "main.h"

//Variables used in Tutorial Gamestate.
AEGfxVertexList* pMesh_Tutorialscreen;
AEGfxTexture *Tutorial_screen[12], **pointer_to_texutre;
size_t TutorialPage, TotalPages;
float yPos = 330;

/*
	Load Function of GameState Tutorial
*/
void TutorialLoad() {
	pMesh_Tutorialscreen = 0;
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f);
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f);
	pMesh_Tutorialscreen = AEGfxMeshEnd();

	Tutorial_screen[0] = AEGfxTextureLoad("Assets/Tutorial/tutorial1.png");
	Tutorial_screen[1] = AEGfxTextureLoad("Assets/Tutorial/tutorial2.png");
	Tutorial_screen[2] = AEGfxTextureLoad("Assets/Tutorial/tutorial3.png");
	Tutorial_screen[3] = AEGfxTextureLoad("Assets/Tutorial/tutorial4.png");
	Tutorial_screen[4] = AEGfxTextureLoad("Assets/Tutorial/tutorial5.png");
	Tutorial_screen[5] = AEGfxTextureLoad("Assets/Tutorial/tutorial6.png");
	Tutorial_screen[6] = AEGfxTextureLoad("Assets/Tutorial/tutorial7.png");
	Tutorial_screen[7] = AEGfxTextureLoad("Assets/Tutorial/tutorial8.png");
	Tutorial_screen[8] = AEGfxTextureLoad("Assets/Tutorial/tutorial9.png");
	Tutorial_screen[9] = AEGfxTextureLoad("Assets/Tutorial/tutorial10.png");
	Tutorial_screen[10] = AEGfxTextureLoad("Assets/Tutorial/tutorial11.png");
	Tutorial_screen[11] = AEGfxTextureLoad("Assets/Tutorial/tutorial12.png");
}

/*
	Init Function of GameState Tutorial
*/
void TutorialInit() {
	click_offset = 0.1;
	TotalPages = ARRAYSIZE(Tutorial_screen);
	TutorialPage = 0;
	pointer_to_texutre = &Tutorial_screen[TutorialPage];
}

/*
	Update Function of GameState Tutorial
*/
void TutorialUpdate() {
	
	//Early escape from tutorial screen.
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		TutorialPage = 0;
		gGameStateNext = GS_MENU;
	}

	//Check button click in tutorial screen, updates TutorialPage, TutorialPage will be the index accessor to the array list of texture loaded.
	if (click_offset <= 0 && AEInputCheckTriggered(AEVK_LBUTTON)) {
		TutorialPage = (TutorialPage < TotalPages) ? TutorialPage + 1 : TutorialPage;
		if (TutorialPage >= TotalPages) {
			TutorialPage = 0;
			gGameStateNext = GS_MENU;
		}
		click_offset = 0.1;
		pointer_to_texutre = &Tutorial_screen[TutorialPage];
	}

	//prevents mouse click from affecting between state transition. 
	click_offset -= g_dt * FRAMERATE;

}

/*
	Draw Function of GameState Tutorial
*/
void TutorialDraw() {
	AEGfxSetBackgroundColor(.0f, .0f, .0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);

	AEMtx33 scale{ 0 };
	AEMtx33 rotate{ 0 };
	AEMtx33 translate{ 0 };
	AEMtx33 transform{ 0 };

	AEGfxTextureSet(*pointer_to_texutre, 0, 0);
	AEMtx33Trans(&translate, 0, 0);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, (f32)AEGetWindowWidth(), (f32)AEGetWindowHeight());
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh_Tutorialscreen, AE_GFX_MDM_TRIANGLES);

	AEGfxSetTransparency(0.25f);
	const char* Tutorial_text[] = { {"Mouse left click to continue"}, {"Press Esc to return to Main Menu"} };

	f32 middle1 = -(((float)strlen(Tutorial_text[0]) / 2) / (AEGetWindowWidth() / FONT_SIZE));
	f32 middle2 = -(((float)strlen(Tutorial_text[1]) / 2) / (AEGetWindowWidth() / FONT_SIZE));
	f32 textY1 = (float)((yPos) / ((f32)AEGetWindowHeight() / 2));
	f32 textY2 = (float)((-yPos) / ((f32)AEGetWindowHeight() / 2));
	AEGfxPrint(font, (s8*)Tutorial_text[0], middle1, textY1, 1, 1, 1, 1);
	AEGfxPrint(font, (s8*)Tutorial_text[1], middle2, textY2, 1, 1, 1, 1);

}

/*
	Free Function of GameState Tutorial
*/
void TutorialFree() {}

/*
	Unload Function of GameState Tutorial
*/
void TutorialUnload() {
	AEGfxMeshFree(pMesh_Tutorialscreen);

	for (int i{}; i < ARRAYSIZE(Tutorial_screen); ++i)
		AEGfxTextureUnload(Tutorial_screen[i]);
}