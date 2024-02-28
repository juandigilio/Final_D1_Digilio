#include "MenuManager.h"

#include <iostream>

#include "GameData.h"
#include "Player.h"

#include "Menu.h"
#include "MainScreen.h"
#include "CarSelection.h"
#include "SecondScreenManager.h"
#include "Game.h"



using namespace GameData;

namespace MenuManager
{
	static void StartUp(Player& player)
	{
		srand(static_cast<unsigned>(time(NULL)));

		SetConfigFlags(FLAG_MSAA_4X_HINT);

		InitWindow(screenWidth, screenHeight, "Gran-Turismo 14");

		InitAudioDevice();

		MainScreen::LoadAssets(player);
		Menu::InitMenu();
	}

	static void UnloadAssets(Player& player)
	{
		MainScreen::UnloadMainAssets();
		PlayerUtilities::UnloadPlayerTexture(player);
		CarSelection::UnloadAssets();
		Game::UnloadAssets();
	}

	void RunGame()
	{
		GameScreen currentScreen = GameScreen::MENU;
		Player player;

		StartUp(player);

		while (currentScreen != GameScreen::EXIT && !WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(BLACK);

			switch (currentScreen)
			{
				case GameScreen::MENU:
				{
					Menu::ShowMenu(currentScreen);
					break;
				}
				case GameScreen::GAME:
				{
					SecondScreenManager::RunSecondGame(player);
					break;
				}
				case GameScreen::RESULTS:
				{
					//FinalResults::ShowResults(player, currentSceen);
					break;
				}
				case GameScreen::PAUSE:
				{
					//Pause::ShowPause(currentScreen);
					break;
				}
				case GameScreen::EXIT:
				{
					UnloadAssets(player);
					CloseWindow();
					break;
				}
			}

			MainScreen::RunMainScreen(player, currentScreen);

			EndDrawing();
		}

		UnloadAssets(player);
	}
}