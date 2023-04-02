/******************************************************************************/
/*!
\file		GameStates.cpp
\project	Alchemice
\author 	Daniel Tee(25%), Liang HongJie(25%), Low Ee Loong(25%), Yeo Jun Jie(25%)
\par    	email: m.tee\@digipen.edu, l.hongjie\@digipen.edu,
					eeloong.l\@digipen.edu, yeo.junjie\@digipen.edu,

\brief		Function declaration for Game as well as define Enum used within Game loop
			
			Daniel contributed to the creation of player, sound and options within the pause menu.
			Eeloong contributed to the spellcrafting and its respective UI.
			Jun Jie contributed to particles and effects as well as enemies and battle system.
			HongJie contributed to the UI for battle systems as well as change of game states.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

// ---------------------------------------------------------------------------
// includes
#pragma once
#include "Main.h"
#include "Crafting.h"
#include "UI.h"
#include <iostream>
#include <fstream>
#include <math.h>

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


//Card Variables
//---------------------------------------------------------------------------------
// Card Details 
//---------------------------------------------------------------------------------
spell_book spellbook;

//Coords for active cards
AEVec2 cards;
aabb bookaabb;
AEVec2 bookpos{-540,-230};
AEVec2 bookscale{ 256,144 };
//Crafting table for magic
craftingtable crafting_table;

//---------------------------------------------------------------------------------

//Loading of Mesh and Texture
AEGfxVertexList* pMesh;
AEGfxTexture* chara{}, * rat{}, * big_rat_texture{}, * spell_g{}, * pause_box{}, * sub{}, * crafting_test{}, * bg{}, * end_turn_box{}, * mana_full{}, * mana_empty{}, * Menu_ui,
* base_mid_pipe, * base_cap_pipe, * unlocked_spell_slot, * fire_icon, * water_icon, * poison_icon, * shadow_icon, *tick_box[2], *toxic_deluge_icon, * inferno_blast_icon, * umbral_tendrils_icon, * maelstrom_surge_icon, * venemous_bite_icon,
* shadow_cloak_icon, * flame_burst_icon, * rat_swarm_icon, * bubonic_blaze_icon, *book_icon;

AEAudio gun, combi, death, whack;
AEAudio bgm;

AEAudioGroup base, bgm_g;


aabb* chara_pos;
aabb* Enemy_pos_1;
aabb* Enemy_pos_2;
/// <summary>

s32 pX{};
s32 pY{};

//Modes
bool alchemy_mode = 0;
bool pause_mode = false;
bool check_exit = false;
bool toggler = true;
bool sub_menu = false;
static bool fullscreen = true;

//Level Turn checks
Turn turn;
level_manager level;
bool transition = false;
const double transition_set_time = 1;
double transition_timer = 1;
std::string transition_text{};

//GameObject Creations
player* alchemice{};
Enemy enemies[3]{};

//Enemy Animations
AEGfxTexture* blast[4];
bool is_enemy_turn = false;
//specific enemy turn
int s_enemy_turn = 0;

//Bleeding Animation
bool enemy_bleeding{ false };
int bleeding_enemy_no{ 0 };

//Particles
AEGfxVertexList* particle_mesh;
particle_manager enemy_part_manager(50);
particle_manager crafting_part_manager(50);

//Button AABB
aabb pause_buttons[4];
aabb end_turn_button;

AEVec2 pause_scale{ 400,600 };
AEVec2 pause_button_scale{ 300,80 };
int pause_start_y = 190;
int pause_space_y = 120;
int pause_length = 300;
int pause_width = 80;

AEVec2 end_scale{ 180,300 };
AEVec2 end_mid{ 516,-308 };
int end_length = 200;
int end_width = 80;
int end_offset = FONT_SIZE / 3;

void GameStateAlchemiceLoad() {
	level.curr_level = level_enum::level_1;

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

	particle_mesh = 0;
	//Creating the particle object
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f);
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f);

	particle_mesh = AEGfxMeshEnd();

	chara = AEGfxTextureLoad("Assets/Art/char.png");
	rat = AEGfxTextureLoad("Assets/Art/Rat.png");
	big_rat_texture = AEGfxTextureLoad("Assets/Art/big_rat.png");
	sub = AEGfxTextureLoad("Assets/Art/submenu.png");
	pause_box = AEGfxTextureLoad("Assets/Art/pause_button.png");
	end_turn_box = AEGfxTextureLoad("Assets/Art/end_button.png");
	crafting_test = AEGfxTextureLoad("Assets/Art/copyright_table.png");
	bg = AEGfxTextureLoad("Assets/Art/background.png");
	mana_full = AEGfxTextureLoad("Assets/Art/mana_full.png");
	mana_empty = AEGfxTextureLoad("Assets/Art/mana_empty.png");

	base_mid_pipe = AEGfxTextureLoad("Assets/Art/midpipe.png");
	base_cap_pipe = AEGfxTextureLoad("Assets/Art/side_ui.png");
	unlocked_spell_slot = AEGfxTextureLoad("Assets/Art/box_ui.png");

	umbral_tendrils_icon = AEGfxTextureLoad("Assets/Art/umbral.png");
	inferno_blast_icon = AEGfxTextureLoad("Assets/Art/inferno_blast.png");
	toxic_deluge_icon = AEGfxTextureLoad("Assets/Art/toxic_deluge.png");
	maelstrom_surge_icon = AEGfxTextureLoad("Assets/Art/maelstrom_surge.png");
	venemous_bite_icon = AEGfxTextureLoad("Assets/Art/venemous_bite.png");
	shadow_cloak_icon = AEGfxTextureLoad("Assets/Art/shadow_cloak.png");
	flame_burst_icon = AEGfxTextureLoad("Assets/Art/flame_burst.png");
	rat_swarm_icon = AEGfxTextureLoad("Assets/Art/rat_swarm.png");
	bubonic_blaze_icon = AEGfxTextureLoad("Assets/Art/bubonic_blaze.png");


	blast[0] = AEGfxTextureLoad("Assets/Art/blast1.png");
	blast[1] = AEGfxTextureLoad("Assets/Art/blast2.png");
	blast[2] = AEGfxTextureLoad("Assets/Art/blast3.png");
	blast[3] = AEGfxTextureLoad("Assets/Art/blast4.png");

	//Icon Loading
	//load_enemy_texture();
	fire_icon = AEGfxTextureLoad("Assets/Art/fire_icon.png");
	water_icon = AEGfxTextureLoad("Assets/Art/water_icon.png");
	shadow_icon = AEGfxTextureLoad("Assets/Art/shadow_icon.png");
	poison_icon = AEGfxTextureLoad("Assets/Art/poison_icon.png");

	tick_box[0] = AEGfxTextureLoad("Assets/Art/tick_box_1.png");
	tick_box[1] = AEGfxTextureLoad("Assets/Art/tick_box_2.png");

	PositionInit();
	alchemice = create_player();

	bgm = AEAudioLoadMusic("Assets/Audio/bgm.wav");
	bgm_g = AEAudioCreateGroup();


	gun = AEAudioLoadSound("Assets/Audio/GUN-MUSKET_GEN-HDF-13603.wav");
	death = AEAudioLoadSound("Assets/Audio/fox.wav");
	whack = AEAudioLoadSound("Assets/Audio/smackwhack.wav");
	combi = AEAudioLoadSound("Assets/Audio/MagicCartoon CTE01_94.8.wav");
	base = AEAudioCreateGroup();


	//Init All Spells
	spellbook = init_all_spells();
	book_icon = AEGfxTextureLoad("Assets/Art/Spellbook.png");

	spellbook.init_spells_coords();
	AEAudioSetGroupVolume(bgm_g, (float)sound);
	AEAudioSetGroupVolume(base, (float)sound);
	AEAudioPlay(bgm, bgm_g, 1.0f, 1.0f, -1);
}

// Initialization of your own variables go here
void GameStateAlchemiceInit() {

	turn = Turn::player_turn;
	pause_mode = false;


	//creates the button from top to bottom top most button [0]
	for (int i = 0; i < sizeof(pause_buttons) / sizeof(pause_buttons[0]); ++i) {
		pause_buttons[i] = CreateAABB({ 0,(f32)-pause_start_y + i * pause_space_y }, pause_length, pause_width);
	}

	//cards.x = -50;
	end_turn_button = CreateAABB(end_mid, end_length, end_width);

	//Most stuff are only needed to be init in level 1;
	if (level.curr_level == level_enum::level_1)
	{

		enemies[0] = Enemy( rat, "Rat", 4, 1, FIRE);
		enemies[0].set_position_and_aabb(enemy_position[0]);

		enemies[1] = Enemy( rat, "Rat", 4, 1, WATER);
		enemies[1].set_position_and_aabb(enemy_position[1]);

		enemies[2] = Enemy( rat, "Rat", 4, 1, WATER);
		enemies[2].set_position_and_aabb(enemy_position[2]);

		level.display_level = "Level 1";
		alchemice->mp = 2;
		alchemice->max_mp = 2;
	}
	else if (level.curr_level == level_enum::level_2)
	{
		enemies[0] = Enemy(big_rat_texture, "Big Rat", 8, 3, SHADOW);
		enemies[0].set_position_and_aabb(enemy_position[0]);

		enemies[1] = Enemy( rat, "Rat", 4, 2, POISON);
		enemies[1].set_position_and_aabb(enemy_position[1]);

		enemies[2] = Enemy( rat, "Rat", 4, 2, FIRE);
		enemies[2].set_position_and_aabb(enemy_position[2]);

		level.display_level = "Level 2";
		alchemice->mp = 3;
		alchemice->max_mp = 3;
	}
	else if (level.curr_level == level_enum::level_3)
	{
		enemies[0] = Enemy( big_rat_texture, "Big Rat", 10, 3, POISON);
		enemies[0].set_position_and_aabb(enemy_position[0]);

		enemies[1] = Enemy( big_rat_texture, "Big Rat", 8, 2, SHADOW);
		enemies[1].set_position_and_aabb(enemy_position[1]);

		enemies[2] = Enemy( big_rat_texture, "Big Rat", 8, 2, SHADOW);
		enemies[2].set_position_and_aabb(enemy_position[2]);

		level.display_level = "Level 3";
		alchemice->mp = 4;
		alchemice->max_mp = 4;
	}
	bookaabb = CreateAABB(bookpos, bookscale.y, bookscale.y);
}


void GameStateAlchemiceUpdate() {
	AEAudioUpdate();
	AEVec2 temp;
	temp = mouse_pos;
	temp.y = mouse_pos.y;

	bool drag;

	drag = true;
	//Pause button, switch state of pause_mode
	if (AEInputCheckTriggered(AEVK_ESCAPE) && !transition) {
		pause_mode = !pause_mode;
	}

	if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		toggler = true;
	}
	

	for (int i{}; i < ARRAYSIZE(pause_buttons); ++i) //for every iteration of pause menu buttons
	{
		if (aabbbutton(&pause_buttons[i], mouse_pos) &&
			AEInputCheckTriggered(AEVK_LBUTTON) && //check if left button is clicked
			pause_mode == true && !check_exit) //only runs during pause mode
		{
			switch (i) {
			case 0:
				pause_mode = !pause_mode;
				break;
			case 1:
				check_exit = !check_exit;
				toggler = false;
				////to be implemented when options is up
				break;
			case 2:
				sound = !sound;
				AEAudioSetGroupVolume(bgm_g, (float)sound);
				AEAudioSetGroupVolume(base, (float)sound);
				break;
			case 3:
				fullscreen = !fullscreen;
				AESysToggleFullScreen(fullscreen);
				break;
			}
		}
	}

	if (check_exit && toggler)
	{
		if(AEInputCheckTriggered(AEVK_LBUTTON))
		if (aabbbutton(&pause_buttons[1], mouse_pos)) //check if left button is clicked
		{
			gGameStateNext = GS_MENU;

		}
		else
		{
			check_exit = !check_exit;

		}
	}

	//Have to check if the player or enemies are all dead
	bool enemies_alive = false;
	for (int i{}; i < TOTAL_ENEMY; i++) {
		if (enemies[i].is_alive()) {
			enemies_alive = true;
		}
	}

	//CHEAT BUTTON
	if (AEInputCheckTriggered(AEVK_F1)) {
		enemies_alive = false;
	}

	//TESTING PARTICLE SYSTEM
	//Particle System Logic/ To spawn a particle each turn.
	for (int i{}; i < TOTAL_ENEMY; i++) {
		if (enemies[i].is_bleeding() == true)
		{
			create_particle(enemy_part_manager.particle_vector, enemy_part_manager.max_capacity, enemies[i].get_pos(), enemy_take_damage_particle);
			enemies[i].update_bleed_timer();
			if (enemies[i].get_bleed_timer() <= 0) {
				enemies[i].reset_bleed_time();
				//f64 j = enemies[i].get_bleed_timer();
				enemies[i].set_bleeding(false);
			}
		}
	}

	//Particles Update
	update_particle(enemy_part_manager.particle_vector);
	update_particle(crafting_part_manager.particle_vector);
	rotation_about_time += (f32)g_dt * FRAMERATE;

	//MAIN GAMEPLAY LOOP
	//Check if players or enemies or all enemies are all dead
	if (alchemice->hp > 0 && enemies_alive && !pause_mode && transition == false) {
		//Checking for turns
		if (turn == Turn::player_turn) {

			if (AEInputCheckCurr(AEVK_LBUTTON))
			{
				for (int i = 0; i <= max_spells; i++)
				{
					if (spellbook.spell_array[i].unlocked == true) {
						if (aabbbutton(spellbook.spell_array[i].spell_dragdrop, mouse_pos)
							&& !crafting_table.get_flag())
						{
							for (int j = 0; j <= max_spells; j++)
							{
								if (spellbook.spell_array[j].spell_dragdrop->getmouse())
								{
									drag = false;
								}
							}
							if (drag)
							{
								spellbook.spell_array[i].spell_dragdrop->mousechange(true);
							}
						}
					}
				}
			}

			/*crafting_table.get_spell2() != spellbook.spell_array[i].id
				&& crafting_table.get_spell1() != spellbook.spell_array[i].id*/
			for (int i = 0; i <= max_spells; i++)
			{
				if (spellbook.spell_array[i].spell_dragdrop->getmouse())
				{
					spellbook.spell_array[i].spell_dragdrop->moveto(temp);
				}
			}

			if (AEInputCheckReleased(AEVK_LBUTTON))
			{
				for (int i = 0; i < max_spells; i++)
				{
					for (int j = 0; j < TOTAL_ENEMY; ++j)
					{
						if (aabbbutton(spellbook.spell_array[i].spell_dragdrop, enemies[j].get_aabb()) != -1)
						{
							if (enemies[j].is_alive() && alchemice->mp > 0)
							{
								if (spellbook.spell_array[i].id > tier3_last) {
									spellbook.spell_array[i].unlocked = false;
								}
								crafting_table.reset_spells();
								enemies[j].take_damage(spellbook.spell_array[i].base_damage, static_cast<Elements>(spellbook.spell_array[i].element));
								if (enemies[j].get_hp() <= 0)
								{
									AEAudioPlay(death, base, 1.0f, 0.6f, 0);

								}
								enemies[j].set_bleeding(true);
								alchemice->mp -= 1;
							}
						}
					}


					if (spellbook.spell_array[i].spell_dragdrop->getmouse())
					{
						if (spellbook.spell_array[i].id == crafting_table.get_spell1()) {
							crafting_table.crafting_table_snap(spellbook, spellbook.spell_array[i].id);
							spellbook.spell_array[i].spell_dragdrop->mousechange(true);
						}
						if (aabbbutton(crafting_table.get_dragdrop(), spellbook.spell_array[i].spell_dragdrop) == 1 && alchemice->mp > 0) {
							crafting_table.crafting_table_snap(spellbook, spellbook.spell_array[i].id);
						}
						else {
							if (crafting_table.get_spell1() == spellbook.spell_array[i].id) {
								crafting_table.reset_spells();
							}
							spellbook.spell_array[i].spell_dragdrop->resetaabb();
							spellbook.spell_array[i].spell_dragdrop->mousechange(false);
						}
					}
				}
			}

			if (crafting_table.get_flag()) {
				if (crafting_table.crafting_table_update(spellbook) == 2) {
					alchemice->mp -= 1;
					AEAudioPlay(combi, base, 1.0f, 1.0f, 0);
				}
			}

			//Check for mouse click
			if (AEInputCheckTriggered(AEVK_LBUTTON))
			{
				if (aabbbutton(&end_turn_button, mouse_pos)) {
					turn = Turn::enemy_turn;
					s_enemy_turn = 0;
					is_enemy_turn = true;
					level.display_turn = "Enemy's Turn";
				}

			}//Check for Lbutton click

			//Opening sub menu
			if (AEInputCheckTriggered(AEVK_W))
			{
				sub_menu = !sub_menu;
			}
			if (sub_menu && AEInputCheckTriggered(AEVK_LBUTTON) && click_offset <= 0) {
					sub_menu = false;
					click_offset = 0.1;
			}
			if (aabbbutton(&bookaabb, mouse_pos) && AEInputCheckTriggered(AEVK_LBUTTON) && click_offset <= 0) {
				sub_menu = true;
				click_offset = 0.1;
			}

		}//End of player turn logic

		//Enemy turn; runs all the enemy functions and animations
		else if (turn == Turn::enemy_turn)
		{
			//Enemy turn duration
			//curr_time -= g_dt;

			//When turn ends
			if (is_enemy_turn == false) {
				turn = Turn::player_turn;
				level.display_turn = "Player's Turn";

				//Player Mana System
				alchemice->max_mp = (alchemice->max_mp == 5) ? 5 : alchemice->max_mp + 1;
				alchemice->mp = alchemice->max_mp;
			}
			else
			{
				if (s_enemy_turn < TOTAL_ENEMY)
				{
					//Is a one time check when it becomes enemy then run animations
					if (enemies[s_enemy_turn].get_finish_attack())
					{

						alchemice->hp -= enemies[s_enemy_turn].get_atk();

						//Do Damage number to alchemice;
						enemies[s_enemy_turn].set_p_damage_num_str(std::to_string(enemies[s_enemy_turn].get_atk()));
						enemies[s_enemy_turn].set_p_bool_damage_num(true);

						enemies[s_enemy_turn].switch_finish_attack();
						enemies[s_enemy_turn].set_audio(false);

						s_enemy_turn++;
					}
					else
					{
						//To update animations(it will auto switch)
						if (enemies[s_enemy_turn].is_alive())
						{
							if (enemies[s_enemy_turn].get_name() == "Big Rat")
							{

								if (!enemies[s_enemy_turn].get_audio())
								{
									AEAudioPlay(gun, base, 1.0f, 1.0f, 0);
									enemies[s_enemy_turn].set_audio(true);
								}

							}
							else if (enemies[s_enemy_turn].get_name() == "Rat")
							{
								if (!enemies[s_enemy_turn].get_audio())
								{
									AEAudioPlay(whack, base, 0.6f, 1.0f, 0);
									enemies[s_enemy_turn].set_audio(true);
								}
							}
							//update_animation will switch enemy object's animation to be finished when it ends.
							enemies[s_enemy_turn].update_animation(g_dt);
						}
						else
						{
							s_enemy_turn++;
						}
					}
				}
				else
				{
					is_enemy_turn = false;
				}
			}
		}//End of enemy_turn logic
	}//End of Main Gameplay Loop.
	else if (!enemies_alive && !transition) {
		if (level.curr_level != level_enum::level_3) {
			transition_timer = transition_set_time;
			transition_text = "";
			transition = true;
		}
		else
			gGameStateNext = GS_VICTORY;
	}
	else if (alchemice->hp <= 0) {
		gGameStateNext = GS_GAMEOVER;
		AEAudioStopGroup(bgm_g);
	}
	if (transition) {
		transition_timer -= g_dt;
		if (transition_timer < 0) {
			level_transition(level.curr_level, abs(transition_timer), transition_text, transition);
		}
		if (!transition) {
			level.next_level();
			gGameStateNext = GS_RESTART;
		}
	}
	click_offset -= g_dt;
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

	if (transition) {
		AEGfxSetBackgroundColor(.0f, .0f, .0f);
		if (transition_timer > 0) {
			AEGfxSetTransparency((f32)transition_timer);
		}
		else {
			AEGfxSetTransparency(0.0f);
		}
	}
	else
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
	if (!transition) {
		AEGfxPrint(font, (s8*)level.display_turn.c_str(), -.1f, .9f, 1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxPrint(font, (s8*)level.display_level.c_str(), -.9f, .9f, 1.0f, 1.0f, 1.0f, 1.0f);
	}

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

	if (!transition) {
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
		name_bar(player_hp, player_position);
	}

	for (int i{}; i < alchemice->max_mp; ++i) {
		AEVec2 mana_draw_position{ (f32)(-AEGetWindowWidth() / 2.5) + (i * 40), (f32)(-AEGetWindowHeight() / 4) };
		AEGfxTextureSet(mana_full, 0, 0);
		AEMtx33Trans(&translate, mana_draw_position.x, mana_draw_position.y);
		AEMtx33Rot(&rotate, 0);
		AEMtx33Scale(&scale, 32.f, 32.f);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		if (alchemice->mp < alchemice->max_mp) {
			for (int j{ alchemice->mp }; j < alchemice->max_mp; ++j) {
				AEGfxTextureSet(mana_empty, 0, 0);
				AEVec2 mana_draw_position_empty{ (f32)(-AEGetWindowWidth() / 2.5) + (j * 40), (f32)(-AEGetWindowHeight() / 4) };
				AEMtx33Trans(&translate, mana_draw_position_empty.x, mana_draw_position_empty.y);
				AEMtx33Concat(&transform, &rotate, &scale);
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);
				AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
			}
		}
	}

	//Spell Slot Drawing
	draw_base_spell_slots(pMesh, base_mid_pipe, base_cap_pipe);
	draw_unlocked_spell_slots(pMesh, spellbook, unlocked_spell_slot);
	draw_spellbook(pMesh, book_icon, bookpos, bookscale);

	//Crafting Table
	draw_crafting_table(pMesh, crafting_table, crafting_part_manager, enemy_take_damage_particle, crafting_test);

	//Card Drawing
	spellbook.draw_all_spells(pMesh);

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

			if (!transition)
				enemy_info(enemies[i], pMesh);

			//Choosing Icon
			AEGfxTexture* element;

			switch (enemies[i].get_element())
			{
			case WATER:
				element = water_icon;
				break;
			case POISON:
				element = poison_icon;
				break;
			case SHADOW:
				element = shadow_icon;
				break;

			case FIRE:
				element = fire_icon;
				break;
			default:
				element = water_icon;
			}
			//Drawing Icon
			AEGfxTextureSet(element, 0, 0);
			AEMtx33Trans(&translate, (f32)(enemies[i].get_element_icon_pos().x), (f32)(enemies[i].get_element_icon_pos().y));
			AEMtx33Rot(&rotate, 0);
			AEMtx33Scale(&scale, 25.f, 25.f);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		}
	}

	//Damage Numbers Drawing
	for (int i = 0; i < TOTAL_ENEMY; i++)
	{
		if (enemies[i].get_bool_damage_num())
		{
			enemies[i].update_damage_timer();
			AEGfxPrint(font, (s8*)enemies[i].get_str_damage_number().c_str(), enemies[i].get_str_damage_pos_percent().x, enemies[i].get_str_damage_pos_percent().y, 1.0f, 1.0f, enemies[i].get_crit_colour(), enemies[i].get_crit_colour());
		}

		if (enemies[i].get_p_bool_damage_num())
		{
			AEGfxPrint(font, (s8*)enemies[i].get_p_damage_num_str().c_str(), enemies[i].get_p_damage_num_percent_pos().x, enemies[i].get_p_damage_num_percent_pos().y, 1.0f, 1.0f, 1.0f, 1.0f);
			enemies[i].update_p_damage_timer();
		}
	}


	//Particles Drawing
	draw_particles(enemy_part_manager.particle_vector, particle_mesh, mana_empty);
	draw_particles(crafting_part_manager.particle_vector, particle_mesh, blast[2]);

	


	// End turn button
	// 85 characters on screen, start to end, 85/2 =  42.5(left and right for scaling) Gothic
	// 1280W,720H, 640/HalfWidth, 360/HalfHeight
	const char* End_Turn_Text{ "End Turn" };
	f32 middle = (end_turn_button.mid.x / (AEGetWindowWidth() / 2));
	f32 offset = -((float)strlen(End_Turn_Text) / 2) / (AEGetWindowWidth() / FONT_SIZE);
	AEGfxTextureSet(end_turn_box, 0.f, 0.f);
	AEMtx33Trans(&translate, end_turn_button.mid.x, -end_turn_button.mid.y + end_offset);
	AEMtx33Rot(&rotate, 0);
	AEMtx33Scale(&scale, end_scale.x, end_scale.y);
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
	if (!transition)
		AEGfxPrint(font, (s8*)End_Turn_Text, middle + offset, (f32)-(end_turn_button.mid.y / (AEGetWindowHeight() / 2)), 1, 0, 0, 0);


	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	if (sub_menu)
	{
		sub_menu_draw(sub, spellbook, pMesh);
	}

	if (pause_mode) {
		AEGfxTextureSet(pause_box, 0, 0);
		AEMtx33Trans(&translate, 0, 0);
		AEMtx33Rot(&rotate, 0);
		AEMtx33Scale(&scale, pause_scale.x, pause_scale.y);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);


		const char* Pause_Text[4]{ { "Continue" }, {"Main Menu"}, {"Sound"},{"Fullscreen"}};

		for (int i = 0; i < ARRAYSIZE(Pause_Text); ++i) {
			f32 pause_middle = -(((float)strlen(Pause_Text[i]) / 2) / (AEGetWindowWidth() / FONT_SIZE));
			f32 textY = (float)((float)(AEGetWindowHeight() - i * AEGetWindowHeight()) / (ARRAYSIZE(pause_buttons) - 1) + pause_space_y) / AEGetWindowHeight();			
			f32 boxY = (float)(pause_start_y - i * pause_space_y);
			AEGfxTextureSet(pause_box, 0.f, 0.f);
			AEMtx33Trans(&translate, 0, boxY);
			AEMtx33Rot(&rotate, 0);
			AEMtx33Scale(&scale, pause_button_scale.x, pause_button_scale.y);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
			AEGfxPrint(font, (s8*)Pause_Text[i], pause_middle, textY, 1, 0, 0, 0);

			if (i == 2 || i == 3)
			{
				AEGfxTextureSet(tick_box[(i == 2) ? sound : fullscreen], 0, 0);
				AEMtx33Trans(&translate, -120, boxY);
				AEMtx33Rot(&rotate, 0);
				AEMtx33Scale(&scale, pause_button_scale.x/6, pause_button_scale.x/4);
				AEMtx33Concat(&transform, &rotate, &scale);
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);
				AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
				AEGfxPrint(font, (s8*)Pause_Text[i], pause_middle, textY, 1, 0, 0, 0);
			}

		}
		
	}

	if (check_exit)
	{
		AEGfxTextureSet(pause_box, 0, 0);
		AEMtx33Trans(&translate, 0, 0);
		AEMtx33Rot(&rotate, 0);
		AEMtx33Scale(&scale, pause_scale.x, pause_scale.y);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES); 

		const char* check[3]{ { "Exit?" }, { "Yes" }, {"No" } };
		for (int i = 0; i < ARRAYSIZE(check); ++i) {
			f32 middle_pause = -(((float)strlen(check[i]) / 2) / (AEGetWindowWidth() / FONT_SIZE));
			f32 textY = (float)((float)(AEGetWindowHeight() - i * AEGetWindowHeight()) / (ARRAYSIZE(pause_buttons) - 1) + pause_space_y) / AEGetWindowHeight();			
			f32 boxY = (float)(pause_start_y - i * pause_space_y);
			AEGfxTextureSet(pause_box, 0.f, 0.f);
			AEMtx33Trans(&translate, 0, boxY);
			AEMtx33Rot(&rotate, 0);
			if (i == 0)
			{
				AEMtx33Scale(&scale, 0, 0);
			}
			else
			{
				AEMtx33Scale(&scale, pause_button_scale.x, pause_button_scale.y);
			}
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
			AEGfxPrint(font, (s8*)check[i], middle_pause, textY, 1, 0, 0, 0);

		}
	}
	
}

