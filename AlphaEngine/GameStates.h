#pragma once

enum Turn {
	player_turn,
	enemy_turn
};

struct Level {
	std::string display_turn = "Player's Turn";
};

void GameStateAlchemiceLoad();
void GameStateAlchemiceInit();
void GameStateAlchemiceUpdate();
void GameStateAlchemiceDraw();
void GameStateAlchemiceFree();
void GameStateAlchemiceUnload();