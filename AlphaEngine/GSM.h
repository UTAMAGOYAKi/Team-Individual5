#pragma once
#include "Main.h"
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

extern void (*GSLoad)();
extern void (*GSInit)();
extern void (*GSUpdate)();
extern void (*GSDraw)();
extern void (*GSFree)();
extern void (*GSUnload)();

void GSMInit(unsigned int gameStateInit);
void GSMUpdate();
