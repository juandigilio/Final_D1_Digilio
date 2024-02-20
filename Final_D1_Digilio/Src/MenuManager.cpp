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

		PlayMusicStream(menuMusic);
	}

	static void UnloadTextures(Player& player)
	{
		//GameLoop::UnloadGameLoopTextures();
		Menu::UnloadMenuTextures();
		PlayerUtilities::UnloadPlayerTextures(player);
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
					Menu::ShowMenu(currentSceen);
					break;
				}
				case GameSceen::GAME:
				{
					//GameLoop::Play(player, enemies, currentScreen);
					break;
				}
				case GameSceen::RESULTS:
				{
					FinalResults::ShowResults(player, currentSceen);
					break;
				}
				case GameSceen::PAUSE:
				{
					Pause::ShowPause(player, currentSceen);
					break;
				}
				case GameSceen::INSTRUCTIONS:
				{
					Instructions::ShowInstructions(currentSceen);
					break;
				}
				case GameSceen::CREDITS:
				{
					Credits::ShowCredits(currentSceen);
					break;
				}
				case GameSceen::EXIT:
				{
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