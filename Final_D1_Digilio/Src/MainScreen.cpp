#include "MainScreen.h"

#include "GameData.h"

namespace MainScreen
{
	Texture2D mainBackground;

	Rectangle pad = { 90.0f, 590.0f,167.0f, 121.0f };

	Texture2D leftButton;
	Vector2 leftButtonPos;

	Texture2D rightButton;
	Vector2 rightButtonPos;

	Texture2D enterButton;
	Vector2 enterButtonPos;

	bool isLeftButtonPressed = false;
	bool isRightButtonPressed = false;
	bool isEnterButtonPressed = false;

	
	static void SetButtonsPositions()
	{
		enterButtonPos.x = pad.x + (pad.width / 2.0f) - (enterButton.width / 4.0f);
		enterButtonPos.y = pad.y - 15.0f;

		leftButtonPos.x = pad.x + 15.0f;
		leftButtonPos.y = enterButtonPos.y + enterButton.height;

		rightButtonPos.x = leftButtonPos.x + (leftButton.width / 2.0f) + 10.0f;
		rightButtonPos.y = leftButtonPos.y - 5.0f;
	}

	void LoadAssets(Player& player)
	{
		mainBackground = LoadTexture("Assets/Images/Main/MainBackground.png");
		leftButton = LoadTexture("Assets/Images/Main/LeftButton.png");
		rightButton = LoadTexture("Assets/Images/Main/RightButton.png");
		enterButton = LoadTexture("Assets/Images/Main/EnterButton.png");

		PlayerUtilities::LoadPlayer(player);

		GameData::font = LoadFont("Assets/Fonts/Minecraft.TTF");

		SetButtonsPositions();
	}

	static void DrawButton(Texture2D button, Vector2 buttonPos, bool isButtonPressed)
	{
		Vector2 origin = { 0, 0 };
		Rectangle dest = { buttonPos.x, buttonPos.y, button.width / 2.0f,  static_cast<float>(button.height) };
		Rectangle source;

		if (isButtonPressed)
		{
			source = { button.width / 2.0f, 0.0f, button.width / 2.0f, static_cast<float>(button.height) };
		}
		else
		{
			source = { 0.0f, 0.0f, button.width / 2.0f, static_cast<float>(button.height) };
		}

		DrawTexturePro(button, source, dest, origin, 0.0f, RAYWHITE);
	}

	static void DrawMainScreen(Player& player)
	{
		DrawTexture(mainBackground, 0, 0, WHITE);

		DrawButton(leftButton, leftButtonPos, isLeftButtonPressed);
		DrawButton(rightButton, rightButtonPos, isRightButtonPressed);
		DrawButton(enterButton, enterButtonPos, isEnterButtonPressed);

		PlayerUtilities::DrawPlayer(player);
	}

	void RunMainScreen(Player& player, GameScreen& currentScreen)
	{
		PlayerUtilities::UpdatePlayer(player, currentScreen);
		DrawMainScreen(player);

	}

	void UnloadMainTextures()
	{
		UnloadTexture(mainBackground);
		UnloadTexture(leftButton);
		UnloadTexture(rightButton);
		UnloadTexture(enterButton);
		
		UnloadFont(GameData::font);
	}
}