#include "main.h"

AEGfxTexture *Menu_UI;
AEGfxVertexList *pMesh_MainMenu;

aabb menu_buttons[4];

void MenuLoad()
{
	Menu_UI = AEGfxTextureLoad("Assets/Menu_placeh.png");

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
}

void MenuInit()
{
	for (int i = 0; i < 4; i++)
	{
		AEVec2 mid = { 0, -100.0f + 75.0f * i };
		menu_buttons[i] = CreateAABB(mid, 128.0, 50.0);
	}

}
void MenuUpdate()
{
	AEGfxSetBackgroundColor(.2f, .2f, .2f);

	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		for (int i = 0; i < 4; i++)
		{
			if (aabbbutton(&menu_buttons[i], mouse_pos))
			{
				switch (i + 1)
				{
				case 1:
					gGameStateNext = GS_ALCHEMICE;
					break;

				case 2:
					std::cout << "Options are not coded yet!\n";
					break;

				case 3:
					//send the player to the credits
					std::cout << "Credits are not coded yet!\n";
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
	AEMtx33 scale{ 0 };
	AEMtx33 rotate{ 0 };
	AEMtx33 translate{ 0 };
	AEMtx33 transform{ 0 };

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTransparency(1.0f);
	for (int i = 0; i < 4; i++)
	{
		AEGfxTextureSet(Menu_UI, 0, 0);
		AEMtx33Trans(&translate, 0, -125.0f + (i * 75.0f));
		AEMtx33Rot(&rotate, 0);
		AEMtx33Scale(&scale, 128, 100);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh_MainMenu, AE_GFX_MDM_TRIANGLES);
	}

	char strbuffer[100];
	const char* words[4] = { "Play","Options", "Credits","Exit" };
	memset(strbuffer, 0, 100 * sizeof(char));
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(strbuffer, words[i]);
		AEGfxPrint(font, strbuffer, -0.08f, 0.25f - i * 0.21f, 1.0f, 0.0f, 0.0f, 0.0f);
	}

}
void MenuFree()
{
	AEGfxMeshFree(pMesh_MainMenu);
}
void MenuUnload()
{
	AEGfxTextureUnload(Menu_UI);
}