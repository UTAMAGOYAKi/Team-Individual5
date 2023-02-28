#pragma once
#include "Main.h"

unsigned int	gGameStateInit;
unsigned int	gGameStateCurr;
unsigned int	gGameStatePrev;
unsigned int	gGameStateNext;

void (*GSLoad)()	= 0; 
void (*GSInit)()	= 0;
void (*GSUpdate)()	= 0;
void (*GSDraw)()	= 0;
void (*GSFree)()	= 0;
void (*GSUnload)()	= 0;

void GSMInit(unsigned int gameStateInit) {
	// set the initial game state
	gGameStateInit = gameStateInit;

	// reset the current, previoud and next game
	gGameStateCurr = gGameStateInit;
	gGameStatePrev = gGameStateInit;
	gGameStateNext = gGameStateInit;

	// call the update to set the function pointers
	GSMUpdate();
}

void GSMUpdate() {

	if ((gGameStateCurr == GS_RESTART) || (gGameStateCurr == GS_QUIT))
		return;

	switch (gGameStateCurr)
	{
		case GS_LOAD:
			GSLoad = LoadScreenLoad;
			GSInit = LoadScreenInit;
			GSUpdate = LoadScreenUpdate;
			GSDraw = LoadScreenDraw;
			GSFree = LoadScreenFree;
			GSUnload = LoadScreenUnload;
		break;
		case GS_ALCHEMICE:
			GSLoad = GameStateAlchemiceLoad;
			GSInit = GameStateAlchemiceInit;
			GSUpdate = GameStateAlchemiceUpdate;
			GSDraw = GameStateAlchemiceDraw;
			GSFree = GameStateAlchemiceFree;
			GSUnload = GameStateAlchemiceUnload;
			break;
		case GS_RESTART:
			break;
		case GS_QUIT:
			break;
		default:
			//AE_FATAL_ERROR("invalid state!!");
			break;
	}
}