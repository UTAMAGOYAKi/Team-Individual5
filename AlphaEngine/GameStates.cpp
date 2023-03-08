// ---------------------------------------------------------------------------
// includes
#pragma once
#include "Main.h"
#include <iostream>
#include <fstream>
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
Spell* spellbook{};
//Coords for active cards
AEVec2 cards;
//Crafting table for magic
craftingtable crafting_table;
//---------------------------------------------------------------------------------


//Loading of Mesh and Texture
AEGfxVertexList* pMesh{}, * pLoad{};
AEGfxTexture* chara{}, * rat{}, * spell_g{}, * pause_box{}, * sub{}, * load_screen{}, * crafting_test{}, * bg{}, * end_turn_box{}, *mana_full{}, * mana_empty{};
AEGfxTexture* Menu_ui{};

aabb* chara_pos;
aabb* Enemy_pos_1;
aabb* Enemy_pos_2;
/// <summary>
s8 font;

s32 pX{};
s32 pY{};

//Modes
bool alchemy_mode = 0;
bool pause_mode = false;
bool sub_menu = false;

//Level Turn checks
Turn turn;
Level level;

//GameObject Creations
player* alchemice{};
Enemy enemies[3]{};

//Enemy Animations
AEGfxTexture* blast[3];
float frame_time{ 2 };
double curr_time{ frame_time }; //Animations Timer
bool is_enemy_turn = false;
int enemy_animation_turn = 0;

//Button AABB
aabb pause_buttons[3];
aabb end_turn_button;
aabb menu_buttons[4];

void GameStateAlchemiceLoad() {
	pMesh = 0;
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
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f);
	// Saving the mesh (list of triangles) in pMesh
	pMesh = AEGfxMeshEnd();

	chara = AEGfxTextureLoad("Assets/char.png");
	rat = AEGfxTextureLoad("Assets/Rat.png");
	sub = AEGfxTextureLoad("Assets/submenu.png");
	pause_box = AEGfxTextureLoad("Assets/pause_button.png");
	end_turn_box = AEGfxTextureLoad("Assets/end_button.png");
	crafting_test = AEGfxTextureLoad("Assets/copyright_table.png");
	bg = AEGfxTextureLoad("Assets/background.png");
	mana_full = AEGfxTextureLoad("Assets/mana_full.png");
	mana_empty = AEGfxTextureLoad("Assets/mana_empty.png");

	blast[0] = AEGfxTextureLoad("Assets/blast1.png");
	blast[1] = AEGfxTextureLoad("Assets/blast2.png");
	blast[2] = AEGfxTextureLoad("Assets/blast3.png");
}

// Initialization of your own variables go here
void GameStateAlchemiceInit() {
	PositionInit();
	alchemice = create_player();
	//Init All Spells
	spellbook = init_all_spells();

	//
	turn = player_turn;
	sub_menu = false;
	pause_mode = false;

	//Draw all spells that are active at beginning
	AEVec2Zero(&cards);
	AEVec2Set(&cards, (f32)-(AEGetWindowWidth() / 2) + 100, -((f32)-(AEGetWindowHeight() / 2) + 100));

	for (int i = 0; i <= max_spells - 1; i++) {
		if (spellbook[i].unlocked == true) {
			if (spellbook[i].spell_dragdrop->getcoord().mid.x == 0 && spellbook[i].spell_dragdrop->getcoord().mid.y == 0) {
				spellbook[i].init_spells_draw(spellbook[i], cards);
				cards.x += 100;
				spellbook[i].spell_dragdrop->set_origin();
			}
		}
	}

	//Creation of enemy
	for (int i = 0; i < 3; i++) {
		enemies[i] = Enemy(base_rat, rat);
		enemies[i].set_position_and_aabb(enemy_position[i]);
	}

	//creates the button from top to bottom top most button [0]
	for (int i = 0; i < sizeof(pause_buttons) / sizeof(pause_buttons[0]); ++i) {
		pause_buttons[i] = CreateAABB({ 0,(f32)-190 + i * 180 }, 300, 80);
	}

	cards.x = -50;
	end_turn_button = CreateAABB({ 516,-308 }, 200, 80);
}


