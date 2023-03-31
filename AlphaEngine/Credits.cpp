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

int linespace;
double scroll_time_current;
double scroll_time_max;

void CreditsLoad() {}
void CreditsInit() {
	scroll_time_current = 0;
	scroll_time_max = 38.0 * (f64)FRAMERATE;
	click_offset = 0.1;
	linespace = 60;
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
}

void CreditsDraw()
{
	AEGfxSetBackgroundColor(.0f, .0f, .0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	
	const char* Credits[] = { {"Developers"}, {"Daniel Tee Ming Zhe"}, {"Liang HongJie"}, {"Low Ee Loong"}, {"Yeo Jun Jie"}, {""},
		{"Instructors"}, {"Cheng Ding Xiang"}, {"Gerald Wong"}, {""},
		{"Created at"}, {"Digipen Institude of Technology Singapore"}, {""},
		{"President"}, {"Claude Comair"}, {""},
		{"Executives"}, {"Angela Kugler"}, {"Ben Ellinger"}, {"Christopher Comair"}, {"Dr. Charles Duba"}, {"Dr. Erik Mohrmann"}, {"Jason Chu"}, {"John Bauer"}, {"Johnny Deek"}, {"Melvin Gonsalvez"},
		{"Michael Gats"}, {"Michele Comair"}, {"Prasanna Ghali"}, {"Samir Abou Samra"}, {"WWW.DIGIPEN.EDU"} };
	
	for (int i{}; i < ARRAYSIZE(Credits); ++i)
	{
		f32 middle = -(((float)strlen(Credits[i]) / 2) / (AEGetWindowWidth() / FONT_SIZE));
		f32 textY = (float)((0 - i*linespace + scroll_time_current)/((f32)AEGetWindowHeight()/2));
		AEGfxPrint(font, (s8*)Credits[i], middle, textY, 1, 1, 1, 1);
	}
}

void CreditsFree() {}
void CreditsUnload() {}