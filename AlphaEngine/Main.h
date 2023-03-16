#pragma once

#include "AEEngine.h"
#include "Math.h"

#include "Battle_system.h"
#include "Buttons.h"
#include "Credits.h"
#include "Elements.h"
#include "EnemyObject.h"
#include "GameStateManager.h"
#include "GameStates.h"
#include "LoadScreen.h"
#include "MainMenu.h"
#include "Mesh.h"
#include "Player.h"
#include "Spells.h"

#include <iostream>
#include <fstream>
#include <string>

extern int FONT_SIZE;
extern const u32 FRAMERATE;
extern s8 font;
extern AEVec2 mouse_pos;
extern f64 g_dt;


#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))
#endif // !
