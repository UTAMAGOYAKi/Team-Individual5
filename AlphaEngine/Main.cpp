#pragma once
#include "Main.h"

const u32 FRAMERATE = 60;

int FONT_SIZE = 30;
AEVec2 mouse_pos;
s8 font;
f64 g_dt;

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
	AESysInit(hInstance, nCmdShow, 1280, 720, 1, FRAMERATE, true, NULL);
	AESysToggleFullScreen(true);

	// Changing the window title
	AESysSetWindowTitle("Alchemy Main");

	GameStateManagerInit(GS_LOAD);

	font = AEGfxCreateFont("Assets/font/DotGothic16-Regular.ttf", FONT_SIZE);

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

			g_dt = AEFrameRateControllerGetFrameTime();
			// Updates global mouse pos
			int x, y;
			AEInputGetCursorPosition(&x, &y);
			mouse_pos.x = (f32)x - AEGetWindowWidth() / 2;
			mouse_pos.y = (f32)y - AEGetWindowHeight() / 2;

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