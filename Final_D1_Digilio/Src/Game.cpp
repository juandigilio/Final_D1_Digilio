#include "Game.h"

#include "raylib.h"

#include <iostream>

#include "GameData.h"
#include "MainScreen.h"
#include "Player.h"
#include "Parallax.h"


using namespace std;

using namespace GameData;
using namespace MainScreen;


namespace Game
{
	struct Enemy
	{
		Texture2D texture{};
		Vector2 position{};
		bool isStoped = true;
	};


	const int enemiesQnty = 3;
	Enemy enemies[enemiesQnty];

	float line1;
	float line2;
	float line3;

	bool isMovingLeft = false;
	bool isMovingRight = false;

	bool firstTime = true;

	bool firstDrop = true;
	int nextToDrop = 0;
	double lastDrop = 0.0f;
	double spawnRateBase = 5.4f;
	double spawnRateHardness = spawnRateBase;
	float actualSpeed;
	float baseSpeed = 60.0f;

	int score = 0;
	int highScore = 0;
	double scoreTimer = 0.0f;

	
	static void InitGame(Player& player)
	{
		enemies[0].texture = LoadTexture("Assets/Images/Game/Cars/Enemy1.png");
		enemies[1].texture = LoadTexture("Assets/Images/Game/Cars/Enemy2.png");
		enemies[2].texture = LoadTexture("Assets/Images/Game/Cars/Enemy3.png");

		line1 = gameScreen.x + 265.0f - (player.carTexture.width / 2.0f);
		line2 = gameScreen.x + 433.0f - (player.carTexture.width / 2.0f);
		line3 = gameScreen.x + 601.0f - (player.carTexture.width / 2.0f);

		actualSpeed = baseSpeed;

		player.carPosition.x = line2;
		player.carPosition.y = gameScreen.y + gameScreen.height - player.texture.height;
	}

	static void ResetGame(Player& player)
	{
		actualSpeed = baseSpeed;
		spawnRateHardness = spawnRateBase;

		player.carPosition.x = line2;

		for (int i = 0; i < enemiesQnty; i++)
		{
			enemies[i].isStoped = true;
		}

		if (score > highScore)
		{
			highScore = score;
		}

		score = 0;

		firstDrop = true;


		isMovingLeft = false;
		isMovingRight = false;
	}

	static void SetEnemyPosition(Enemy& enemy)
	{
		int newPos = (rand() % 3) + 1;

		switch (newPos)
		{
			case 1:
			{
				enemy.position.x = line1;
				break;
			}
			case 2:
			{
				enemy.position.x = line2;
				break;
			}
			case 3:
			{
				enemy.position.x = line3;
				break;
			}
		}

		enemy.position.y = gameScreen.y - enemy.texture.height;	
	}

	static void GetInput(Player& player)
	{
		SetExitKey(KEY_Q);

		if (isLeftButtonPressed && !isRightButtonHold)
		{
			isLeftButtonPressed = false;

			isMovingRight = false;

			if (player.line > 1)
			{
				isMovingLeft = true;

				player.line--;
			}
		}
		else if (isRightButtonPressed && !isLeftButtonHold)
		{
			isRightButtonPressed = false;

			isMovingLeft = false;

			if (player.line < 3)
			{
				isMovingRight = true;

				player.line++;
			}
		}
		else if (isEnterButtonPressed && !isLeftButtonHold && !isRightButtonHold)
		{
			miniGameScreen = SecondScreen::CARSELECTION;

			isEnterButtonPressed = false;

			ResetGame(player);
		}

		if (IsKeyDown(KEY_ESCAPE))
		{
			pauseTimer = GetTime();

			miniGameScreen = SecondScreen::CARSELECTION;
			currentScreen = GameScreen::MENU;

			ResetGame(player);
		}
	}

	static void CheckCollisions(Player& player)
	{
		Rectangle playerRec
		{ 
			player.carPosition.x, 
			player.carPosition.y,
			static_cast<float>(player.carTexture.width),
			static_cast<float>(player.carTexture.height)
		};

		for (int i = 0; i < enemiesQnty; i++)
		{
			if (!enemies[i].isStoped)
			{
				Rectangle enemyRec
				{
					enemies[i].position.x,
					enemies[i].position.y,
					static_cast<float>(enemies[i].texture.width),
					static_cast<float>(enemies[i].texture.height)
				};

				if (CheckCollisionRecs(playerRec, enemyRec))
				{
					miniGameScreen = SecondScreen::LOOSE;

					ResetGame(player);

					break;
				}
			}
			
		}


	}

