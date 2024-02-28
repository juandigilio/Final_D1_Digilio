#include "Menu.h"

#include <iostream>

#include "MainScreen.h"
#include "Instructions.h"
#include "Credits.h"

using namespace MainScreen;

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
		fontSize = 50.0f;

		playSize = MeasureTextEx(font, "Play", fontSize * 1.1f, spacing);

		playPos.x = gameScreen.x + (gameScreen.width / 2.0f) - (playSize.x / 2.0f);
		playPos.y = gameScreen.y + (gameScreen.height / 2.0f) - (playSize.y / 2.0f);

		pos1 = gameScreen.x + (gameScreen.width / 2.0f) - (playSize.x / 2.0f);
		pos2 = pos1 - gameScreen.width + (playSize.x / 2.0f);
		pos3 = pos2 - gameScreen.width;
		pos4 = pos3 - gameScreen.width;
	}

	static void GetInput(GameScreen& currentScreen)
	{
		SetExitKey(KEY_ESCAPE);

		if (isLeftButtonPressed)
		{
			isLeftButtonPressed = false;

			isMovingRight = false;

			if (menuPos < 4)
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

		if (currentScreen == GameScreen::GAME)
		{
			currentScreen = GameScreen::MENU;
		}
		
		if (isEnterButtonPressed && isComputerOn)
		{
			if (menuPos == 1)
			{
				currentScreen = GameScreen::GAME;
			}
			else if (menuPos == 4)
			{
				currentScreen = GameScreen::EXIT;
			}

			isEnterButtonPressed = false;
		}
	}

	static void UpdateMenu()
	{
		if (isMovingRight)
		{
			playPos.x += 1000 * GetFrameTime();

			if (menuPos == 1)
			{
				if (playPos.x >= pos1)
				{
					isMovingRight = false;
					playPos.x = pos1;
				}
			}
			else if (menuPos == 2)
			{
				if (playPos.x >= pos2)
				{
					isMovingRight = false;
					playPos.x = pos2;
				}
			}
			else if (menuPos == 3)
			{
				if (playPos.x >= pos3)
				{
					isMovingRight = false;
					playPos.x = pos3;
				}
			}
			else if (menuPos == 4)
			{
				if (playPos.x >= pos4)
				{
					playPos.x = pos4;

					isMovingRight = false;
				}
			}
		}
		else if (isMovingLeft)
		{
			playPos.x -= 1000 * GetFrameTime();

			if (menuPos == 1)
			{
				if (playPos.x <= pos1)
				{
					playPos.x = pos1;

					isMovingLeft = false;
				}
			}
			else if (menuPos == 2)
			{
				if (playPos.x <= pos2)
				{
					playPos.x = pos2;

					isMovingLeft = false;
				}
			}
			else if (menuPos == 3)
			{
				if (playPos.x <= pos3)
				{
					playPos.x = pos3;

					isMovingLeft = false;
				}
			}
			else if (menuPos == 4)
			{
				if (playPos.x <= pos4)
				{
					playPos.x = pos4;

					isMovingLeft = false;
				}
			}
		}

		UpdateMusicStream(menuMusic);
	}

	static void DrawExit(Vector2 playPosition)
	{
		Vector2 actualPos = playPosition;

		float exitLength = MeasureTextEx(font, "Exit", fontSize * 1.1f, spacing).x / 2.0f;

		actualPos.x += gameScreen.width * 3.0f - exitLength;

		DrawTextEx(font, "Exit", actualPos, fontSize * 1.1f, spacing, WHITE);
	}

	static void DrawMenu()
	{
		DrawTextEx(font, "Play", playPos, fontSize * 1.1f, spacing, WHITE);
		
		Instructions::DrawInstructions(playPos);

		Credits::DrawCredits(playPos);

		DrawExit(playPos);
	}

	void ShowMenu(GameScreen& currentScreen)
	{
		if (MainScreen::isComputerOn)
		{
			GetInput(currentScreen);

			UpdateMenu();

			DrawMenu();
		}
	}
}