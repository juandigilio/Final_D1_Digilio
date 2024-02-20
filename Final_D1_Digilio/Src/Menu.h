#pragma once

#include "raylib.h"

#include "GameData.h"


using namespace GameData;

namespace Menu
{
	extern void ShowMenu(GameSceen& currentSceen);

	extern void InitMenu();

	extern void UnloadMenuTextures();
}