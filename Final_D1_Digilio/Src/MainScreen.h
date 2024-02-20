#pragma once

#include "raylib.h"

namespace MainScreen
{
	extern bool isUpButtonPressed;
	extern bool isDownButtonPressed;
	extern bool isLeftButtonPressed;
	extern bool isRightButtonPressed;
	extern bool isEnterButtonPressed;

	extern void LoadAssets();
	extern void DrawMainScreen();
	extern void UnloadMainTextures();
}
