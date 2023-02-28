#pragma once

enum Turn {
	player_turn,
	enemy_turn
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