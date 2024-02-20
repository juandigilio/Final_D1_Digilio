#include "Menu.h"

#include "Instructions.h"
#include "Credits.h"


namespace Menu
{
	Vector2 playPos;
	Vector2 instructionsPos;
	Vector2 creditsPos;
	Vector2 exitPos;

	void InitMenu()
	{
		Vector2 playSize = MeasureTextEx(font, "Play", fontSize * 0.65f, spacing / 4.0f);

		playPos.x = gameScreen.x + (gameScreen.width / 2.0f) - (playSize.x / 2.0f);
		playPos.y = gameScreen.y + (gameScreen.height / 2.0f) - (playSize.y / 2.0f);
	}

	static void GetInput()
	{
		SetExitKey(KEY_ESCAPE);

		
	}

	static void DrawMenu()
	{
		DrawTextEx(font, "Play", playPos, fontSize * 1.1f, spacing, BLACK);
		
		Instructions::DrawInstructions(playPos);

		Credits::DrawCredits(playPos);
	}

	void ShowMenu()
	{
		DrawMenu();

		UpdateMusicStream(menuMusic);

		GetInput();
	}
}