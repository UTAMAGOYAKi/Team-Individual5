/******************************************************************************/
/*!
\file		Credits.cpp
\project	Alchemice
\author 	Liang HongJie
\par    	email: l.hongjie\@digipen.edu
\brief		Function definitions for Credits gamestate.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "main.h"

//Defines
AEGfxVertexList* pMesh_Creditscreen;
AEGfxTexture *fmodcredits;
AEVec2 fmodposition;

int linespace;
double scroll_time_current;
double scroll_time_max;

void CreditsLoad() {
	pMesh_Creditscreen = 0;
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f);
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f);
	pMesh_Creditscreen = AEGfxMeshEnd();

	fmodcredits = AEGfxTextureLoad("Assets/FMODlogo.png");
}

void CreditsInit() {
	scroll_time_current = 0;
	scroll_time_max = 42.0 * (f64)FRAMERATE;
	click_offset = 0.1;
	linespace = 60;
	fmodposition.x = 0;
	fmodposition.y = -360;
	fmodposition.y = -(35 * linespace);
}

void CreditsUpdate()
{
	if (click_offset <= 0) {
		scroll_time_current += g_dt * FRAMERATE;
	}

	if ((AEInputCheckTriggered(AEVK_LBUTTON) && click_offset <= 0) || scroll_time_current >= scroll_time_max) {
		gGameStateNext = GS_MENU;
	}

	click_offset -= g_dt * FRAMERATE;
	fmodposition.y += g_dt*FRAMERATE;
}

void CreditsDraw()
{
	AEGfxSetBackgroundColor(.0f, .0f, .0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	
	AEMtx33 scale{ 0 };
	AEMtx33 rotate{ 0 };
	AEMtx33 translate{ 0 };
	AEMtx33 transform{ 0 };

	AEGfxTextureSet(fmodcredits, 0, 0);
	AEMtx33Trans(&translate, fmodposition.x, fmodposition.y);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, (f32)AEGetWindowWidth(), (f32)AEGetWindowHeight());
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh_Creditscreen, AE_GFX_MDM_TRIANGLES);

	const char* Credits[] = { {"Team::Individual[5];"}, {""}, {"Developers"}, {"Daniel Tee Ming Zhe"}, {"Liang HongJie"}, {"Low Ee Loong"}, {"Yeo Jun Jie"}, {""},
		{"Instructors"}, {"Cheng Ding Xiang"}, {"Gerald Wong"}, {""},
		{"Created at"}, {"Digipen Institute of Technology Singapore"}, {""},
		{"President"}, {"Claude Comair"}, {""},
		{"Executives"}, {"Angela Kugler"}, {"Ben Ellinger"}, {"Christopher Comair"}, {"Dr. Charles Duba"}, {"Dr. Erik Mohrmann"}, {"Jason Chu"}, {"John Bauer"}, {"Johnny Deek"}, {"Melvin Gonsalvez"},
		{"Michael Gats"}, {"Michele Comair"}, {"Prasanna Ghali"}, {"Samir Abou Samra"}, {"WWW.DIGIPEN.EDU"} };
	
	for (int i{}; i < ARRAYSIZE(Credits); ++i)
	{
		f32 middle = -(((float)strlen(Credits[i]) / 2) / (AEGetWindowWidth() / FONT_SIZE));
		f32 textY = (float)((0 - i*linespace + scroll_time_current) / ((f32)AEGetWindowHeight()/2));
		AEGfxPrint(font, (s8*)Credits[i], middle, textY, 1, 1, 1, 1);
	}
}

void CreditsFree() {}

void CreditsUnload() {
	AEGfxMeshFree(pMesh_Creditscreen);
	AEGfxTextureUnload(fmodcredits);
}