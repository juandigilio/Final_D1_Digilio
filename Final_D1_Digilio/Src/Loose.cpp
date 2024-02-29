#include "Loose.h"

#include "raylib.h"


namespace Loose
{
	double startPoint;
	bool firstTime = true;

	void ShowLooseScreen()
	{
		if (firstTime)
		{
			startPoint = GetTime();

			firstTime = false;
		}

		DrawTextEx(font, "You crashed!!", { 270.0f, 250.0f}, fontSize * 1.1f, spacing, WHITE);

		double elapsedTime = GetTime() - startPoint;

		if (elapsedTime > 3.0f)
		{
			firstTime = true;

			miniGameScreen = SecondScreen::CARSELECTION;
		}
	}
}