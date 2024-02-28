#pragma once

#include "GameData.h"
#include "Player.h"

namespace CarSelection
{
	extern void LoadAssets();

	extern void RunCarSelection(Player& player, SecondScreen& secondScreen);

	extern void UnloadAssets();
}
