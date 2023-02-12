// ---------------------------------------------------------------------------
// includes
#pragma once
#include "Main.h"
#include <iostream>
#include <fstream>
#include "Buttons.h"

//Reference for controls
//Q - basic attack against first rat
//W - start alchemy
//Z - check for mouse position
//X - cancel alchemy
//E - in alchemy, try combination
//drag& drop fire to left spell slot of glyth
//poison on right
//burn can be placed on either rat, but second rat has no hp

// ---------------------------------------------------------------------------
// main
int i = 0;
float position = 1000.0;


enum spell_slot { empty, fire_slot, poison_slot, lighting_slot };
Ingredients spell_slot_one = NILL;
Ingredients spell_slot_two = NILL;
//int gGameRunning = 1;

//Loading of Mesh and Texture
AEGfxVertexList *pMesh{};
AEGfxTexture* pTex{}, * chara{}, * rat{}, * spell_g{}, * fire{}, * poison{}, * shame{};


/// <summary>
s8 test_font;

s32 pX{};
s32 pY{};

//Modes
bool alchemy_mode = 0;

player* alchemice{};
std::string rat_hp{};


void GameStateAlchemiceLoad() {
	pMesh = 0;
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF00FF, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFF00, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFF00FFFF, 0.0f, 1.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
	// Saving the mesh (list of triangles) in pMesh
	pMesh = AEGfxMeshEnd();

	test_font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", 26);

	pTex = AEGfxTextureLoad("Assets/rat_Piskel.png");
	chara = AEGfxTextureLoad("Assets/character.png");
	rat = AEGfxTextureLoad("Assets/rat_Piskel.png");
	spell_g = AEGfxTextureLoad("Assets/spell_glyph.png");
	fire = AEGfxTextureLoad("Assets/not_fire.png");
	poison = AEGfxTextureLoad("Assets/not_posion.png");
	shame = AEGfxTextureLoad("Assets/not_burn.png");
}

void GameStateAlchemiceInit() {
	// Initialization of your own variables go here

	alchemice = player_create();
}

void GameStateAlchemiceUpdate() {


	if (alchemy_mode)
	{

	}
}

void GameStateAlchemiceDraw() {
	// Your own rendering logic goes here
	// Set the background to black.
	AEGfxSetBackgroundColor(.2f, .2f, .2f);
	// Tell the engine to get ready to draw something with texture.
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// Set the tint to white, so that the sprite can 
	// display the full range of colors (default is black).
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set blend mode to AE_GFX_BM_BLEND
	// This will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	// Set the texture to pTex
	AEGfxTextureSet(pTex, 0, 0);
	// Create a scale matrix that scales by 100 x and y
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, 100.f, 100.f);
	// Create a rotation matrix that rotates by 45 degrees
	AEMtx33 rotate = { 0 };

	AEMtx33Rot(&rotate, PI);
	// Create a translation matrix that translates by
	// 100 in the x-axis and 100 in the y-axis
	AEMtx33 translate = { 0 };

	AEMtx33Trans(&translate, (250.f), -20.f);
	// Concat the matrices (TRS)
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	// Choose the transform to use
	AEGfxSetTransform(transform.m);
	// Actually drawing the mesh 
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

	//Character drawing
	AEGfxTextureSet(chara, 0, 0);
	AEMtx33Trans(&translate, (-200.f), 20.f);
	AEMtx33Rot(&rotate, PI);
	AEMtx33Scale(&scale, -200.f, 200.f);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

	//Enemy Drawing (Needs to be a loop in the future)
	AEGfxTextureSet(rat, 0, 0);
	AEMtx33Trans(&translate, (position - 900.f), -20.f);
	AEMtx33Rot(&rotate, PI);
	AEMtx33Scale(&scale, 100.f, 100.f);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);



	//if (alchemy_mode)
	//{
	//	AEGfxTextureSet(fire, 0, 0);
	//	AEMtx33Trans(&translate, fire_x, -fire_y);
	//	AEMtx33Rot(&rotate, PI);
	//	AEMtx33Scale(&scale, 100.f, 100.f);
	//	AEMtx33Concat(&transform, &rotate, &scale);
	//	AEMtx33Concat(&transform, &translate, &transform);
	//	AEGfxSetTransform(transform.m);
	//	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

	//	AEGfxTextureSet(poison, 0, 0);
	//	AEMtx33Trans(&translate, poison_x, -poison_y);
	//	AEMtx33Rot(&rotate, PI);
	//	AEMtx33Scale(&scale, 100.f, 100.f);
	//	AEMtx33Concat(&transform, &rotate, &scale);
	//	AEMtx33Concat(&transform, &translate, &transform);
	//	AEGfxSetTransform(transform.m);
	//	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
	//}

	//AEGfxPrint(test_font, (s8*)test_str, -0.65f, 0.5f, 1, 0.0f, 0.0f, 0.0f);
	//if (rat_hp_1 > 0)
	//{
	//	AEGfxPrint(test_font, (s8*)rat_name_1, 0.225f, 0.2f, 1, 0.0f, 0.0f, 0.0f);
	//	AEGfxPrint(test_font, (s8*)rat_hp.c_str(), 0.225f, 0.1f, 1, 0.0f, 0.0f, 0.0f);
	//}
	//AEGfxPrint(test_font, (s8*)rat_name_2, 0.625f, 0.2f, 1, 0.0f, 0.0f, 0.0f);
}

void GameStateAlchemiceFree() {
	AEGfxMeshFree(pMesh);
}

void GameStateAlchemiceUnload() {
	AEGfxTextureUnload(pTex);
	AEGfxTextureUnload(rat);
	AEGfxTextureUnload(chara);
	AEGfxTextureUnload(shame);
	AEGfxTextureUnload(fire);
	AEGfxTextureUnload(poison);
}