/******************************************************************************/
/*!
\file		Main.h
\project	Alchemice
\author 	TeamIndividual5
\brief		Global variables and all header files included here.
			Macro ARRAYSIZE defined here.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <assert.h>
#include <string>

#include "AEEngine.h"
#include "Math.h"
#include "Elements.h"
#include "Buttons.h"
#include "Credits.h"
#include "EnemyObject.h"
#include "GameOver.h"
#include "GameStateManager.h"
#include "GameStates.h"
#include "LoadScreen.h"
#include "MainMenu.h"
#include "Player.h"
#include "Particles.h"
#include "Tutorial.h"
#include "Spells.h"
#include "Crafting.h"
#include "UI.h"

extern int FONT_SIZE;
extern const u32 FRAMERATE;
extern s8 font;
extern AEVec2 mouse_pos;
extern f64 g_dt;
extern double click_offset;
// crafting table timer for combination spell delay
extern f64 timer;
extern bool sound;

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))
#endif
