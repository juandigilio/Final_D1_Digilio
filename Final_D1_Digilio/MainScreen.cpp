#include "MainScreen.h"


namespace MainScreen
{
	Texture2D mainBackground;

	Texture2D upButton;
	Vector2 upButtonPos;

	Texture2D downButton;
	Vector2 downButtonPos;

	Texture2D leftButton;
	Vector2 leftButtonPos;

	Texture2D rightButton;
	Vector2 rightButtonPos;

	Texture2D enterButton;
	Vector2 enterButtonPos;

	bool isUpButtonPressed = false;
	bool isDownButtonPressed = false;
	bool isLeftButtonPressed = false;
	bool isRightButtonPressed = false;
	bool isEnterButtonPressed = false;

	void LoadAssets()
	{
		mainBackground = LoadTexture("Assets/Images/Main/MainBackground.png");
		upButton = LoadTexture("Assets/Images/Main/UpButton.png");
		downButton = LoadTexture("Assets/Images/Main/DownButton.png");
		leftButton = LoadTexture("Assets/Images/Main/LeftButton.png");
		rightButton = LoadTexture("Assets/Images/Main/RightButton.png");
		enterButton = LoadTexture("Assets/Images/Main/EnterButton.png");
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

	void DrawMainScreen()
	{
		DrawTexture(mainBackground, 0, 0, WHITE);

		DrawButton(upButton, upButtonPos, isUpButtonPressed);
		DrawButton(downButton, downButtonPos, isDownButtonPressed);
		DrawButton(leftButton, leftButtonPos, isLeftButtonPressed);
		DrawButton(rightButton, rightButtonPos, isRightButtonPressed);
		DrawButton(enterButton, enterButtonPos, isEnterButtonPressed);
	}

	void UnloadMainTextures()
	{
		UnloadTexture(mainBackground);
		UnloadTexture(upButton);
		UnloadTexture(downButton);
		UnloadTexture(leftButton);
		UnloadTexture(rightButton);
		UnloadTexture(enterButton);
	}
}