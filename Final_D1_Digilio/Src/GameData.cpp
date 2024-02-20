#include "GameData.h"

namespace GameData
{
	const int screenWidth = 1024;
	const int screenHeight = 768;
	Vector2 screenCenter = { screenWidth / 2, screenHeight / 2 };
	bool loading = true;
	int highScore = 0;
	double spawnRateBase  = 1.4f;
	double spawnRateHardnes = spawnRateBase;
	float enemyBaseSpeed  = 200.0f;
	float enemySpeedHardnes = enemyBaseSpeed;

	Music menuMusic{};
	Music gameLoopMusic{};

	Font font{};
	float fontSize{};
	float spacing = 8.0f;
	float instrucrtionsSpacing = 2.0f;

	double pauseTimer = 0.0f;
	double pauseDelay = 0.2f;

	bool isUpButtonPressed = false;
	bool isDownButtonPressed = false;
	bool isLeftButtonPressed = false;
	bool isRightButtonPressed = false;
	bool isEnterButtonPressed = false;

	double buttonTimer{};

	Rectangle gameScreen{96.0f, 30.0f, 852.0f, 506.0f};
}