void GameStateAlchemiceUpdate() {

	// Updates global mouse pos
	int x, y;
	AEInputGetCursorPosition(&x, &y);
	mouse_pos.x = (f32)x - AEGetWindowWidth() / 2;
	mouse_pos.y = (f32)y - AEGetWindowHeight() / 2;

	AEVec2 temp;
	temp = mouse_pos;
	temp.y = mouse_pos.y;

	bool drag;

	drag = true;
	//Pause button, switch state of pause_mode
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		pause_mode = !pause_mode;
	}

	for (int i{}; i < sizeof(pause_buttons) / sizeof(pause_buttons[0]); ++i) //for every iteration of pause menu buttons
	{
		if (aabbbutton(&pause_buttons[i], mouse_pos) &&
			AEInputCheckTriggered(AEVK_LBUTTON) && //check if left button is clicked
			pause_mode == true) //only runs during pause mode
		{
			switch (i) {
			case 0:
				pause_mode = !pause_mode;
				break;
			case 1:
				//to be implemented when options is up
				break;
			case 2:
				gGameStateNext = GS_MENU;
				break;
			}
		}
	}

	//Draw spells player unlocks / combines
	for (int i = 4; i <= max_spells - 1; i++) {
		if (spellbook[i].unlocked == true) {
			//Checks if 2 spells are colliding for combination
			if (spellbook[i].spell_dragdrop->getcoord().mid.x == 0 && spellbook[i].spell_dragdrop->getcoord().mid.y == 0) {
				spellbook[i].init_spells_draw(spellbook[i], cards);
				cards.x += 110;
				spellbook[i].spell_dragdrop->set_origin();
			}
		}
	}

	//Mouse Debug
	if (AEInputCheckTriggered(AEVK_E))
	{
		printf("mouse x is %f\n", mouse_pos.x);
		printf("mouse y is %f\n", mouse_pos.y);
	}
	//Have to check if the player or enemies are all dead
	bool enemies_alive = false;
	for (int i{}; i < TOTAL_ENEMY; i++) {
		if (enemies[i].is_alive()) {
			enemies_alive = true;
		}
	}

	//MAIN GAMEPLAY LOOP
	//Check if players or enemies or all enemies are all dead
	if (alchemice->hp > 0 && enemies_alive && !pause_mode) {
		//Checking for turns
		if (turn == player_turn) {

			if (AEInputCheckCurr(AEVK_LBUTTON))
			{
				for (int i = 0; i <= max_spells - 1; i++)
				{
					if (aabbbutton(spellbook[i].spell_dragdrop, mouse_pos))
					{
						for (int i = 0; i <= max_spells - 1; i++)
						{
							if (spellbook[i].spell_dragdrop->getmouse())
							{
								drag = false;
							}
						}
						if (drag)
						{
							spellbook[i].spell_dragdrop->mousechange(true);
						}
					}
				}
			}

			for (int i = 0; i <= max_spells - 1; i++)
			{
				if (spellbook[i].spell_dragdrop->getmouse())
				{
					spellbook[i].spell_dragdrop->moveto(temp);

				}
			}

			if (AEInputCheckReleased(AEVK_LBUTTON))
			{
				for (int i = 0; i < max_spells; i++)
				{
					for (int j = 0; j < TOTAL_ENEMY; ++j)
					{
						if (aabbbutton(spellbook[i].spell_dragdrop, enemies[j].get_aabb()) != -1)
						{
							if (enemies[j].is_alive() && alchemice->mp > 0)
							{
								enemies[j].take_damage(spellbook[i].base_damage);
								alchemice->mp -= 1;
								if (spellbook[i].id > 3) {
									spellbook[i].reset_spell();
									cards.x -= 110;
								}
							}
						}

					}
				}

				for (int i = 0; i <= max_spells - 1; i++)
				{
					if (spellbook[i].spell_dragdrop->getmouse())
					{
						std::cout << "RELEASE" << std::endl;
						if (aabbbutton(crafting_table.get_dragdrop(), spellbook[i].spell_dragdrop) == 1 && alchemice->mp > 0) {
							if (crafting_table.crafting_table_update(spellbook, spellbook[i].id) == 3) {
								alchemice->mp -= 1;
							}
						}
						else {
							if (crafting_table.get_spell1() == spellbook[i].id) {
								crafting_table.reset_spells();
							}
							spellbook[i].spell_dragdrop->resetaabb();
							spellbook[i].spell_dragdrop->mousechange(false);
						}
					}
				}
			}

			//Check for mouse click
			if (AEInputCheckTriggered(AEVK_LBUTTON))
			{
				for (int i = 0; i <= max_spells - 1; i++) {
					if (aabbbutton(spellbook[i].spell_dragdrop, mouse_pos)) {
						std::cout << "Clicking " << spellbook[i].spell_name << std::endl;
					}
				}

				if (mouse_pos.x >= end_turn_button.s2.x && mouse_pos.x <= end_turn_button.s1.x &&
					mouse_pos.y <= end_turn_button.s2.y && mouse_pos.y >= end_turn_button.s1.y) {
					turn = enemy_turn;
					is_enemy_turn = true;
					level.display_turn = "Enemy's Turn";
					std::cout << "enemy turn " << std::endl;
				}

			}//Check for Lbutton click

			//Opening sub menu
			if (AEInputCheckTriggered(AEVK_W))
			{
				sub_menu = !sub_menu;
			}

			//Debug for dealing damage, (put the dragging of spell onto enemy here)
			if (AEInputCheckTriggered(AEVK_Q))
			{
				enemies[rand() % TOTAL_ENEMY].take_damage(1);
			}
		}//End of player turn logic

		//Enemy turn; runs all the enemy functions and animations
		else if (turn == enemy_turn) 
		{
			
			curr_time -= AEFrameRateControllerGetFrameTime();

			//When turn ends
			if (curr_time <= 0.0f) {
				turn = player_turn;
				level.display_turn = "Player's Turn";

				//Variables to update when switching back to Player Turn.
				is_enemy_turn = false;
				curr_time = frame_time;
				
				//Player Mana System
				alchemice->max_mp = (alchemice->max_mp == 5) ? 5 : alchemice->max_mp + 1;
				alchemice->mp = alchemice->max_mp;
			}
			else
			{
				if (is_enemy_turn) {
					std::cout << "Enemy actual turn\n";

					for (int i = 0; i < TOTAL_ENEMY; i++) {
						if (enemies[i].is_alive())
						{
							enemies[i].set_frame_num(0);
							alchemice->hp -= enemies[i].get_atk();
							std::cout << "Enemy Damage\n";
						}
					}
					is_enemy_turn = false;
				}
				for (int i{}; i < TOTAL_ENEMY; i++) {
					enemies[i].update_animation(AEFrameRateControllerGetFrameTime());
				}
			}
		}//End of enemy_turn logic
	}//End of Main Gameplay Loop.
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

	AEGfxTextureSet(bg, 0, 0);
	AEMtx33Trans(&translate, 0, -50);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, 2000.f, 800.f);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

	//UI Drawing
	AEGfxPrint(font, (s8*)level.display_turn.c_str(), -.1f, .9f, 1.0f, 1.0f, 1.0f, 1.0f);

	//Character drawing
	AEGfxTextureSet(chara, 0, 0);
	AEMtx33Trans(&translate, (f32)player_position.x, (f32)player_position.y);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, 200.f, 200.f);
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
	
	for (int i{0}; i < alchemice->max_mp; ++i) {
		AEVec2 mana_draw_position{ (f32)(-AEGetWindowWidth()/2.5 ) + (i * 40), (f32)(-AEGetWindowHeight() / 4) };
		AEGfxTextureSet(mana_full, 0, 0);
		AEMtx33Trans(&translate, mana_draw_position.x, mana_draw_position.y);
		AEMtx33Rot(&rotate, 0);
		AEMtx33Scale(&scale, 32.f, 32.f);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		if (alchemice->mp < alchemice->max_mp) {
			for (int j{alchemice->mp}; j < alchemice->max_mp; ++j) {
				AEGfxTextureSet(mana_empty, 0, 0);
				AEVec2 mana_draw_position{ (f32)(-AEGetWindowWidth()/2.5) + (j * 40), (f32)(-AEGetWindowHeight() / 4) };
				AEMtx33Trans(&translate, mana_draw_position.x, mana_draw_position.y);
				AEMtx33Concat(&transform, &rotate, &scale);
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);
				AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
			}
		}
	}

	//Crafting Table
	draw_crafting_table(pMesh, crafting_table, crafting_test);

	//Card Drawing
	draw_all_spells(spellbook, pMesh);

	//Enemy drawing
	for (int i = 0; i < TOTAL_ENEMY; ++i) {
		if (enemies[i].is_alive())
		{
			AEGfxTextureSet(enemies[i].get_texture(), 0, 0);
			AEMtx33Trans(&translate, (f32)(enemies[i].get_pos().x), (f32)(enemies[i].get_pos().y));
			AEMtx33Rot(&rotate, 0);
			AEMtx33Scale(&scale, 100.f, 100.f);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

			enemy_info(enemies[i], font, pMesh);
		}
	}

	//Enemy Attack Animation
	if (turn == enemy_turn) {

		for (int i{}; i < TOTAL_ENEMY; i++) {
			if (enemies[i].is_alive() && (i == enemy_animation_turn))
			{
				AEGfxTextureSet(blast[enemies[i].get_frame_num()], 0, 0);
				AEMtx33Trans(&translate, (f32)(enemies[i].get_pos().x), (f32)(enemies[i].get_pos().y));
				AEMtx33Rot(&rotate, 0);
				AEMtx33Scale(&scale, 100.f, 100.f);
				AEMtx33Concat(&transform, &rotate, &scale);
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);
				AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
			}
		}
	}


	// End turn button
	// 113 characters on screen, start to end, 113/2 =  56.5(left and right for scaling) Roboto
	// 85 characters, 85/2 = 42.5 Gothic
	// 1280W,720H, 640/HalfWidth, 360/HalfHeight
	const char* mytext{ "End Turn" };
	f32 middle = (end_turn_button.mid.x / (AEGetWindowWidth() / 2));
	f32 offset = -((float)strlen(mytext) / 2) / (AEGetWindowWidth() / FONT_SIZE);
	AEGfxTextureSet(end_turn_box, 0.f, 0.f);
	AEMtx33Trans(&translate, end_turn_button.mid.x, -end_turn_button.mid.y);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, 180, 300);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
	AEGfxPrint(font, (s8*)mytext, middle + offset, (f32)-(end_turn_button.mid.y / (AEGetWindowHeight() / 2)), 1, 0, 0, 0);


	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	if (sub_menu)
	{
		sub_menu_draw(sub, spellbook, pMesh, font);
	}

	if (pause_mode) {
		AEGfxTextureSet(pause_box, 0, 0);
		AEMtx33Trans(&translate, 0, 0);
		AEMtx33Rot(&rotate, 0);
		AEMtx33Scale(&scale, 400, 600);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		// 113 characters on screen, start to end, 113/2 =  56.5(left and right for scaling) Roboto
		// 85 characters, 85/2 = 42.5 Gothic
		// 1280W,720H, 640/HalfWidth, 360/HalfHeight
		const char* mytex[3]{ { "Continue" }, { "Options" }, {"Main Menu"} };

		for (int i = 0; i < 3; ++i) {
			f32 middle = -(((float)strlen(mytex[i]) / 2) / (AEGetWindowWidth() / FONT_SIZE));
			f32 textY = ((float)(AEGetWindowHeight() - i * AEGetWindowHeight()) / 2) / AEGetWindowHeight();
			f32 boxY = (float)(190 - i * 180);
			AEGfxTextureSet(pause_box, 0.f, 0.f);
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
}

void GameStateAlchemiceFree() {
	AEGfxMeshFree(pMesh);
}

void GameStateAlchemiceUnload() {
	AEGfxTextureUnload(chara);
	AEGfxTextureUnload(rat);
	AEGfxTextureUnload(sub);
	AEGfxTextureUnload(pause_box);
	AEGfxTextureUnload(end_turn_box);
	AEGfxTextureUnload(crafting_test);
	AEGfxTextureUnload(bg);
	AEGfxTextureUnload(blast[0]);
	AEGfxTextureUnload(blast[1]);
	AEGfxTextureUnload(blast[2]);
	AEGfxTextureUnload(mana_full);
	AEGfxTextureUnload(mana_empty);
	unload_spells(spellbook);
	delete_player(alchemice);
}

float load_screen_time{};

void LoadScreenLoad() {
	pLoad = 0;
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		-0.5f, 0.5f, 0x00000000, 0.0f, 0.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f);
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00000000, 0.0f, 1.0f,
		0.5f, 0.5f, 0x00000000, 1.0f, 0.0f,
		0.5f, -0.5f, 0x00000000, 1.0f, 1.0f);
	pLoad = AEGfxMeshEnd();

	load_screen = AEGfxTextureLoad("Assets/digilogo.png");
}

