#pragma once

#include "raylib.h"


namespace GameData
{
	enum class GameScreen
	{
		MENU,
		GAME,
		RESULTS,
		PAUSE,
		EXIT,
	};

	extern const int screenWidth;
	extern const int screenHeight;
	extern Vector2 screenCenter;
	extern bool loading;
	extern int highScore;
	extern double spawnRateBase ;
	extern double spawnRateHardness;
	extern float enemyBaseSpeed;
	extern float enemySpeedHardness;

	extern Music menuMusic;
	extern Music gameLoopMusic;

	extern Font font;
	extern float fontSize;
	extern float spacing;
	extern float instructionsSpacing;

	extern double pauseTimer;
	extern double pauseDelay;

	extern Rectangle gameScreen;
}
