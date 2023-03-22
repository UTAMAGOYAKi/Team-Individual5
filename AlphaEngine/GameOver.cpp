#include "main.h"

double click_offset_gameover;

void GameOverLoad() {}

void GameOverInit() {
	click_offset_gameover = 0.1;
}

void GameOverUpdate() {
	click_offset_gameover -= g_dt;
	if ((AEInputCheckTriggered(AEVK_LBUTTON) && click_offset_gameover <= 0)) {
		gGameStateNext = GS_MENU;
	}
}

void GameOverDraw() {
	AEGfxSetBackgroundColor(.0f, .0f, .0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	AEMtx33 scale{ 100 };
	AEMtx33 rotate{ 0 };
	AEMtx33 translate{ 0 };
	AEMtx33 transform{ 0 };

	const char* Credits[] = { {"You DIED."}};

	for (int i{}; i < ARRAYSIZE(Credits); ++i)
	{
		f32 middle = -(((float)strlen(Credits[i]) / 2) / (AEGetWindowWidth() / FONT_SIZE));
		f32 textY = (0) / ((f32)AEGetWindowHeight() / 2);
		AEMtx33Rot(&rotate, 0);
		AEMtx33Scale(&scale, 300, 80);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxPrint(font, (s8*)Credits[i], middle, textY, 1, 1, 1, 1);
	}
}

void GameOverFree() {}

void GameOverUnload() {}