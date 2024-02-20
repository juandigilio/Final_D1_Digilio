#include "Credits.h"

#include "GameData.h"

using namespace GameData;

namespace Credits
{
	void DrawCredits(Vector2 playPosCenter)
	{
		Vector2 actualPos = playPosCenter;

		actualPos.x = actualPos.x + gameScreen.width * 2.0f - MeasureTextEx(font, "Created by Juan Digilio", fontSize * 0.65f, spacing / 4.0f).x / 2.0f;
		actualPos.y -= 60;
		DrawTextEx(font, "Created by Juan Digilio", actualPos, fontSize * 0.65f, spacing / 4.0f, BLACK);

		actualPos = playPosCenter;

		actualPos.x = actualPos.x + gameScreen.width * 2.0f - MeasureTextEx(font, "Game art by Juan Digilio", fontSize * 0.4f, spacing / 8.0f).x / 2.0f;
		DrawTextEx(font, "Game art by Juan Digilio", actualPos, fontSize * 0.4f, spacing / 8.0f, BLACK);

		actualPos = playPosCenter;

		actualPos.x = actualPos.x + gameScreen.width * 2.0f - MeasureTextEx(font, "Cars assets by TheMemeLord4", fontSize * 0.25f, spacing / 8.0f).x / 2.0f;
		actualPos.y += 60;
		DrawTextEx(font, "Cars assets by TheMemeLord4", actualPos, fontSize * 0.25f, spacing / 8.0f, BLACK);
	}
}