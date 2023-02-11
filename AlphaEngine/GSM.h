#pragma once

#include "AEEngine.h"
//#include "GameStateList.h"
enum
{
	// list of all game states 
	GS_ALCHEMICE = 0,

	// special game state. Do not change
	GS_RESTART,
	GS_QUIT,
	GS_NONE
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

void GSMInit(unsigned int);
void GSMUpdate();
