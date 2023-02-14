#include "Main.h"

position enemy_position[3];
position player_position;

void LevelManagerInit() {
	player_position.x = (float)(-(AEGetWindowWidth() / 4)); 
	player_position.y = 0;// (float)-(AEGetWindowHeight() / 8);
	enemy_position[0].x = (float)((9.0/16.0) * (AEGetWindowWidth()/2));
	enemy_position[0].y = 0;
	enemy_position[1].x = (float)((6.0 / 16.0) * (AEGetWindowWidth() / 2));
	enemy_position[1].y = 0;
	enemy_position[2].x = (float)((12.0 / 16.0) * (AEGetWindowWidth() / 2));
	enemy_position[2].y = 0;
}


