#include "SecondScreenManager.h"

#include "raylib.h"

#include "GameData.h"
#include "CarSelection.h"
#include "Game.h"
#include "Win.h"
#include "Loose.h"
#include "Parallax.h"


using namespace GameData;


namespace SecondScreenManager
{
	bool firstTime = true;

	void RunSecondGame(Player& player)
	{
		if (firstTime)
		{
			CarSelection::InitCarSelection();

			Parallax::InitParallax();

			firstTime = false;
		}

		switch (miniGameScreen)
		{
			case SecondScreen::CARSELECTION:
			{
				CarSelection::RunCarSelection(player);
				break;
			}
			case SecondScreen::PLAY:
			{
				Game::PlayGame(player);
				break;
			}
			case SecondScreen::LOOSE:
			{
				Loose::ShowLooseScreen();
				break;
			}
			case SecondScreen::WIN:
			{
				Win::ShowWinScreen();
				break;
			}
		}
	}
}