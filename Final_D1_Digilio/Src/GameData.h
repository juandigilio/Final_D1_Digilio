#pragma once

#include "raylib.h"


namespace GameData
{
	enum class GameScreen
	{
		MENU,
		GAME,
		EXIT,
	};

	enum class SecondScreen
	{
		CARSELECTION,
		PLAY,
		LOOSE,
		WIN
	};

	extern const int screenWidth;
	extern const int screenHeight;
	extern Vector2 screenCenter;

	extern Music menuMusic;
	extern Music gameLoopMusic;

	extern Font font;
	extern float fontSize;
	extern float spacing;
	extern float instructionsSpacing;

	extern double pauseTimer;
	extern double pauseDelay;

	extern bool hasWon;
	extern GameScreen currentScreen;
	extern SecondScreen miniGameScreen;

	extern Rectangle gameScreen;
}
