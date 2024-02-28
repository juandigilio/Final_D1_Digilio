#include "SecondScreenManager.h"

#include "raylib.h"

#include "GameData.h"
#include "CarSelection.h"

using namespace GameData;


namespace SecondScreenManager
{
	bool firstTime = true;
	static SecondScreen currentScreen = SecondScreen::CARSELECTION;

	void RunSecondGame(Player& player)
	{
		if (firstTime)
		{
			CarSelection::LoadAssets();

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
				//GameLoop::Play(player, enemies, currentScreen);
				break;
			}
		}
	}
}