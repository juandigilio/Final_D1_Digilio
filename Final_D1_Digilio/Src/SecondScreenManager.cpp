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
				CarSelection::RunCarSelection(player, miniGameScreen);
				break;
			}
			case SecondScreen::PLAY:
			{
				Game::PlayGame(player, miniGameScreen);
				break;
			}
			case SecondScreen::LOOSE:
			{
				Loose::ShowLooseScreen(miniGameScreen);
				break;
			}
			case SecondScreen::WIN:
			{
				Win::ShowWinScreen(miniGameScreen);
				break;
			}
		}
	}
}