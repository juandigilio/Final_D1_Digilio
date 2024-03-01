#include "Instructions.h"


namespace Instructions
{
	void DrawInstructions(Vector2 playPosCenter)
	{
		float instructionsSize = fontSize / 3.0f;

		Vector2 actualPos = playPosCenter;

		actualPos.x = actualPos.x + gameScreen.width - (MeasureTextEx(font, "INSTRUCTIONS", fontSize * 0.85f, spacing / 2.0f).x / 2.0f);
		actualPos.y -= 75.0f;
		DrawTextEx(font, "INSTRUCTIONS", actualPos, fontSize * 0.85f, spacing / 2.0f, RAYWHITE);

		actualPos.x = playPosCenter.x + +gameScreen.width - (MeasureTextEx(font, "Use arrows to cut lines, press ENTER to go back to car selection", instructionsSize, spacing / 4.0f).x / 2.0f);
		actualPos.y += fontSize * 2.0f;
		DrawTextEx(font, "Use arrows to cut lines, press ENTER to go back to car selection", actualPos, instructionsSize, spacing / 4.0f, RAYWHITE);

		actualPos.x = playPosCenter.x + +gameScreen.width - (MeasureTextEx(font, "Don't crash and earn 1.000 points to win the game", instructionsSize, spacing / 4.0f).x / 2.0f);
		actualPos.y += fontSize / 2.0f;
		DrawTextEx(font, "Don't crash and earn 1.000 points to win the game", actualPos, instructionsSize, spacing / 4.0f, RAYWHITE);
	}
}