#include "Main.h"

position enemy_position[3];
position player_position;

void LevelManagerInit() {
	player_position.x = (float)(-(AEGetWindowWidth() / 4)); 
	player_position.y = 0;// (float)-(AEGetWindowHeight() / 8);
	enemy_position[0].x = (float)((4 * AEGetWindowWidth()) / 16);
	enemy_position[0].y = 0;
	enemy_position[1].x = (float)((5.5 * AEGetWindowWidth()) / 16);
	enemy_position[1].y = 0;
	enemy_position[2].x = (float)((7 * AEGetWindowWidth()) / 16);
	enemy_position[2].y = 0;
}




