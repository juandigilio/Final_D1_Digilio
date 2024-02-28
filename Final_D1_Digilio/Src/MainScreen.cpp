#include "MainScreen.h"

#include <iostream>

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
	bool isLeftButtonHold = false;

	bool isRightButtonPressed = false;
	bool isRightButtonHold = false;

	bool isEnterButtonPressed = false;
	bool isEnterButtonHold = false;

	bool isComputerOn = false;
	
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

	static void DrawButton(Texture2D button, Vector2 buttonPos, bool isButtonHold)
	{
		Vector2 origin = { 0, 0 };
		Rectangle dest = { buttonPos.x, buttonPos.y, button.width / 2.0f,  static_cast<float>(button.height) };
		Rectangle source;

		if (isButtonHold)
		{
			source = { button.width / 2.0f, 0.0f, button.width / 2.0f, static_cast<float>(button.height) };
		}
		else
		{
			source = { 0.0f, 0.0f, button.width / 2.0f, static_cast<float>(button.height) };
		}

		DrawTexturePro(button, source, dest, origin, 0.0f, RAYWHITE);
	}

	static void CheckButtonsCollision(Player& player)
	{
		Rectangle rightRec = {rightButtonPos.x, rightButtonPos.y, rightButton.width / 2.0f, rightButton.height * 1.0f };
		Rectangle enterRec = {enterButtonPos.x, enterButtonPos.y, enterButton.width / 2.0f, enterButton.height * 1.0f };
		Rectangle leftRec = {leftButtonPos.x, leftButtonPos.y, leftButton.width / 2.0f, leftButton.height * 1.0f };

		if (CheckCollisionRecs(player.collisionBox, leftRec))
		{
			if (!isLeftButtonHold)
			{
				isLeftButtonPressed = true;
				isLeftButtonHold = true;
			}
		}
		else
		{
			isLeftButtonHold = false;
		}

		if (CheckCollisionRecs(player.collisionBox, rightRec))
		{
			if (!isRightButtonHold)
			{
				isRightButtonPressed = true;
				isRightButtonHold = true;
			}
		}
		else
		{
			isRightButtonHold = false;
		}

		if (CheckCollisionRecs(player.collisionBox, enterRec))
		{
			if (!isEnterButtonHold)
			{
				isEnterButtonPressed = true;
				isEnterButtonHold = true;
			}

			if (!isComputerOn)
			{
				isComputerOn = true;
				isEnterButtonPressed = false;
			}
		}
		else
		{
			isEnterButtonHold = false;
		}
	}

	static void DrawMainScreen(Player& player)
	{
		DrawTexture(mainBackground, 0, 0, WHITE);

		DrawButton(leftButton, leftButtonPos, isLeftButtonHold);
		DrawButton(rightButton, rightButtonPos, isRightButtonHold);
		DrawButton(enterButton, enterButtonPos, isEnterButtonHold);

		PlayerUtilities::DrawPlayer(player);
	}

	void RunMainScreen(Player& player, GameScreen& currentScreen)
	{
		PlayerUtilities::UpdatePlayer(player, currentScreen);

		CheckButtonsCollision(player);

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