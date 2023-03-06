#pragma once
#include "Main.h"

//Reference for controls
//Q - basic attack against first rat
//W - start alchemy
//Z - check for mouse position
//X - cancel alchemy
//E - in alchemy, try combination
//drag& drop fire to left spell slot of glyth
//poison on right
//burn can be placed on either rat, but second rat has no hp

// ---------------------------------------------------------------------------

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//enum spell_slot {empty, fire_slot, poison_slot, lighting_slot};
	//Elements spell_slot_one = NILL;
	//Elements spell_slot_two = NILL;
	//int gGameRunning = 1;

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1280, 720, 1, 60, true, NULL);
	AESysToggleFullScreen(false);

	// Changing the window title
	AESysSetWindowTitle("Alchemy Main");

	GSMInit(GS_LOAD);

	font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", 26);

	// Game Loop
	while (gGameStateCurr != GS_QUIT)
	{
		// reset the system modules
		AESysReset();

		if (gGameStateCurr != GS_RESTART) {
			GSMUpdate();
			GSLoad();
		}
		else
			gGameStateNext = gGameStateCurr = gGameStatePrev;

		GSInit();

		while (gGameStateCurr == gGameStateNext)
		{
			// Informing the system about the loop's start
			AESysFrameStart();

			// Handling Input
			AEInputUpdate();

			GSUpdate();

			GSDraw();

			AESysFrameEnd();

			if (AESysDoesWindowExist() == false)
				gGameStateNext = GS_QUIT;
		}
		GSFree();

		if (gGameStateNext != GS_RESTART) {
			GSUnload();
		}

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}

	AEGfxDestroyFont(font);

	AESysExit();
}