	static void UpdatePlayerCar(Player& player)
	{
		if (isMovingRight)
		{
			player.carPosition.x += 170 * GetFrameTime();

			if (player.line == 1)
			{
				if (player.carPosition.x >= line1)
				{
					isMovingRight = false;
					player.carPosition.x = line1;
				}
			}
			else if (player.line == 2)
			{
				if (player.carPosition.x >= line2)
				{
					isMovingRight = false;
					player.carPosition.x = line2;
				}
			}
			else if (player.line == 3)
			{
				if (player.carPosition.x >= line3)
				{
					isMovingRight = false;
					player.carPosition.x = line3;
				}
			}
		}
		else if (isMovingLeft)
		{
			player.carPosition.x -= 170 * GetFrameTime();

			if (player.line == 1)
			{
				if (player.carPosition.x <= line1)
				{
					player.carPosition.x = line1;

					isMovingLeft = false;
				}
			}
			else if (player.line == 2)
			{
				if (player.carPosition.x <= line2)
				{
					player.carPosition.x = line2;

					isMovingLeft = false;
				}
			}
			else if (player.line == 3)
			{
				if (player.carPosition.x <= line3)
				{
					player.carPosition.x = line3;

					isMovingLeft = false;
				}
			}
		}
	}

	static void SpawnEnemies()
	{
		int current = nextToDrop - 1;

		if (current < 0)
		{
			current = 2;
		}

		float minY = gameScreen.y + (gameScreen.height / 2.0f);

		bool enoughDistance = (enemies[current].position.y > minY);

		double elapsedTime = GetTime() - lastDrop;

		if (elapsedTime > spawnRateHardness)
		{
			if (firstDrop)
			{
				enemies[nextToDrop].isStoped = false;

				SetEnemyPosition(enemies[nextToDrop]);

				nextToDrop++;

				firstDrop = false;
			}
			else if (enemies[nextToDrop].isStoped && enoughDistance)
			{
				enemies[nextToDrop].isStoped = false;

				SetEnemyPosition(enemies[nextToDrop]);

				nextToDrop++;

				if (nextToDrop > 2)
				{
					nextToDrop = 0;
				}

				lastDrop = GetTime();
			}		
		}
	}

	static void UpdateEnemies()
	{
		float limit = gameScreen.y + gameScreen.height;

		SpawnEnemies();

		for (int i = 0; i < enemiesQnty; i++)
		{
			if (!enemies[i].isStoped)
			{
				enemies[i].position.y += actualSpeed * GetFrameTime();

				if (enemies[i].position.y > limit)
				{
					enemies[i].isStoped = true;
				}
			}
		}
	}

	static void UpdateScore(Player& player)
	{
		double elapsedTime = GetTime() - scoreTimer;

		if (elapsedTime > 0.1f)
		{
			score++;

			scoreTimer = GetTime();
		}

		if (score >= 10)
		{
			ResetGame(player);

			miniGameScreen = SecondScreen::WIN;
		}
		else if(score * 0.3f > baseSpeed)
		{		
			actualSpeed = score * 0.3f;		
		}
	}

	static void Update(Player& player)
	{
		UpdatePlayerCar(player);

		UpdateScore(player);

		UpdateEnemies();

		Parallax::UpdateParallax(actualSpeed);

		CheckCollisions(player);
	}

	static void DrawScore()
	{
		const char* scoreTxt = TextFormat("%i", score);
		
		Vector2 scorePos{gameScreen.x + 40.0f, gameScreen.y + 40.0f};
		
		DrawTextEx(font, scoreTxt, scorePos, fontSize * 1.1f, spacing, WHITE);
	}

	static void DrawGame(Player player)
	{
		Parallax::DrawParallax();

		for (int i = 0; i < enemiesQnty; i++)
		{
			if (!enemies[i].isStoped)
			{
				DrawTextureV(enemies[i].texture, enemies[i].position, RAYWHITE);
			}
		}

		DrawTextureV(player.carTexture, player.carPosition, RAYWHITE);

		DrawScore();
	}

	void PlayGame(Player& player)
	{
		if (firstTime)
		{
			InitGame(player);

			firstTime = false;
		}

		GetInput(player);

		Update(player);

		DrawGame(player);
	}

	void UnloadAssets()
	{
		for (int i = 0; i < enemiesQnty; i++)
		{
			UnloadTexture(enemies[i].texture);
		}

		Parallax::UnloadParallaxAssets();
	}
}