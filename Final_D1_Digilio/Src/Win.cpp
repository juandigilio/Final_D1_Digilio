#include "Win.h"

#include "raylib.h"


namespace Win
{
	double startPoint;
	bool firstTime = true;
	Vector2 pos1;
	Vector2 pos2;

	Texture2D face;
	Vector2 facePos;

	static void LoadWinScreen()
	{
		face = LoadTexture("Assets/Images/Game/BadFace.png");

		facePos.x = gameScreen.x + 40.0f;
		facePos.y = gameScreen.y + 40.0f;

		pos1.x = facePos.x;
		pos1.y = facePos.y + face.width + 50.0f;

		pos2.x = facePos.x;
		pos2.y = pos1.y + 30.0f;
	}

	void ShowWinScreen()
	{
		if (firstTime)
		{
			startPoint = GetTime();

			firstTime = false;

			LoadWinScreen();
		}

		DrawTextureV(face, facePos, RAYWHITE);
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