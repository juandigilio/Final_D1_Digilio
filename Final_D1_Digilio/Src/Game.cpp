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

	float actualSpeed;
	float maxSpeed;

	float line1;
	float line2;
	float line3;

	bool isMovingLeft = false;
	bool isMovingRight = false;

	bool firstTime = true;

	int nextToDrop = 0;
	double lastDrop = 0.0f;
	double spawnRateBase = 5.4f;
	double spawnRateHardness = spawnRateBase;
	
	static void InitGame(Player& player)
	{
		enemies[0].texture = LoadTexture("Assets/Images/Game/Cars/Enemy1.png");
		enemies[1].texture = LoadTexture("Assets/Images/Game/Cars/Enemy2.png");
		enemies[2].texture = LoadTexture("Assets/Images/Game/Cars/Enemy3.png");

		line1 = gameScreen.x + 265.0f - (player.carTexture.width / 2.0f);
		line2 = gameScreen.x + 433.0f - (player.carTexture.width / 2.0f);
		line3 = gameScreen.x + 601.0f - (player.carTexture.width / 2.0f);

		actualSpeed = 150.0f;
		maxSpeed = 250.0f;

		player.carPosition.x = line2;
		player.carPosition.y = gameScreen.y + gameScreen.height - player.texture.height;
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

	static void GetInput(Player& player, SecondScreen& secondScreen)
	{
		SetExitKey(KEY_Q);

		if (isLeftButtonPressed)
		{
			isLeftButtonPressed = false;

			isMovingRight = false;

			if (player.line > 1)
			{
				isMovingLeft = true;

				player.line--;
			}
		}
		else if (isRightButtonPressed)
		{
			isRightButtonPressed = false;

			isMovingLeft = false;

			if (player.line < 3)
			{
				isMovingRight = true;

				player.line++;
			}
		}
		else if (isEnterButtonPressed)
		{
			secondScreen = SecondScreen::CARSELECTION;

			isEnterButtonPressed = false;
		}
	}

	static void UpdatePlayerCar(Player& player)
	{
		if (isMovingRight)
		{
			player.carPosition.x += 100 * GetFrameTime();

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
			player.carPosition.x -= 100 * GetFrameTime();

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
		double elapsedTime = GetTime() - lastDrop;
		
		if (elapsedTime > spawnRateHardness)
		{
			if (enemies[nextToDrop].isStoped)
			{
				enemies[nextToDrop].isStoped = false;

				SetEnemyPosition(enemies[nextToDrop]);

				nextToDrop++;

				if (nextToDrop > 2)
				{
					nextToDrop = 0;
				}

				lastDrop = GetTime();

				//cout << "Droped " << nextToDrop << endl;
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

	static void Update(Player& player)
	{
		UpdatePlayerCar(player);

		UpdateEnemies();

		Parallax::UpdateParallax(actualSpeed);
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
	}

	void PlayGame(Player& player, SecondScreen& secondScreen)
	{
		if (firstTime)
		{
			InitGame(player);

			firstTime = false;
		}

		GetInput(player, secondScreen);

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