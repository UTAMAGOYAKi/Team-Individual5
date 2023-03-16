#include "Main.h"

AEGfxVertexList* pMesh_Loadscreen;
AEGfxTexture *load_screen;

float load_screen_time{};
const float load_screen_timer{ 3 };

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

void LoadScreenInit() {
	load_screen_time = load_screen_timer;
}

void LoadScreenUpdate() {
	if (load_screen_time > 0) {
		load_screen_time -= (f32)g_dt;
	}
	if (load_screen_time <= 0 || AEInputCheckTriggered(AEVK_LBUTTON)) {
		gGameStateNext = GS_MENU;
	}
}

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

void LoadScreenFree() {}

void LoadScreenUnload() {
	AEGfxMeshFree(pMesh_Loadscreen);
	AEGfxTextureUnload(load_screen);
}
