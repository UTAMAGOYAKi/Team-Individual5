// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include "player.h"
#include <iostream>
#include <string>

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
// main
int i = 0;
float position = 1000.0;



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	enum spell_slot {empty, fire_slot, poison_slot, water_slot};
	enum combined { cempty, burn, toxic};
	int spell_slot_combine = empty;
	int spell_slot_one = empty;
	int spell_slot_two = empty;
	int gGameRunning = 1;

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("Alchemy -- Daniel's testing branch");

	// reset the system modules
	AESysReset();

	// Initialization of your own variables go here
	s8 test_font = AEGfxCreateFont("Assets/Roboto-Regular.ttf", 20);
	const char* test_str = { "Test" };
	const char* rat_name_1 = { "Rat 1" };
	const char* rat_name_2 = { "Rat 2" };
	int rat_hp_1 = 10;
	float outside = -1000.0;
	float center_x = 400.0;
	float center_y = 300.0;
	s32 pX ;
	s32 pY ;
	bool alchemy_mode = false;
	bool combination = false;
	float spell_pos = outside;
	float item_one_pos = (spell_pos - 100);
	float item_two_pos = (spell_pos + 100);

	float fire_y = -250.0;
	float fire_x = (spell_pos - 100);
	bool fire_to_mouse = false;
	
	float poison_y = -250.0;
	float poison_x = (spell_pos + 100);
	bool poison_to_mouse = false;
	
	float burn_y = -250.0;
	float burn_x = (spell_pos + 100);
	bool burn_to_mouse = false;


	float toxic_y = -250.0;
	float toxic_x = (spell_pos + 100);
	bool toxic_to_mouse = false;

	float water_y = -250.0;
	float water_x = (spell_pos - 200);
	bool water_to_mouse = false;

	player* alchemice = player_create();
	std::string rat_hp;
	// Pointer to Mesh
	AEGfxVertexList* pMesh = 0;
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF00FF, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFF00, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFF00FFFF, 0.0f, 1.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
	// Saving the mesh (list of triangles) in pMesh
	pMesh = AEGfxMeshEnd();
	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/rat_Piskel.png");
	AEGfxTexture* chara = AEGfxTextureLoad("Assets/character.png");
	AEGfxTexture* rat = AEGfxTextureLoad("Assets/rat_Piskel.png");
	AEGfxTexture* spell_g = AEGfxTextureLoad("Assets/spell_glyph.png");
	AEGfxTexture* fire = AEGfxTextureLoad("Assets/not_fire.png");
	AEGfxTexture* poison = AEGfxTextureLoad("Assets/not_posion.png");
	AEGfxTexture* water = AEGfxTextureLoad("Assets/water.png");
	AEGfxTexture* toxict = AEGfxTextureLoad("Assets/toxic.png");
	AEGfxTexture* shame = AEGfxTextureLoad("Assets/not_burn.png");
	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		// Your own update logic goes here
		if (AEInputCheckTriggered(AEVK_Q))
		{
			rat_hp_1--;
			std::cout << "The player used basic attack\n";
			//std::cout << "The player has : " << alchemice->avail_ingre << " available ingredients\n";
		}
		if (rat_hp_1 > 0)
		{
			rat_hp.clear();
			rat_hp += std::to_string(rat_hp_1);
			rat_hp += "/10";
			position = 1000.0;
		}
		else
		{
			if (AEInputCheckTriggered(AEVK_Q) && rat_hp_1 == 0)
			{
				std::cout << rat_name_1 << " is defeated!\n";
			}
			position = 0.0;
		}


		AEInputGetCursorPosition(&pX, &pY);

		if(AEInputCheckTriggered(AEVK_Z))
		{
			std::cout << "The rough position of the mouse is x: " << pX << " y: " << pY<< "\n";
		}


		if (AEInputCheckTriggered(AEVK_W) && spell_pos != 0.0)
		{
			std::cout << "Aclhemy start\n";
			spell_pos = 0.0;
			fire_y = 250;
			fire_x = (spell_pos - 100);
			poison_x = (spell_pos + 100);
			poison_y = 250;
			water_y = 250;
			water_x = (spell_pos - 200);
			alchemy_mode = true;


		}

		if (alchemy_mode)
		{

			if (AEInputCheckTriggered(AEVK_LBUTTON)|| AEInputCheckCurr(AEVK_LBUTTON))
			{
				if (fire_to_mouse)
				{
					fire_y = pY-330;
					fire_x = pX-400;
				}
				else
				{
					if (pX < 350 && pX >240 && pY >500 && pY < 580)
					{
						fire_to_mouse = true;
					}
				}

				if (poison_to_mouse)
				{
					poison_y = pY-330;
					poison_x = pX-400;
				}
				else
				{
					if (pX < 550 && pX >440 && pY >500 && pY < 580)
					{
						poison_to_mouse = true;
					}
				}

				if (water_to_mouse)
				{
					water_y = pY - 330;
					water_x = pX - 400;
				}
				else
				{
					if (pX < 250 && pX >140 && pY > 500 && pY < 580)
					{
						water_to_mouse = true;
					}
				}
			}

			if (AEInputCheckReleased(AEVK_LBUTTON))
			{
				if(fire_to_mouse && !spell_slot_one)
				{
					if (pX < 340 && pX > 250 && pY < 175 && pY > 120)
					{
						fire_y = -150;

					}
					else
					{
						fire_y = 250;
					}
					fire_x = (spell_pos - 100);
					fire_to_mouse = false;
					spell_slot_one = fire_slot;
				}

				if (poison_to_mouse && !spell_slot_one)
				{
					if (pX < 540 && pX > 450 && pY < 175 && pY > 120)
					{
						poison_y = -150;

					}
					else
					{
						poison_y = 250;
					}
					poison_x = (spell_pos + 100);
					poison_to_mouse = false;
					spell_slot_two = poison_slot;
				}


				if (water_to_mouse)
				{
					if (pX < 340 && pX > 250 && pY < 175 && pY > 120)
					{
						water_y = -150;
						water_x = (spell_pos - 100);

					}
					else
					{
						water_y = 250;
						water_x = (spell_pos - 200);

					}
					water_to_mouse = false;
					spell_slot_one = water_slot;
				}
			}

			if (AEInputCheckTriggered(AEVK_X) || combination )
			{
				spell_pos = outside;
				alchemy_mode = false;
				std::cout << "Aclhemy end\n";
				fire_y = -250.0;
				fire_x = (spell_pos - 100);
			}
			if (AEInputCheckTriggered(AEVK_E))
			{
				if (spell_slot_one && spell_slot_two)
				{

					switch (spell_slot_one)
					{
					case fire_slot:
						combination = true;
						alchemy_mode = false;
						fire_y = -outside;
						poison_y = -outside;

						fire_x = (spell_pos - 100);
						poison_x = (spell_pos + 100);
						std::cout << "Alchemy combination!\n BURN\n";
						burn_x = spell_pos;
						burn_y = -150;
						spell_slot_combine = burn;
						break;
					case water_slot:
						combination = true;
						alchemy_mode = false;
						water_y = -outside;
						poison_y = -outside;

						water_x = (spell_pos - 100);
						poison_x = (spell_pos + 100);
						std::cout << "Alchemy combination!\n Toxic\n";
						toxic_x = spell_pos;
						toxic_y = -150;
						spell_slot_combine = toxic;
						break;
					}
				}
				else
				{
					std::cout << "Alchemy combination invalid\n";
				}
			}

		}

		if (combination)
		{
			if (AEInputCheckTriggered(AEVK_LBUTTON) || AEInputCheckCurr(AEVK_LBUTTON))
			{
				if (burn_to_mouse)
				{
					burn_y = pY - 330;
					burn_x = pX - 400;
				}
				else
				{
					if (pX < 450 && pX >340 && pY < 175 && pY > 120 && spell_slot_combine == burn)
					{
						burn_to_mouse = true;
					}
				}

				if (toxic_to_mouse)
				{
					toxic_y = pY - 330;
					toxic_x = pX - 400;
				}
				else
				{
					if (pX < 450 && pX >340 && pY < 175 && pY > 120 && spell_slot_combine == toxic)
					{
						toxic_to_mouse = true;
					}
				}
			}

			if (AEInputCheckReleased(AEVK_LBUTTON))
			{
				if (burn_to_mouse)
				{
					if (pX < 550 && pX > 450 && pY < 350 && pY > 250)
					{
						rat_hp_1 -= 5;
 						spell_pos = outside;
						burn_to_mouse = false;
						combination = false;
						if (rat_hp_1 <= 0)
						{
							std::cout << "Rat 1 was defeated\n";
						}
					}
					else
					{
						burn_x = spell_pos;
						burn_y = -150;
					}
					if (pX < 700 && pX > 620 && pY < 350 && pY > 250)
					{
						//rat_hp_2 -= 5;
						spell_pos = outside;
						burn_to_mouse = false;
						combination = false;
					}
					else
					{
						burn_x = spell_pos;
						burn_y = -150;
					}
				}
				if (toxic_to_mouse)
				{
					if (pX < 550 && pX > 450 && pY < 350 && pY > 250)
					{
						rat_hp_1 -= 3;
						spell_pos = outside;
						toxic_to_mouse = false;
						combination = false;
						if (rat_hp_1 <= 0)
						{
							std::cout << "Rat 1 was defeated\n";
						}
					}
					else
					{
						toxic_x = spell_pos;
						toxic_y = -150;
					}
					if (pX < 700 && pX > 620 && pY < 350 && pY > 250)
					{
						//rat_hp_2 -= 5;
						spell_pos = outside;
						toxic_to_mouse = false;
						combination = false;
					}
					else
					{
						toxic_x = spell_pos;
						toxic_y = -150;
					}
				}
			}


		}







		// Your own rendering logic goes here
		// Set the background to black.
		AEGfxSetBackgroundColor(.2f, .2f, .2f);
		// Tell the engine to get ready to draw something with texture.
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		// Set the tint to white, so that the sprite can 
		// display the full range of colors (default is black).
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Set blend mode to AE_GFX_BM_BLEND
		// This will allow transparency.
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
		// Set the texture to pTex
		AEGfxTextureSet(pTex, 0, 0);
		// Create a scale matrix that scales by 100 x and y
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, 100.f, 100.f);
		// Create a rotation matrix that rotates by 45 degrees
		AEMtx33 rotate = { 0 };

		AEMtx33Rot(&rotate, PI);
		// Create a translation matrix that translates by
		// 100 in the x-axis and 100 in the y-axis
		AEMtx33 translate = { 0 };

		AEMtx33Trans(&translate, (250.f), -20.f);
		// Concat the matrices (TRS)
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		// Choose the transform to use
		AEGfxSetTransform(transform.m);
		// Actually drawing the mesh 
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		AEGfxTextureSet(chara, 0, 0);
		AEMtx33Trans(&translate, (-200.f), 20.f);
		AEMtx33Rot(&rotate, PI);
		AEMtx33Scale(&scale, -200.f, 200.f);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);


		AEGfxTextureSet(rat, 0, 0);
		AEMtx33Trans(&translate, (position - 900.f), -20.f);
		AEMtx33Rot(&rotate, PI);
		AEMtx33Scale(&scale, 100.f, 100.f);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);


		if(alchemy_mode || combination)
		{
			AEGfxTextureSet(spell_g, 0, 0);
			AEMtx33Trans(&translate, (spell_pos), 150.f);
			AEMtx33Rot(&rotate, PI);
			AEMtx33Scale(&scale, 300.f, 300.f);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		}

		if(alchemy_mode)
		{
			AEGfxTextureSet(fire, 0, 0);
			AEMtx33Trans(&translate, fire_x, -fire_y);
			AEMtx33Rot(&rotate, PI);
			AEMtx33Scale(&scale, 100.f, 100.f);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

			AEGfxTextureSet(poison, 0, 0);
			AEMtx33Trans(&translate, poison_x, -poison_y);
			AEMtx33Rot(&rotate, PI);
			AEMtx33Scale(&scale, 100.f, 100.f);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

			AEGfxTextureSet(water, 0, 0);
			AEMtx33Trans(&translate, water_x, -water_y);
			AEMtx33Rot(&rotate, PI);
			AEMtx33Scale(&scale, 100.f, 100.f);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		}

		if(combination)
		{
			AEGfxTextureSet(shame, 0, 0);
			AEMtx33Trans(&translate, burn_x, -burn_y);
			AEMtx33Rot(&rotate, PI);
			AEMtx33Scale(&scale, 100.f, 100.f);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

			AEGfxTextureSet(toxict, 0, 0);
			AEMtx33Trans(&translate, toxic_x, -toxic_y);
			AEMtx33Rot(&rotate, PI);
			AEMtx33Scale(&scale, 100.f, 100.f);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		}

		AEGfxPrint(test_font, (s8*)test_str, -0.65f, 0.5f, 1, 0.0f, 0.0f, 0.0f);
		if (rat_hp_1 > 0)
		{
			AEGfxPrint(test_font, (s8*)rat_name_1, 0.225f, 0.2f, 1, 0.0f, 0.0f, 0.0f);
			AEGfxPrint(test_font, (s8*)rat_hp.c_str(), 0.225f, 0.1f, 1, 0.0f, 0.0f, 0.0f);
		}

		AEGfxPrint(test_font, (s8*)rat_name_2, 0.625f, 0.2f, 1, 0.0f, 0.0f, 0.0f);
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pTex);
	AEGfxTextureUnload(rat);
	AEGfxTextureUnload(chara);
	AEGfxTextureUnload(shame);
	AEGfxTextureUnload(fire);
	AEGfxTextureUnload(poison);
	// free the system
	AESysExit();
}