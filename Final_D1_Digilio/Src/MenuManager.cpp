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

		InitWindow(screenWidth, screenHeight, "Dyno Street Racing");

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

	static void ClearScreen()
	{
		if (miniGameScreen == SecondScreen::WIN)
		{
			ClearBackground(BLUE);
		}
		else
		{
			ClearBackground(BLACK);
		}
	}

	void RunGame()
	{
		Player player;

		StartUp(player);

		while (currentScreen != GameScreen::EXIT && !WindowShouldClose())
		{
			BeginDrawing();

			ClearScreen();

			switch (currentScreen)
			{
				case GameScreen::MENU:
				{
					Menu::ShowMenu();
					break;
				}
				case GameScreen::GAME:
				{
					SecondScreenManager::RunSecondGame(player);
					break;
				}
				case GameScreen::EXIT:
				{
					UnloadAssets(player);
					CloseWindow();
					break;
				}
			}

			MainScreen::RunMainScreen(player);

			EndDrawing();
		}

		UnloadAssets(player);
	}
}