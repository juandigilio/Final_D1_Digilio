#include "Menu.h"

namespace Menu
{
	Vector2 playPos;
	Vector2 instructionsPos;
	Vector2 creditsPos;
	Vector2 exitPos;

	static void GetInput()
	{
		SetExitKey(KEY_ESCAPE);

		
	}

	static void DrawMenu()
	{
		DrawTextEx(font, "Play", playPos, fontSize * 1.1f, spacing, BLACK);
		DrawTextEx(font, "Instructions", instructionsPos, fontSize * 0.5f, instrucrtionsSpacing, BLACK);
		DrawTextEx(font, "Credits", creditsPos, fontSize * 0.8f, 3, BLACK);
		DrawTextEx(font, "Exit", exitPos, fontSize, spacing, BLACK);
	}

	void ShowMenu(GameSceen& currentSceen)
	{
		DrawMenu();

		UpdateMusicStream(menuMusic);

		GetInput(currentSceen);
	}

	void UnloadMenuTextures()
	{

		UnloadMusicStream(menuMusic);


		UnloadFont(font);
	}
}