void LoadScreenInit() {
	//0 for now since its annoying to wait
	load_screen_time = 0;
}

void LoadScreenUpdate() {
	if (load_screen_time > 0) {
		load_screen_time -= (f32)AEFrameRateControllerGetFrameTime();
	}
	else {
		gGameStateNext = GS_MENU;
	}
}

void LoadScreenDraw() {
	AEGfxSetBackgroundColor(.0f, .0f, .0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

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
	AEGfxMeshDraw(pLoad, AE_GFX_MDM_TRIANGLES);
}

void LoadScreenFree() {
	AEGfxMeshFree(pLoad);
}

void LoadScreenUnload() {
	AEGfxTextureUnload(load_screen);
}


void Menuload()
{
	Menu_ui = AEGfxTextureLoad("Assets/Menu_placeh.png");

	pLoad = 0;
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
	// Saving the mesh (list of triangles) in pMesh
	pLoad = AEGfxMeshEnd();
}

void Menuinit()
{
	for (int i = 0; i < 4; i++)
	{
		AEVec2 mid = { 0, -100.0f+75.0f*i};
		menu_buttons[i] = CreateAABB(mid,128.0,50.0);
	}

}
void Menuupdate()
{
	AEGfxSetBackgroundColor(.2f, .2f, .2f);

	s32 x, y;
	AEInputGetCursorPosition(&x, &y);
	mouse_pos.x = (f32)x - AEGetWindowWidth() / 2;
	mouse_pos.y = (f32)y - AEGetWindowHeight() / 2;

	
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		for (int i = 0; i < 4; i++)
		{
			if (aabbbutton(&menu_buttons[i], mouse_pos))
			{
				switch (i+1)
				{
				case 1:
					gGameStateNext = GS_ALCHEMICE;
					break;

				case 2:
					std::cout << "Options are not coded yet!\n";
					break;

				case 3:
					//send the player to the credits
					std::cout <<"Credits are not coded yet!\n";
					break;

				case 4:
					gGameStateNext = GS_QUIT;
					break;

				}

			}
		}
	}
	
}
void Menudraw()
{
	AEMtx33 scale{ 0 };
	AEMtx33 rotate{ 0 };
	AEMtx33 translate{ 0 };
	AEMtx33 transform{ 0 };

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	for (int i = 0; i < 4; i++)
	{
		AEGfxTextureSet(Menu_ui, 0, 0);
		AEMtx33Trans(&translate, 0, -125.0f+(i*75.0f));
		AEMtx33Rot(&rotate, 0);
		AEMtx33Scale(&scale, 128, 100);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pLoad, AE_GFX_MDM_TRIANGLES);
	}

	char strbuffer[100];
	const char* words[4] = { "Play","Options", "Credits","Exit" };
	memset(strbuffer, 0, 100 * sizeof(char));
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(strbuffer, words[i]);
		AEGfxPrint(font, strbuffer, -0.08f, 0.25f-i*0.21f, 1.0f, 0.0f, 0.0f, 0.0f);
	}

}
void Menufree()
{
	AEGfxMeshFree(pLoad);
}
void Menuunload()
{
	AEGfxTextureUnload(Menu_ui);
}