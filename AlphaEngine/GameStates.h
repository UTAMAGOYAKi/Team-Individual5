#pragma once

enum Turn {
	player_turn,
	enemy_turn
};

enum level_enum {
	level_1 = 1,
	level_2,
	level_3,
};

struct level_manager {
	level_enum curr_level = level_1;
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