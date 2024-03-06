#include "MainScreen.h"

#include "GameData.h"

using namespace GameData;


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

	Texture2D itchIo;
	Vector2 itchIoPos;

	Texture2D gitHub;
	Vector2 gitHubPos;

	Sound keySound;

	bool isLeftButtonPressed = false;
	bool isLeftButtonHold = false;

	bool isRightButtonPressed = false;
	bool isRightButtonHold = false;

	bool isEnterButtonPressed = false;
	bool isEnterButtonHold = false;

	bool isItchIoHold = false;
	bool isGitHubHold = false;

	bool isComputerOn = false;
	
	static void SetButtonsPositions()
	{
		enterButtonPos.x = pad.x + (pad.width / 2.0f) - (enterButton.width / 4.0f);
		enterButtonPos.y = pad.y - 15.0f;

		leftButtonPos.x = pad.x + 15.0f;
		leftButtonPos.y = enterButtonPos.y + enterButton.height;

		rightButtonPos.x = leftButtonPos.x + (leftButton.width / 2.0f) + 10.0f;
		rightButtonPos.y = leftButtonPos.y - 5.0f;

		itchIoPos.x = static_cast<float>(screenWidth) - itchIo.width;
		itchIoPos.y = pad.y - 40.0f;

		gitHubPos.x = itchIoPos.x;
		gitHubPos.y = itchIoPos.y + itchIo.height;
	}

	void LoadAssets(Player& player)
	{
		mainBackground = LoadTexture("Assets/Images/Main/MainBackground.png");
		leftButton = LoadTexture("Assets/Images/Main/LeftButton.png");
		rightButton = LoadTexture("Assets/Images/Main/RightButton.png");
		enterButton = LoadTexture("Assets/Images/Main/EnterButton.png");

		itchIo = LoadTexture("Assets/Images/ItchIo.png");
		gitHub = LoadTexture("Assets/Images/GitHub.png");

		keySound = LoadSound("Assets/Sounds/KeySound.wav");
		gameplayMusic = LoadMusicStream("Assets/Sounds/GamePlayMusic.wav");

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

		Rectangle itchIoRec = {itchIoPos.x, itchIoPos.y, itchIo.width / 2.0f, itchIo.height * 1.0f };
		Rectangle gitHubRec = {gitHubPos.x, gitHubPos.y, gitHub.width / 2.0f, gitHub.height * 1.0f };

		if ( CheckCollisionRecs(player.collisionBox, leftRec))
		{
			if (!isLeftButtonHold)
			{
				isLeftButtonPressed = true;
				isLeftButtonHold = true;
				PlaySound(keySound);
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
				PlaySound(keySound);
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
				PlaySound(keySound);
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

		if (CheckCollisionRecs(player.collisionBox, itchIoRec))
		{
			if (!isItchIoHold)
			{
				OpenURL("https://juandigilio.itch.io");

				isItchIoHold = true;
			}
		}
		else
		{
			isItchIoHold = false;
		}
		

		if (CheckCollisionRecs(player.collisionBox, gitHubRec))
		{
			if (!isGitHubHold)
			{
				OpenURL("https://github.com/juandigilio");

				isGitHubHold = true;
			}
		}
		else
		{
			isGitHubHold = false;
		}
	}

	static void DrawMainScreen(Player& player)
	{
		DrawTexture(mainBackground, 0, 0, WHITE);

		DrawTextureV(itchIo,itchIoPos, WHITE);
		DrawTextureV(gitHub,gitHubPos, WHITE);

		DrawButton(leftButton, leftButtonPos, isLeftButtonHold);
		DrawButton(rightButton, rightButtonPos, isRightButtonHold);
		DrawButton(enterButton, enterButtonPos, isEnterButtonHold);

		PlayerUtilities::DrawPlayer(player);
	}

	static void CheckWiningCondition()
	{
		if (hasWon)
		{
			currentScreen = GameScreen::MENU;

			hasWon = false;
		}
	}

	void RunMainScreen(Player& player)
	{
		PlayerUtilities::UpdatePlayer(player);

		CheckWiningCondition();

		CheckButtonsCollision(player);

		DrawMainScreen(player);
	}

	void UnloadMainAssets()
	{
		UnloadTexture(mainBackground);
		UnloadTexture(leftButton);
		UnloadTexture(rightButton);
		UnloadTexture(enterButton);

		UnloadTexture(itchIo);
		UnloadTexture(gitHub);

		UnloadSound(keySound);
		UnloadMusicStream(gameplayMusic);
		
		UnloadFont(GameData::font);
	}
}