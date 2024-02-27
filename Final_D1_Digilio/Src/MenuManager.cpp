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
	static void StartUp(Player& player)
	{
		srand(static_cast<unsigned>(time(NULL)));

		SetConfigFlags(FLAG_MSAA_4X_HINT);

		InitWindow(screenWidth, screenHeight, "Gran-Turismo 14");

		InitAudioDevice();

		MainScreen::LoadAssets(player);

		//PlayMusicStream(menuMusic);
	}

	static void UnloadTextures(Player& player)
	{
		MainScreen::UnloadMainTextures();
		PlayerUtilities::UnloadPlayerTexture(player);
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
					Menu::ShowMenu();
					//MainScreen::DrawMainScreen(player);
					break;
				}
				case GameScreen::GAME:
				{
					//GameLoop::Play(player, enemies, currentScreen);
					break;
				}
				case GameScreen::RESULTS:
				{
					//FinalResults::ShowResults(player, currentSceen);
					break;
				}
				case GameScreen::PAUSE:
				{
					Pause::ShowPause(currentScreen);
					break;
				}
				case GameScreen::EXIT:
				{
					UnloadTextures(player);
					CloseWindow();
					break;
				}
			}

			MainScreen::RunMainScreen(player, currentScreen);

			EndDrawing();
		}

		UnloadTextures(player);
	}
}