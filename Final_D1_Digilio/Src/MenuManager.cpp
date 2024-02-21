#include "MenuManager.h"

#include <iostream>

#include "GameData.h"
#include "Player.h"

#include "Menu.h"
#include "Credits.h"
#include "Instructions.h"
#include "Pause.h"
#include "FinalResults.h"
#include "MainScreen.h"
//#include "GameLoop.h"



using namespace GameData;

namespace MenuManager
{
	static void StartUp()
	{
		srand(static_cast<unsigned>(time(NULL)));

		SetConfigFlags(FLAG_MSAA_4X_HINT);

		InitWindow(screenWidth, screenHeight, "Gran-Turismo 14");

		InitAudioDevice();

		MainScreen::LoadAssets();

		//PlayMusicStream(menuMusic);
	}

	static void UnloadTextures(Player& player)
	{
		MainScreen::UnloadMainTextures();
		PlayerUtilities::UnloadPlayerTexture(player);
	}

	void RunGame()
	{
		GameSceen currentSceen = GameSceen::MENU;
		Player player;

		StartUp();

		while (currentSceen != GameSceen::EXIT && !WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(BLACK);

			switch (currentSceen)
			{
				case GameSceen::MENU:
				{
					Menu::ShowMenu();
					MainScreen::DrawMainScreen();
					break;
				}
				case GameSceen::GAME:
				{
					//GameLoop::Play(player, enemies, currentScreen);
					break;
				}
				case GameSceen::RESULTS:
				{
					//FinalResults::ShowResults(player, currentSceen);
					break;
				}
				case GameSceen::PAUSE:
				{
					Pause::ShowPause(currentSceen);
					break;
				}
				case GameSceen::EXIT:
				{
					UnloadTextures(player);
					CloseWindow();
					break;
				}
			}

			MainScreen::DrawMainScreen();

			EndDrawing();
		}

		UnloadTextures(player);
	}
}