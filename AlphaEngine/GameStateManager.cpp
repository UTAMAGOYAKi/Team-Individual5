#pragma once
#include "Main.h"

unsigned int	gGameStateInit;
unsigned int	gGameStateCurr;
unsigned int	gGameStatePrev;
unsigned int	gGameStateNext;

void (*GameStateLoad)()	= 0; 
void (*GameStateInit)()	= 0;
void (*GameStateUpdate)()	= 0;
void (*GameStateDraw)()	= 0;
void (*GameStateFree)()	= 0;
void (*GameStateUnload)()	= 0;

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

void GameStateManagerUpdate() {

	if ((gGameStateCurr == GS_RESTART) || (gGameStateCurr == GS_QUIT))
		return;

	switch (gGameStateCurr)
	{
		case GS_LOAD:
			GameStateLoad = LoadScreenLoad;
			GameStateInit = LoadScreenInit;
			GameStateUpdate = LoadScreenUpdate;
			GameStateDraw = LoadScreenDraw;
			GameStateFree = LoadScreenFree;
			GameStateUnload = LoadScreenUnload;
		break;
		case GS_ALCHEMICE:
			GameStateLoad = GameStateAlchemiceLoad;
			GameStateInit = GameStateAlchemiceInit;
			GameStateUpdate = GameStateAlchemiceUpdate;
			GameStateDraw = GameStateAlchemiceDraw;
			GameStateFree = GameStateAlchemiceFree;
			GameStateUnload = GameStateAlchemiceUnload;
			break;
		case GS_MENU:
			GameStateLoad = Menuload;
			GameStateInit = Menuinit;
			GameStateUpdate = Menuupdate;
			GameStateDraw = Menudraw;
			GameStateFree = Menufree;
			GameStateUnload = Menuunload;
			break;
		case GS_RESTART:
			break;
		case GS_QUIT:
			break;
		default:
			break;
	}
}