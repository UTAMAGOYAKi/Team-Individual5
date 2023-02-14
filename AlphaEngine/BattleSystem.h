#pragma once
#include "AEEngine.h"

typedef struct position {
	float x, y;
}position;

extern position player_position;
extern position enemy_position[3];

void LevelManagerInit();