#include "Player.h"

#include <iostream>

#include "raymath.h"


using namespace std;


namespace PlayerUtilities
{
	void LoadPlayer(Player& player)
	{
        player.texture = LoadTexture("Assets/Images/Main/Player.png");
        player.position.x = static_cast<float>(screenWidth - player.texture.width);
        player.position.y = static_cast<float>(screenHeight - player.texture.height * 1.5f);
        player.source = { 0, 0, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
        player.frame = 0;       
        player.lastFrame = 0.0f;

        player.collisionBox.width = 45.0f;
        player.collisionBox.height = 7.0f;
	}

    static void MovePlayer(Player& player)
    {
        player.position.x += player.velocity.x * GetFrameTime();
        player.position.y += player.velocity.y * GetFrameTime();

        player.collisionBox.x = player.position.x + 70.0f;
        player.collisionBox.y = player.position.y + 127.0f;

        if (player.position.x > screenWidth - (player.texture.width / 3.0f))
        {
            player.position.x = static_cast<float>(screenWidth) - (player.texture.width / 3.0f);
        }
        else if (player.position.x < 0.0f)
        {
            player.position.x = 0.0f;
        }

        if (player.position.y > screenHeight - player.texture.height)
        {
            player.position.y = static_cast<float>(screenHeight) - static_cast<float>(player.texture.height);
        }
        else if (player.position.y < 500.0f)
        {
            player.position.y = 500.0f;
        }
    }

	void GetPlayerInput(Player& player, GameScreen& currentScreen)
	{
        SetExitKey(KEY_Q);

        if (IsKeyDown(KEY_UP))
        {
            player.velocity.y = (- player.maxSpeed);
            player.isWalking = true;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            player.velocity.y = (player.maxSpeed);
            player.isWalking = true;
        }
        else
        {
            player.velocity.y = 0.0f;
        }

        if (IsKeyDown(KEY_LEFT))
        {
            player.velocity.x = (-player.maxSpeed);
            player.isWalking = true;
            player.lookingLeft = true;
            player.lookingRight = false;
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            player.velocity.x = (player.maxSpeed);
            player.isWalking = true;
            player.lookingLeft = false;
            player.lookingRight = true;
        }
        else
        {
            player.velocity.x = 0.0f;
        }

        if (player.velocity.x == 0.0f && player.velocity.y == 0.0f)
        {
            player.isWalking = false;
        }

        double elapsedTime = GetTime() - pauseTimer;

        if (IsKeyDown(KEY_ESCAPE) && elapsedTime > pauseDelay)
        {
            currentScreen = GameScreen::PAUSE;
        }
	}

	void UpdatePlayer(Player& player, GameScreen& currentScreen)
	{
        MovePlayer(player);

        GetPlayerInput(player, currentScreen);
	}

	void DrawPlayer(Player& player)
	{
        Vector2 origin = { 0.0f, 0.0f };
        Rectangle dest = { player.position.x, player.position.y, (player.texture.width / 3.0f), static_cast<float>(player.texture.height) };

        float playerWidth = player.texture.width / 3.0f;

        if (player.lookingRight)
        {
            playerWidth *= -1.0f;
        }

        if (player.isWalking)
        {
            switch (player.frame)
            {
                case 0:
                {
                    player.source = { (player.texture.width / 3.0f), 0, playerWidth, static_cast<float>(player.texture.height) };
                    DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
                    break;
                }
                case 1:
                {
                    player.source = { (player.texture.width / 3.0f) * 2, 0, playerWidth, static_cast<float>(player.texture.height) };
                    DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
                    break;
                }
            }

            double elapsedTime = GetTime() - player.lastFrame;

            if (elapsedTime > 0.04f)
            {
                player.frame++;

                player.lastFrame = GetTime();

                if (player.frame > 1)
                {
                    player.frame = 0;
                }
            }
        }
        else
        {
            player.source = { 0.0f, 0.0f, playerWidth, static_cast<float>(player.texture.height) };
            DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
        }
	}

    void UnloadPlayerTexture(Player& player)
    {
        UnloadTexture(player.texture);
    }
}