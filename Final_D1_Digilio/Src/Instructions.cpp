#include "Instructions.h"



namespace Instructions
{
	void DrawInstructions(Vector2 playPosCenter)
	{
		float instructionsSize = fontSize / 3.0f;

		Vector2 actualPos = playPosCenter;

		actualPos.x = actualPos.x + gameScreen.width - (MeasureTextEx(font, "INSTRUCTIONS", fontSize * 0.85f, spacing / 2.0f).x / 2.0f);
		DrawTextEx(font, "INSTRUCTIONS", actualPos, fontSize * 0.85f, spacing / 2.0f, RAYWHITE);

		actualPos.x = playPosCenter.x + +gameScreen.width - (MeasureTextEx(font, "Don't crash...", instructionsSize, spacing / 4.0f).x / 2.0f);
		actualPos.y += fontSize;
		DrawTextEx(font, "Don't crash...", actualPos, instructionsSize, spacing / 4.0f, RAYWHITE);
	}
}