/******************************************************************************/
/*!
\file		GaneStateManager.cpp
\author 	Liang HongJie
\par    	email: l.hongjie\@digipen.edu
\brief		Defines functions for GameStateManager.
			Update function is to change the function pointer to point to its
			respective function of the game state.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once
#include "Main.h"

//Game states
unsigned int	gGameStateInit;
unsigned int	gGameStateCurr;
unsigned int	gGameStatePrev;
unsigned int	gGameStateNext;

//Function pointers
void (*GameStateLoad)()	= 0; 
void (*GameStateInit)()	= 0;
void (*GameStateUpdate)()	= 0;
void (*GameStateDraw)()	= 0;
void (*GameStateFree)()	= 0;
void (*GameStateUnload)()	= 0;

/*
	Init function of GameStateManager
*/
void GameStateManagerInit(unsigned int gameStateInit) {
	// set the initial game state
	gGameStateInit = gameStateInit;

	// reset the current, previoud and next game
	gGameStateCurr = gGameStateInit;
	gGameStatePrev = gGameStateInit;
	gGameStateNext = gGameStateInit;

	// call the update to set the function pointers
	GameStateManagerUpdate();
}

/*
	Update function of GameStateManager

	Function changes function pointer to point to respective game state function calls.

	These function pointers will then be called in Main.cpp.
*/
void GameStateManagerUpdate() {
	if ((gGameStateCurr == GS_RESTART) || (gGameStateCurr == GS_QUIT))
		return;

	switch (gGameStateCurr)
	{
		case GS_LOAD:
			GameStateLoad	= LoadScreenLoad;
			GameStateInit	= LoadScreenInit;
			GameStateUpdate = LoadScreenUpdate;
			GameStateDraw	= LoadScreenDraw;
			GameStateFree	= LoadScreenFree;
			GameStateUnload = LoadScreenUnload;
		break;
		case GS_ALCHEMICE:
			GameStateLoad	= GameStateAlchemiceLoad;
			GameStateInit	= GameStateAlchemiceInit;
			GameStateUpdate = GameStateAlchemiceUpdate;
			GameStateDraw	= GameStateAlchemiceDraw;
			GameStateFree	= GameStateAlchemiceFree;
			GameStateUnload = GameStateAlchemiceUnload;
			break;
		case GS_MENU:
			GameStateLoad	= MenuLoad;
			GameStateInit	= MenuInit;
			GameStateUpdate = MenuUpdate;
			GameStateDraw	= MenuDraw;
			GameStateFree	= MenuFree;
			GameStateUnload = MenuUnload;
			break;
		case GS_TUTORIAL:
			GameStateLoad	= TutorialLoad;
			GameStateInit	= TutorialInit;
			GameStateUpdate = TutorialUpdate;
			GameStateDraw	= TutorialDraw;
			GameStateFree	= TutorialFree;
			GameStateUnload = TutorialUnload;
			break;
		case GS_CREDITS:
			GameStateLoad	= CreditsLoad;
			GameStateInit	= CreditsInit;
			GameStateUpdate = CreditsUpdate;
			GameStateDraw	= CreditsDraw;
			GameStateFree	= CreditsFree;
			GameStateUnload = CreditsUnload;
			break;
		case GS_GAMEOVER:
			GameStateLoad	= GameOverLoad;
			GameStateInit	= GameOverInit;
			GameStateUpdate	= GameOverUpdate;
			GameStateDraw	= GameOverDraw;
			GameStateFree	= GameOverFree;
			GameStateUnload	= GameOverUnload;
			break;
		case GS_VICTORY:
			GameStateLoad = GameOverLoad;
			GameStateInit = GameOverInit;
			GameStateUpdate = GameOverUpdate;
			GameStateDraw = VictoryDraw;
			GameStateFree = GameOverFree;
			GameStateUnload = GameOverUnload;
			break;
		case GS_RESTART:
			break;
		case GS_QUIT:
			break;
		case GS_OPTIONS:
			GameStateLoad = GameOverLoad;
			GameStateInit = GameOverInit;
			GameStateUpdate = GameOverUpdate;
			GameStateDraw = VictoryDraw;
			GameStateFree = GameOverFree;
			GameStateUnload = GameOverUnload;
			break;
		default:
			break;
	}
}