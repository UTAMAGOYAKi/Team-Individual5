#include "main.h"

AEGfxVertexList* pMesh_GameOver;
AEGfxTexture *Gameover_screen, *Victory_screen;

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

void GameOverInit() {
	click_offset = 0.1;
}

void GameOverUpdate() {
	if ((AEInputCheckTriggered(AEVK_LBUTTON) && click_offset <= 0)) {
		gGameStateNext = GS_MENU;
	}

	click_offset -= g_dt * FRAMERATE;
}

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

void GameOverFree() {}

void GameOverUnload() {
	AEGfxMeshFree(pMesh_GameOver);
	AEGfxTextureUnload(Gameover_screen);
	AEGfxTextureUnload(Victory_screen);
}