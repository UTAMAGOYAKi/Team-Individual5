/******************************************************************************/
/*!
\file		MainMenu.cpp
\project	Alchemice
\author 	Liang HongJie(50%), Daniel Tee(50%)
\par    	email: l.hongjie\@digipen.edu, m.tee\@digipen.edu
\brief		Function definitions for MainMenu gamestate.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "main.h"

//Variables used in MainMenu state
AEGfxVertexList* pMesh_MainMenu;
AEGfxTexture *Menu_BG, *Menu_UI;
aabb menu_buttons[4];
float const linespace_main = 75.0f;
float const texture_start = -175.0f;
float const text_start = 40.0f;
AEVec2 const main_button_size{ 140,50 };

bool exit_game = false;
bool refresher;

/*
	Load function of Menu
*/
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

	Menu_BG = AEGfxTextureLoad("Assets/Art/MainMenu_Text.png");
	Menu_UI = AEGfxTextureLoad("Assets/Art/Menu_placeh.png");

}

/*
	Init function of Menu
*/
void MenuInit()
{
	for (int i{}; i < ARRAYSIZE(menu_buttons); ++i)
	{
		AEVec2 mid = { 0, -text_start + linespace_main * i };
		menu_buttons[i] = CreateAABB(mid, main_button_size.x, main_button_size.y);
	}

}

/*
	Update function of Menu
*/
void MenuUpdate()
{

	if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		refresher = true;
	}

	if (AEInputCheckTriggered(AEVK_LBUTTON) && !exit_game)
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
					gGameStateNext = GS_TUTORIAL;
					break;

				case 2:
					gGameStateNext = GS_CREDITS;
					break;

				case 3:
					exit_game = !exit_game;
					refresher = false;

					break;

				}

			}
		}
	}

	if (refresher)
	{
		if (AEInputCheckTriggered(AEVK_LBUTTON) && exit_game)
		{
			for (int i{}; i < ARRAYSIZE(menu_buttons); ++i)
			{
				if (aabbbutton(&menu_buttons[i], mouse_pos))
				{
					switch (i)
					{
					case 1:
						gGameStateNext = GS_QUIT;
						break;

					case 2:
						exit_game = !exit_game;
						break;

					 default:
						 break;

					}
				}
			}
		}
	}

}

/*
	Draw function of Menu
*/
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

	AEGfxTextureSet(Menu_BG, 0, 0);
	AEMtx33Trans(&translate, 0, 0);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, (f32)AEGetWindowWidth(), (f32)AEGetWindowHeight());
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh_MainMenu, AE_GFX_MDM_TRIANGLES);

	for (int i{}; i < ARRAYSIZE(menu_buttons); ++i)
	{
		AEGfxTextureSet(Menu_UI, 0, 0);
		AEMtx33Trans(&translate, 0, texture_start + (i * linespace_main));
		AEMtx33Rot(&rotate, 0);
		AEMtx33Scale(&scale, main_button_size.x, main_button_size.y*2);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh_MainMenu, AE_GFX_MDM_TRIANGLES);
	}

	const char* MainMenu[] = { {"Play"}, {"Tutorial"}, {"Credits"}, {"Exit"} };

	for (int i{}; i < ARRAYSIZE(MainMenu); ++i)
	{
		f32 middle = -(((float)strlen(MainMenu[i]) / 2) / (AEGetWindowWidth() / FONT_SIZE));
		f32 textY = (float)((text_start - i * linespace_main) / ((f32)AEGetWindowHeight() / 2));
		AEGfxPrint(font, (s8*)MainMenu[i], middle, textY, 1, 0, 0, 0);
	}

	if (exit_game)
	{
		for (int i{}; i < ARRAYSIZE(menu_buttons)-1; ++i)
		{
			AEGfxTextureSet(Menu_UI, 0, 0);
			AEMtx33Trans(&translate, 0, texture_start + (i * linespace_main));
			AEMtx33Rot(&rotate, 0);
			if (i == 0)
			{
				AEMtx33Scale(&scale, main_button_size.x*2, main_button_size.y * 200);
			}
			else
			{
				AEMtx33Scale(&scale, main_button_size.x, main_button_size.y * 2);
			}
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh_MainMenu, AE_GFX_MDM_TRIANGLES);
		}


		const char* confirm_exit[] = { {"Exit?"}, {"Yes"}, {"No"}};

		for (int i{}; i < ARRAYSIZE(confirm_exit); ++i)
		{
			f32 middle = -(((float)strlen(confirm_exit[i]) / 2) / (AEGetWindowWidth() / FONT_SIZE));
			f32 textY = (float)((text_start - i * linespace_main) / ((f32)AEGetWindowHeight() / 2));
			AEGfxPrint(font, (s8*)confirm_exit[i], middle, textY, 1, 0, 0, 0);
		}


	}

}

/*
	Free function of Menu
*/
void MenuFree() {}

/*
	Unload function of Menu
*/
void MenuUnload() {
	AEGfxMeshFree(pMesh_MainMenu);
	AEGfxTextureUnload(Menu_UI);
	AEGfxTextureUnload(Menu_BG);
}