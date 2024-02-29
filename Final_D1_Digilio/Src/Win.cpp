#include "Win.h"

#include "raylib.h"


namespace Win
{
	double startPoint;
	bool firstTime = true;
	Vector2 pos1;
	Vector2 pos2;

	static void SetPositions()
	{
		pos1.x = gameScreen.x + 30.0f;
		pos1.y = gameScreen.y + 30.0f;

		pos2.x = gameScreen.x + 30.0f;
		pos2.y = gameScreen.y + 70.0f;
	}

	void ShowWinScreen()
	{
		if (firstTime)
		{
			startPoint = GetTime();

			firstTime = false;

			SetPositions();
		}

		DrawTextEx(font, "Your PC ran into a problem that it couldn't", pos1, fontSize * 0.5f, spacing, WHITE);
		DrawTextEx(font, "handle, and now it needs to restart", pos2, fontSize * 0.5f, spacing, WHITE);

		double elapsedTime = GetTime() - startPoint;

		if (elapsedTime > 3.0f)
		{
			firstTime = true;

			hasWon = true;

			miniGameScreen = SecondScreen::CARSELECTION;
		}
	}
}