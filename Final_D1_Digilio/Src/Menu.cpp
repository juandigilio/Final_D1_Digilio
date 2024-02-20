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

	void InitMenu()
	{
		playSize = MeasureTextEx(font, "Play", fontSize * 0.65f, spacing / 4.0f);

		playPos.x = gameScreen.x + (gameScreen.width / 2.0f) - (playSize.x / 2.0f);
		playPos.y = gameScreen.y + (gameScreen.height / 2.0f) - (playSize.y / 2.0f);
	}

	static void GetInput()
	{
		SetExitKey(KEY_ESCAPE);

		float leftLimit = gameScreen.width * -4.0f - (playSize.x / 2.0f);
		float rightLimit = gameScreen.x + (gameScreen.width / 2.0f) - (playSize.x / 2.0f);

		if (isLeftButtonPressed)
		{
			playPos.x += gameScreen.width;

			if (playPos.x > rightLimit)
			{
				playPos.x = rightLimit;
			}
		}
		else if (isRightButtonPressed)
		{
			playPos.x -= gameScreen.width;

			if (playPos.x < leftLimit)
			{
				playPos.x = leftLimit;
			}
		}
	}

	static void DrawMenu()
	{
		DrawTextEx(font, "Play", playPos, fontSize * 1.1f, spacing, BLACK);
		
		Instructions::DrawInstructions(playPos);

		Credits::DrawCredits(playPos);

		Vector2 exitPos = playPos;
		exitPos.x += gameScreen.width * 3.0f;

		DrawTextEx(font, "Exit", exitPos, fontSize * 1.1f, spacing, BLACK);
	}

	void ShowMenu()
	{
		DrawMenu();

		UpdateMusicStream(menuMusic);

		GetInput();
	}
}