void GameStateAlchemiceFree() {
	if (!(gGameStateNext == GS_RESTART))
	{
		AEAudioStopGroup(bgm_g);
		AEAudioStopGroup(base);
	}

}

void GameStateAlchemiceUnload() {
	delete_player(alchemice);

	//Character texture
	AEGfxTextureUnload(chara);
	AEGfxTextureUnload(rat);
	AEGfxTextureUnload(big_rat_texture);

	//UI
	AEGfxTextureUnload(sub);
	AEGfxTextureUnload(pause_box);
	AEGfxTextureUnload(end_turn_box);
	AEGfxTextureUnload(crafting_test);
	AEGfxTextureUnload(bg);
	AEGfxTextureUnload(mana_full);
	AEGfxTextureUnload(mana_empty);
	
	//Unload all spells in spellbook
	spellbook.unload_spells();
	AEGfxTextureUnload(book_icon);

	//Unloads spell icons used in known spell list
	AEGfxTextureUnload(umbral_tendrils_icon);
	AEGfxTextureUnload(inferno_blast_icon);
	AEGfxTextureUnload(toxic_deluge_icon);
	AEGfxTextureUnload(maelstrom_surge_icon);
	AEGfxTextureUnload(venemous_bite_icon);
	AEGfxTextureUnload(shadow_cloak_icon);
	AEGfxTextureUnload(flame_burst_icon);
	AEGfxTextureUnload(rat_swarm_icon);
	AEGfxTextureUnload(bubonic_blaze_icon);

	//Animations
	AEGfxTextureUnload(blast[0]);
	AEGfxTextureUnload(blast[1]);
	AEGfxTextureUnload(blast[2]);
	AEGfxTextureUnload(blast[3]);

	//Spell Slot 
	AEGfxTextureUnload(base_mid_pipe);
	AEGfxTextureUnload(base_cap_pipe);
	AEGfxTextureUnload(unlocked_spell_slot);

	//Elemental Icons
	AEGfxTextureUnload(fire_icon);
	AEGfxTextureUnload(water_icon);
	AEGfxTextureUnload(shadow_icon);
	AEGfxTextureUnload(poison_icon);
	//unload_enemy_texture();

	AEGfxTextureUnload(tick_box[0]);
	AEGfxTextureUnload(tick_box[1]);

	AEGfxMeshFree(pMesh);
	AEGfxMeshFree(particle_mesh);
}
