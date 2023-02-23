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
AEVec2 mouse_pos{}; // Current mouse pos

//Card Variables
//---------------------------------------------------------------------------------
// Card Details 
//---------------------------------------------------------------------------------

//Contains all spells in a dynamically allocated array
Spell* spellbook;
//Coords for active cards
AEVec2 cards;
//---------------------------------------------------------------------------------


//enum spell_slot { empty, fire_slot, poison_slot, lighting_slot };
//Elements spell_slot_one = NILL;
//Elements spell_slot_two = NILL;
//int gGameRunning = 1;

//Loading of Mesh and Texture
AEGfxVertexList* pMesh{}, *pLoad{};
AEGfxTexture* chara{}, * rat{}, * spell_g{}, * box{}, * sub{}, *load_screen{};

aabb* chara_pos;
aabb* Enemy_pos_1;
aabb* Enemy_pos_2;
/// <summary>
s8 font{};

s32 pX{};
s32 pY{};

//Modes
bool alchemy_mode = 0;
bool pause_mode = false;
bool sub_menu = false;

player* alchemice{};

//GameObject creations
std::string rat_hp{};
Enemy enemies[3]{};

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

	chara = AEGfxTextureLoad("Assets/character.png");
	rat = AEGfxTextureLoad("Assets/rat_Piskel.png");
	sub = AEGfxTextureLoad("Assets/submenu.png");
	box = AEGfxTextureLoad("Assets/box.png");
}

// Initialization of your own variables go here
void GameStateAlchemiceInit() {
	PositionInit();
	alchemice = create_player();

	//Init All Spells
	spellbook = init_allspells();

	//Draw all spells that are active at beginning
	AEVec2Zero(&cards);
	AEVec2Set(&cards, (f32) - (AEGetWindowWidth() / 2) + 100,(f32) - (AEGetWindowHeight() / 2) + 100);


	//Creation of enemy
	for (int i = 0; i < 3; i++) {
		enemies[i] = Enemy(base_rat, rat);
		enemies[i].set_position(enemy_position[i]);
	}

	for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); ++i) {
		buttons[i].mid.x = 0;
		buttons[i].mid.y = (f32)(190 - i * 180);

		buttons[i].s1.x = 300;
		buttons[i].s1.y = (f32)(190 - i * 180) + 80;
		buttons[i].s2.x = -300;
		buttons[i].s1.y = (f32)(190 - i * 180) - 80;
	}
}

void GameStateAlchemiceUpdate() {

	// Updates global mouse pos
	int x , y;
	AEInputGetCursorPosition(&x, &y);
	mouse_pos.x = (f32)x - AEGetWindowWidth()/2;
	mouse_pos.y = (f32)y - AEGetWindowHeight()/2;

	//std::cout << "mouse x:" << mouse_pos.x << "mouse y:" << mouse_pos.y << std::endl;

	//Check for mouse click
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		for (int i = 0; i <= max_spells-1; i++) {
			if (aabbbutton(spellbook[i].spell_dragdrop, mouse_pos)) {
				std::cout<< "Clicking "<< spellbook[i].spell_name<<std::endl;
			}
		}
	}

	//Draw spells player unlocks / combines
//TO BE IMPLEMENTED

	for (int i = 0; i <= max_spells-1; i++) {
		if (spellbook[i].unlocked == true) {
			if (spellbook[i].spell_dragdrop->getcoord().mid.x == 0 && spellbook[i].spell_dragdrop->getcoord().mid.y == 0) {
				spellbook[i].init_spells_draw(spellbook[i], cards);
				cards.x += 100;
			}
		}
	}

	if (AEInputCheckTriggered(AEVK_W))
	{
		sub_menu = !sub_menu;
	}



	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		pause_mode = !pause_mode;
	}

	if (!pause_mode) {
		//if pause_game and !pause_game, to prevent overlapping of checking for aabb or what not
		if (alchemy_mode)
		{

		}
		if (AEInputCheckTriggered(AEVK_Q))
		{
			enemies[rand() % 3].change_hp(-1);
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
	std::string player_hp;
	if (alchemice->hp)
	{
		player_hp += std::to_string(alchemice->hp);
		player_hp_bar(*alchemice, player_position, pMesh);
	}
	else
	{
		player_hp += "0";
	}
	player_hp += "/";
	player_hp += std::to_string(alchemice->max_hp);
	name_bar(player_hp, player_position, font);

	// Card Drawing
	for (int i = 0; i <= max_spells-1; i++) {
		if (spellbook[i].unlocked == true) {
			AEGfxTextureSet(spellbook[i].texture, 0, 0);
			AEMtx33Trans(&translate, spellbook[i].spell_dragdrop->getcoord().mid.x, spellbook[i].spell_dragdrop->getcoord().mid.y);
			AEMtx33Rot(&rotate, PI);
			AEMtx33Scale(&scale, spellbook[i].card_width, spellbook[i].card_height);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		}
	}

	for (int i = 0; i < 3; ++i) {
		AEGfxTextureSet(enemies[i].get_texture(), 0, 0);
		AEMtx33Trans(&translate, (f32)(enemies[i].get_pos().x), (f32)(enemies[i].get_pos().y));
		AEMtx33Rot(&rotate, PI);
		AEMtx33Scale(&scale, 100.f, 100.f);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		enemy_info(enemies[i], font, pMesh);
	}

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// Set the tint to white, so that the sprite can 
	// display the full range of colors (default is black).
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set blend mode to AE_GFX_BM_BLEND
	// This will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	if (sub_menu)
	{
		sub_menu_draw(sub, spellbook, pMesh, font);
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

		for (int i = 0; i < 3; ++i) {
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
	/*delete_player(alchemice);
	for (int i = 0; i < 3; ++i) {
		delete_enemy(enemies[i]);
	}*/
	AEGfxMeshFree(pMesh);
}

void GameStateAlchemiceUnload() {
	AEGfxTextureUnload(chara);
	AEGfxTextureUnload(rat);
	unload_spells(spellbook);
}

float load_screen_time{};

void LoadScreenLoad() {
	pLoad = 0;
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f);
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f);
	// Saving the mesh (list of triangles) in pMesh
	pLoad = AEGfxMeshEnd();


	font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", 26);
	load_screen = AEGfxTextureLoad("Assets/digilogo.png");
}

void LoadScreenInit() {
	load_screen_time = 3;
}

void LoadScreenUpdate() {
	if (load_screen_time > 0) {
		load_screen_time -= (f32)AEFrameRateControllerGetFrameTime();
	}
	else {
		gGameStateNext = GS_ALCHEMICE;
	}
}

void LoadScreenDraw() {
	// Your own rendering logic goes here
	// Set the background to black.
	AEGfxSetBackgroundColor(.0f, .0f, .0f);
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

	AEGfxTextureSet(load_screen, 0, 0);
	AEMtx33Trans(&translate, 0, 0);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, 915, 287); //hardcoded values from the pixels in .png file, 3x value 
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	/*AEMtx33Identity(&transform);*/
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pLoad, AE_GFX_MDM_TRIANGLES);
}

void LoadScreenFree() {
	AEGfxMeshFree(pLoad);
}

void LoadScreenUnload() {
	AEGfxTextureUnload(load_screen);
}
