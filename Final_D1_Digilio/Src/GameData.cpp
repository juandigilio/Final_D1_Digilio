#include "GameData.h"

namespace GameData
{
	const int screenWidth = 1024;
	const int screenHeight = 768;
	Vector2 screenCenter = { screenWidth / 2, screenHeight / 2 };

	Music menuMusic{};
	Music gameLoopMusic{};

	Font font{};
	float fontSize{};
	float spacing = 8.0f;
	float instructionsSpacing = 2.0f;

	double pauseTimer = 0.0f;
	double pauseDelay = 0.2f;

	bool hasWon = false;
	GameScreen currentScreen = GameScreen::MENU;
	SecondScreen miniGameScreen = SecondScreen::CARSELECTION;

	Rectangle gameScreen{96.0f, 30.0f, 852.0f, 506.0f};
}