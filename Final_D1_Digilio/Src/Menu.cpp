#include "Menu.h"

#include "Instructions.h"
#include "Credits.h"


namespace Menu
{
	Vector2 playPos;
	Vector2 instructionsPos;
	Vector2 creditsPos;
	Vector2 exitPos;
	Vector2 playSize;

	float leftLimit;
	float rightLimit;

	float pos1;
	float pos2;
	float pos3;
	float pos4;

	int menuPos = 1;

	bool isMovingLeft = false;
	bool isMovingRight = false;

	void InitMenu()
	{
		playSize = MeasureTextEx(font, "Play", fontSize * 0.65f, spacing / 4.0f);

		leftLimit = gameScreen.width * -4.0f - (playSize.x / 2.0f);
		rightLimit = gameScreen.x + (gameScreen.width / 2.0f) - (playSize.x / 2.0f);

		playPos.x = gameScreen.x + (gameScreen.width / 2.0f) - (playSize.x / 2.0f);
		playPos.y = gameScreen.y + (gameScreen.height / 2.0f) - (playSize.y / 2.0f);

		pos1 = gameScreen.x + (gameScreen.width / 2.0f) - (playSize.x / 2.0f);
		pos2 = pos1 - gameScreen.width;
		pos3 = pos2 - gameScreen.width;
		pos4 = pos3 - gameScreen.width;
	}

	static void GetInput()
	{
		SetExitKey(KEY_ESCAPE);

		if (isLeftButtonPressed)
		{
			isLeftButtonPressed = false;

			if (menuPos > 1)
			{
				isMovingLeft = true;

				menuPos--;
			}
		}
		else if (isRightButtonPressed)
		{
			isRightButtonPressed = false;

			if (menuPos < 4)
			{
				isMovingRight = true;

				menuPos++;
			}
		}
	}

	static void UpdateMenu()
	{
		if (isMovingRight)
		{
			playPos.x -= 1 * GetFrameTime();

			if (menuPos == 2)
			{
				if (playPos.x <= pos2)
				{
					isMovingRight = false;
					playPos.x = pos2;
				}
			}
			else if (menuPos == 3)
			{
				if (playPos.x <= pos3)
				{
					isMovingRight = false;
					playPos.x = pos3;
				}
			}
			else if (menuPos == 4)
			{
				if (playPos.x <= pos4)
				{
					playPos.x = pos4;

					isMovingRight = false;
				}
			}
		}
		else if (isMovingLeft)
		{
			playPos.x += 1 * GetFrameTime();

			if (menuPos == 1)
			{
				if (playPos.x >= pos1)
				{
					playPos.x = pos1;

					isMovingLeft = false;
				}
				else if (playPos.x >= pos2)
				{
					playPos.x = pos2;

					isMovingLeft = false;
				}
				else if (playPos.x >= pos3)
				{
					playPos.x = pos3;

					isMovingLeft = false;
				}
			}
		}

		UpdateMusicStream(menuMusic);
	}

	static void DrawMenu()
	{
		DrawTextEx(font, "Play", playPos, fontSize * 1.1f, spacing, BLACK);
		
		Instructions::DrawInstructions(playPos);

		Credits::DrawCredits(playPos);

		Vector2 actualPos = playPos;

		actualPos.x += gameScreen.width * 3.0f;

		DrawTextEx(font, "Exit", actualPos, fontSize * 1.1f, spacing, BLACK);
	}

	void ShowMenu()
	{
		GetInput();

		UpdateMenu();

		DrawMenu();
	}
}