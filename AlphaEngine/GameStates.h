#pragma once

enum Turn {
	player_turn,
	enemy_turn
};

struct Level {
	std::string display_turn = "Player's Turn";
};
extern s8 font;

void GameStateAlchemiceLoad();
void GameStateAlchemiceInit();
void GameStateAlchemiceUpdate();
void GameStateAlchemiceDraw();
void GameStateAlchemiceFree();
void GameStateAlchemiceUnload();

void LoadScreenLoad();
void LoadScreenInit();
void LoadScreenUpdate();
void LoadScreenDraw();
void LoadScreenFree();
void LoadScreenUnload();

void Menuload();
void Menuinit();
void Menuupdate();
void Menudraw();
void Menufree();
void Menuunload();