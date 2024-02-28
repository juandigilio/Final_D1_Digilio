#pragma once

#include "raylib.h"

#include "Player.h"

namespace MainScreen
{
	extern bool isLeftButtonPressed;
	extern bool isRightButtonPressed;
	extern bool isEnterButtonPressed;

	extern bool isComputerOn;

	extern void LoadAssets(Player& player);
	extern void RunMainScreen(Player& player, GameScreen& gameScreen);
	extern void UnloadMainTextures();
}
