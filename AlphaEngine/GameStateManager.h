/******************************************************************************/
/*!
\file		GaneStateManager.h
\author 	Liang HongJie
\par    	email: l.hongjie\@digipen.edu
\brief		Defines for Global state variables as well as enum for states.
			Declares Init and Update function of GameStateManager.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/


#pragma once
#include "Main.h"

enum
{
	// list of all game states
	GS_LOAD = 0,
	GS_ALCHEMICE,
	GS_MENU,
	GS_RESTART,
	GS_VICTORY,
	GS_GAMEOVER,
	GS_TUTORIAL,
	GS_QUIT,
	GS_CREDITS,
};

extern unsigned int gGameStateInit;
extern unsigned int gGameStateCurr;
extern unsigned int gGameStatePrev;
extern unsigned int gGameStateNext;

extern void (*GameStateLoad)();
extern void (*GameStateInit)();
extern void (*GameStateUpdate)();
extern void (*GameStateDraw)();
extern void (*GameStateFree)();
extern void (*GameStateUnload)();

void GameStateManagerInit(unsigned int gameStateInit);
void GameStateManagerUpdate();
