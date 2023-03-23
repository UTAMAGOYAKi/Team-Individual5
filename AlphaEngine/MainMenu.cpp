#include "main.h"

AEGfxVertexList* pMesh_MainMenu;
AEGfxTexture *Menu_UI;
aabb menu_buttons[5];

void MenuLoad()
{
	pMesh_MainMenu = 0;
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f);
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f);
	// Saving the mesh (list of triangles) in pMesh_MainMenu
	pMesh_MainMenu = AEGfxMeshEnd();

	Menu_UI = AEGfxTextureLoad("Assets/Menu_placeh.png");

}

void MenuInit()
{
	for (int i{}; i < ARRAYSIZE(menu_buttons); ++i)
	{
		AEVec2 mid = { 0, -100.0f + 75.0f * i };
		menu_buttons[i] = CreateAABB(mid, 140.0, 50.0);
	}

}
void MenuUpdate()
{
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		for (int i{}; i < ARRAYSIZE(menu_buttons); ++i)
		{
			if (aabbbutton(&menu_buttons[i], mouse_pos))
			{
				switch (i)
				{
				case 0:
					gGameStateNext = GS_ALCHEMICE;
					break;

				case 1:
					std::cout << "Options are not coded yet!\n";
					break;

				case 2:
					gGameStateNext = GS_TUTORIAL;
					break;

				case 3:
					gGameStateNext = GS_CREDITS;
					break;

				case 4:
					gGameStateNext = GS_QUIT;
					break;

				}

			}
		}
	}

}
void MenuDraw()
{
	AEGfxSetBackgroundColor(.2f, .2f, .2f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	
	AEMtx33 scale{ 0 };
	AEMtx33 rotate{ 0 };
	AEMtx33 translate{ 0 };
	AEMtx33 transform{ 0 };

	for (int i{}; i < ARRAYSIZE(menu_buttons); ++i)
	{
		AEGfxTextureSet(Menu_UI, 0, 0);
		AEMtx33Trans(&translate, 0, -200.0f + (i * 75.0f));
		AEMtx33Rot(&rotate, 0);
		AEMtx33Scale(&scale, 140, 100);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh_MainMenu, AE_GFX_MDM_TRIANGLES);
	}

	char strbuffer[100];
	const char* words[5] = { "Play","Options", "Tutorial" ,"Credits","Exit"};
	memset(strbuffer, 0, 100 * sizeof(char));
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	for (int i{}; i < ARRAYSIZE(menu_buttons); ++i)
	{
		sprintf_s(strbuffer, words[i]);
		AEGfxPrint(font, strbuffer, -0.08f, 0.25f - i * 0.21f, 1.0f, 0.0f, 0.0f, 0.0f);
	}

}
void MenuFree() {}

void MenuUnload() {
	AEGfxMeshFree(pMesh_MainMenu);
	AEGfxTextureUnload(Menu_UI);
}