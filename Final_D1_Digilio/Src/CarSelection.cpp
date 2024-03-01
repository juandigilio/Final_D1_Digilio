#include "CarSelection.h"

#include "raylib.h"

#include "MainScreen.h"
#include "Menu.h"
#include "Credits.h"
#include "Instructions.h"

using namespace MainScreen;


namespace CarSelection
{
	Texture redCar;
	Vector2 redCarPos;

	Texture blueCar;
	Vector2 blueCarPos;

	Texture yellowCar;
	Vector2 yellowCarPos;


	float pos1;
	float pos2;
	float pos3;

	int menuPos = 1;

	bool isMovingLeft = false;
	bool isMovingRight = false;

	void InitCarSelection()
	{
		redCar = LoadTexture("Assets/Images/Game/Cars/RedFerrari.png");
		blueCar = LoadTexture("Assets/Images/Game/Cars/BlueBugatti.png");
		yellowCar = LoadTexture("Assets/Images/Game/Cars/YellowLambo.png");

		pos1 = gameScreen.x + (gameScreen.width / 2.0f) - (redCar.width / 2.0f);
		pos2 = gameScreen.x - (gameScreen.width * 1.5f) - (blueCar.width / 2.0f);
		pos3 = gameScreen.x - (gameScreen.width * 2.5f) - (yellowCar.width / 2.0f);

		redCarPos.x = pos1;
		
		redCarPos.y = gameScreen.y + (gameScreen.height / 2.0f) - (redCar.height / 2.0f);
		blueCarPos.y = gameScreen.y + (gameScreen.height / 2.0f) - (blueCar.height / 2.0f);
		yellowCarPos.y = gameScreen.y + (gameScreen.height / 2.0f) - (yellowCar.height / 2.0f);
	}

	static void GetInput(Player& player)
	{
		if (isLeftButtonPressed)
		{
			isLeftButtonPressed = false;

			isMovingRight = false;

			if (menuPos < 3)
			{
				isMovingLeft = true;

				menuPos++;
			}
		}
		else if (isRightButtonPressed)
		{
			isRightButtonPressed = false;

			isMovingLeft = false;

			if (menuPos > 1)
			{
				isMovingRight = true;

				menuPos--;
			}
		}

		if (isEnterButtonPressed)
		{
			if (menuPos == 1)
			{
				player.carTexture = LoadTexture("Assets/Images/Game/Cars/RedCarTopView.png");
			}
			else if (menuPos == 2)
			{
				player.carTexture = LoadTexture("Assets/Images/Game/Cars/BlueCarTopView.png");
			}
			else if (menuPos == 3)
			{
				player.carTexture = LoadTexture("Assets/Images/Game/Cars/YellowCarTopView.png");
			}

			miniGameScreen = SecondScreen::PLAY;

			isEnterButtonPressed = false;
		}

		if (IsKeyDown(KEY_ESCAPE))
		{
			pauseTimer = GetTime();
		}
	}

	static void UpdateCarsPositions()
	{
		if (isMovingRight)
		{
			redCarPos.x += 1000 * GetFrameTime();

			if (menuPos == 1)
			{
				if (redCarPos.x >= pos1)
				{
					isMovingRight = false;
					redCarPos.x = pos1;
				}
			}
			else if (menuPos == 2)
			{
				if (redCarPos.x >= pos2)
				{
					isMovingRight = false;
					redCarPos.x = pos2;
				}
			}
			else if (menuPos == 3)
			{
				if (redCarPos.x >= pos3)
				{
					isMovingRight = false;
					redCarPos.x = pos3;
				}
			}
		}
		else if (isMovingLeft)
		{
			redCarPos.x -= 1000 * GetFrameTime();

			if (menuPos == 1)
			{
				if (redCarPos.x <= pos1)
				{
					redCarPos.x = pos1;

					isMovingLeft = false;
				}
			}
			else if (menuPos == 2)
			{
				if (redCarPos.x <= pos2)
				{
					redCarPos.x = pos2;

					isMovingLeft = false;
				}
			}
			else if (menuPos == 3)
			{
				if (redCarPos.x <= pos3)
				{
					redCarPos.x = pos3;

					isMovingLeft = false;
				}
			}
		}

		blueCarPos.x = redCarPos.x + (redCar.width / 2.0f) + gameScreen.width + (blueCar.width / 2.0f) + 190.0f;
		yellowCarPos.x = redCarPos.x + (redCar.width / 2.0f) + (gameScreen.width * 2.0f) + (yellowCar.width / 2.0f) + 210.0f;

		//UpdateMusicStream(menuMusic);
	}

	static void DrawCars()
	{
		DrawTextureV(redCar, redCarPos, WHITE);
		DrawTextureV(blueCar, blueCarPos, WHITE);
		DrawTextureV(yellowCar, yellowCarPos, WHITE);
	}

	void RunCarSelection(Player& player)
	{
		GetInput(player);

		UpdateCarsPositions();

		DrawCars();
	}

	void UnloadAssets()
	{
		UnloadTexture(redCar);
		UnloadTexture(blueCar);
		UnloadTexture(yellowCar);
	}
}