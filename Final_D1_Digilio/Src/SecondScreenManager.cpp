#include "SecondScreenManager.h"

#include "raylib.h"

#include "GameData.h"
#include "CarSelection.h"
#include "Game.h"
#include "Parallax.h"


using namespace GameData;


namespace SecondScreenManager
{
	bool firstTime = true;
	static SecondScreen currentScreen = SecondScreen::CARSELECTION;

	void RunSecondGame(Player& player)
	{
		if (firstTime)
		{
			CarSelection::InitCarSelection();

			Parallax::InitParallax();

			firstTime = false;
		}

		switch (currentScreen)
		{
			case SecondScreen::CARSELECTION:
			{
				CarSelection::RunCarSelection(player, currentScreen);
				break;
			}
			case SecondScreen::PLAY:
			{
				Game::PlayGame(player, currentScreen);
				break;
			}
		}
	}
}