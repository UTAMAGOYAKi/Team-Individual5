/******************************************************************************/
/*!
\file		GameStates.h
\project	Alchemice
\author 	Yeo Jun Jie(75%), Liang HongJie(25%)
\par    	email: yeo.junjie\@digipen.edu, l.hongjie\@digipen.edu,
\brief		Function declaration for Game as well as define Enum used within Game loop

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once

enum class Turn {
	player_turn,
	enemy_turn
};

enum class level_enum {
	
	level_1 = 1,
	level_2,
	level_3,
};

struct level_manager {
	level_enum curr_level = level_enum::level_1;
	std::string display_turn = "Player's Turn";
	std::string display_level = "Level 1";

	void next_level() {
		curr_level = static_cast<level_enum>(static_cast<int>(curr_level) + 1);
	}
};

void GameStateAlchemiceLoad();
void GameStateAlchemiceInit();
void GameStateAlchemiceUpdate();
void GameStateAlchemiceDraw();
void GameStateAlchemiceFree();
void GameStateAlchemiceUnload();