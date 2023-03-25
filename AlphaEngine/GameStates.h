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
	
	void next_level() {
		curr_level = static_cast<level_enum>(static_cast<int>(curr_level) + 1);
		//curr_level = (curr_level == level_1) ? level_2 : (curr_level == leve)
	}
};

void GameStateAlchemiceLoad();
void GameStateAlchemiceInit();
void GameStateAlchemiceUpdate();
void GameStateAlchemiceDraw();
void GameStateAlchemiceFree();
void GameStateAlchemiceUnload();