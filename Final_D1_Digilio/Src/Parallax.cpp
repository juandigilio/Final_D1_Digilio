#include "Parallax.h"

#include "raylib.h"

#include "GameData.h"

using namespace GameData;

namespace Parallax
{
	Texture2D gameBackground;
	Vector2 backgroundPos;
	Vector2 backgroundPos2;

	void InitParallax()
	{
		gameBackground = LoadTexture("Assets/Images/Game/RoadBackground.png");

		backgroundPos.x = gameScreen.x;
		backgroundPos.y = gameScreen.y - gameBackground.height + gameScreen.height;

		backgroundPos2.x = backgroundPos.x;
		backgroundPos2.y = backgroundPos.y - gameBackground.height;
	}

	void UpdateParallax(float actualSpeed)
	{
		float limit = gameScreen.y + gameScreen.height;

		actualSpeed *= 2.5f;

		backgroundPos.y += actualSpeed * GetFrameTime();
		backgroundPos2.y += actualSpeed * GetFrameTime();

		if (backgroundPos.y > limit)
		{
			backgroundPos.y = backgroundPos2.y - gameBackground.height;
		}
		else if (backgroundPos2.y > limit)
		{
			backgroundPos2.y = backgroundPos.y - gameBackground.height;
		}
	}

	void DrawParallax()
	{
		DrawTextureV(gameBackground, backgroundPos, RAYWHITE);
		DrawTextureV(gameBackground, backgroundPos2, RAYWHITE);
	}

	void UnloadParallaxAssets()
	{
		UnloadTexture(gameBackground);
	}
}