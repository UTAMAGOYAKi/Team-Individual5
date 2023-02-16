// ---------------------------------------------------------------------------
// includes
#pragma once
#include "Main.h"
#include <iostream>
#include <fstream>
#include "Buttons.h"
#include "Battle_system.h"
#include "UI.h"


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
AEGfxTexture *chara{}, * rat{}, * spell_g{}, * fire{}, * poison{}, * shame{}, * box{};

aabb* chara_pos;
aabb* Enemy_pos_1;
aabb* Enemy_pos_2;
/// <summary>
s8 font = AEGfxCreateFont("\Assets\Roboto-Regular.ttf",1);

s32 pX{};
s32 pY{};

//Modes
bool alchemy_mode = 0;
bool pause_mode = false;

player* alchemice{};

//GameObject creations
std::string rat_hp{};
enemy* enemies[3]{};

aabb buttons[3];

void GameStateAlchemiceLoad() {
	pMesh = 0;
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
	// Saving the mesh (list of triangles) in pMesh
	pMesh = AEGfxMeshEnd();

	//font
	font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", 26);
	chara = AEGfxTextureLoad("Assets/character.png");
	rat = AEGfxTextureLoad("Assets/rat_Piskel.png");

	//spells
	spell_g = AEGfxTextureLoad("Assets/spell_glyph.png");
	fire = AEGfxTextureLoad("Assets/not_fire.png");
	poison = AEGfxTextureLoad("Assets/not_posion.png");
	shame = AEGfxTextureLoad("Assets/not_burn.png");

	box = AEGfxTextureLoad("Assets/box.png");
}

// Initialization of your own variables go here
void GameStateAlchemiceInit() {
	PositionInit();
	alchemice = create_player();

	//Just for for testing; to be changed when we have a level system. 
	for (int i = 0; i < 3; i++) {
		enemies[i] = create_enemy(base_rat, rat);
		enemies[i]->pos.x = enemy_position[i].x;
		enemies[i]->pos.y = enemy_position[i].y;
	}

	for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); ++i) {
		buttons[i].mid.x = 0;
		buttons[i].mid.y = (190 - i * 180);

		buttons[i].s1.x = 300;
		buttons[i].s1.y = (190 - i * 180) + 80;
		buttons[i].s2.x = -300;
		buttons[i].s1.y = (190 - i * 180) - 80;
	}
}

void GameStateAlchemiceUpdate() {

	if (AEInputCheckTriggered(AEVK_Q))
	{
		enemies[rand() % 3]->hp--;
	}
		

	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		pause_mode = !pause_mode;
	}

	if (!pause_mode) {
		//if pause_game and !pause_game, to prevent overlapping of checking for aabb or what not
		if (alchemy_mode)
		{

		}
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

	AEMtx33 scale{ 0 };
	AEMtx33 rotate{ 0 };
	AEMtx33 translate{ 0 };
	AEMtx33 transform{ 0 };



	//Character drawing
	AEGfxTextureSet(chara, 0, 0);
	AEMtx33Trans(&translate, (f32)player_position.x, (f32)player_position.y);
	AEMtx33Rot(&rotate, PI);
	AEMtx33Scale(&scale, -200.f, 200.f);
	AEMtx33Concat(&transform, &rotate, &scale);	
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

	for (int i = 0; i < 3; ++i) {
		AEGfxTextureSet(enemies[i]->texture, 0, 0);
		AEMtx33Trans(&translate, (f32)(enemies[i]->pos.x), (f32)(enemies[i]->pos.y));
		AEMtx33Rot(&rotate, PI);
		AEMtx33Scale(&scale, 100.f, 100.f);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		enemy_info(enemies[i], font, pMesh);
	}

	if (pause_mode) {
		AEGfxTextureSet(box, 0, 0);
		AEMtx33Trans(&translate, 0, 0);
		AEMtx33Rot(&rotate, 0);
		AEMtx33Scale(&scale, 400, 600);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		//const char* mytex{ "test font1test font2test font3test font4test font5test font6test font7test font8test font9test font0test font1test font2test" };
		// 113 characters on screen, start to end, 113/2 =  56.5(left and right for scaling)
		const char* mytex[3]{ { "Continue" }, { "Options" }, {"Main Menu"} };

		for (int i = 0; i < 3; ++i){
			f32 middle = -(((float)strlen(mytex[i]) / 2) / 56.5f);
			f32 textY = ((float)(AEGetWindowHeight() - i * AEGetWindowHeight()) / 2) / AEGetWindowHeight();
			f32 boxY = (float)(190 - i * 180);
			AEGfxTextureSet(box, 0.f, 0.f);
			AEMtx33Trans(&translate, 0, boxY);
			AEMtx33Rot(&rotate, 0);
			AEMtx33Scale(&scale, 300, 80);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

			AEGfxPrint(font, (s8*)mytex[i], middle, textY, 1, 0, 0, 0);
		}
		AEGfxPrint(font, (s8*)mytex[1], ((float)300/640), 0, 1, 0, 0, 0);
	}
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
	delete_player(alchemice);
	for (int i = 0; i<3; ++i) {
		delete_enemy(enemies[i]);
	}
	AEGfxMeshFree(pMesh);
}

void GameStateAlchemiceUnload() {
	AEGfxTextureUnload(chara);
	AEGfxTextureUnload(rat);

	AEGfxTextureUnload(spell_g);
	AEGfxTextureUnload(shame);
	AEGfxTextureUnload(fire);
	AEGfxTextureUnload(poison);
}
  