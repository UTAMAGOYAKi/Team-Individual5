#pragma once
#include "Main.h"

int FONT_SIZE = 30;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//Mem check
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1280, 720, 1, 60, true, NULL);
	AESysToggleFullScreen(false);

	// Changing the window title
	AESysSetWindowTitle("Alchemy Main");

	GameStateManagerInit(GS_LOAD);

	font = AEGfxCreateFont("Assets/font/DotGothic16-Regular.ttf", 30);

	// Game Loop
	while (gGameStateCurr != GS_QUIT)
	{
		// reset the system modules
		AESysReset();

		if (gGameStateCurr != GS_RESTART) {
			GameStateManagerUpdate();
			GameStateLoad();
		}
		else
			gGameStateNext = gGameStateCurr = gGameStatePrev;

		GameStateInit();

		while (gGameStateCurr == gGameStateNext)
		{
			// Informing the system about the loop's start
			AESysFrameStart();

			// Handling Input
			AEInputUpdate();

			GameStateUpdate();

			GameStateDraw();

			AESysFrameEnd();

			if (AESysDoesWindowExist() == false)
				gGameStateNext = GS_QUIT;
		}
		GameStateFree();

		if (gGameStateNext != GS_RESTART) {
			GameStateUnload();
		}

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}

	AEGfxDestroyFont(font);

	AESysExit();
}