#include "Player.h"

#include <iostream>

#include "raymath.h"


using namespace std;


namespace PlayerUtilities
{
	void LoadPlayer(Player& player1, Player& player2, Player& player3)
	{
        player1.texture = LoadTexture("Assets/Images/ship.png");
        player1.position.x = screenWidth - player1.texture.width;
        player1.position.y = static_cast<float>(screenHeight - screenHeight / 6 - player1.texture.height);
        player1.source = { 0, 0, static_cast<float>(player1.texture.width), static_cast<float>(player1.texture.height) };
        player1.frame = 0;       
        player1.lastFrame = 0.0f;
        
	}

    static void MovePlayer(Player& player, Rectangle level)
    {
        player.position.x += player.velocity.x * GetFrameTime();
        player.position.y += player.velocity.y * GetFrameTime();

        if (player.position.x > screenWidth - static_cast<float>(player.texture.width))
        {
            player.position.x = static_cast<float>(screenWidth) - static_cast<float>(player.texture.width);
        }
        else if (player.position.x < 0.0f)
        {
            player.position.x = 0.0f;
        }
        else if (player.position.y > level.y - player.texture.height)
        {
            player.position.y = level.y + player.texture.height;
        }
        else if (player.position.y < level.y)
        {
            player.position.y = level.y;
        }
    }

	void GetPlayerInput(Player& player, GameSceen& currentSceen)
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
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            player.velocity.x = (player.maxSpeed);
            player.isWalking = true;
        }
        else
        {
            player.velocity.x = 0.0f;
        }

        if (player.velocity.x == 0 && player.velocity.y == 0)
        {
            player.isWalking = false;
        }

        double elapsedTime = GetTime() - pauseTimer;

        if (IsKeyDown(KEY_ESCAPE) && elapsedTime > pauseDelay)
        {
            currentSceen = GameSceen::PAUSE;
        }
	}

	void UpdatePlayer(Player& player, Rectangle level)
	{
        MovePlayer(player, level);
	}

	void DrawPlayer(Player& player)
	{
        const float rotationCenterX = 50.0f;
        const float rotationCenterY = 50.0f;
        Vector2 origin = { rotationCenterX, rotationCenterY };

        if (player.isWalking)
        {
            Rectangle dest = { player.GetCenter().x, player.GetCenter().y, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };

            switch (player.frame)
            {
            case 0:
            {
                player.source = { static_cast<float>(player.texture.width), 0, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
                DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 1:
            {
                player.source = { static_cast<float>(player.texture.width) * 2, 0, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
                DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 2:
            {
                player.source = { static_cast<float>(player.texture.width) * 3, 0, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
                DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 3:
            {
                player.source = { static_cast<float>(player.texture.width) * 4, 0, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
                DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            }

            double elapsedTime = GetTime() - player.lastFrame;

            if (elapsedTime > 0.07f)
            {
                player.frame++;

                player.lastFrame = GetTime();

                if (player.frame > 3)
                {
                    player.frame = 0;
                }
            }
        }
       /* else if (!player.isColliding)
        {
            Rectangle dest = { player.GetCenter().x, player.GetCenter().y, player.width, player.height };
            player.source = { 0, 0, player.width, player.height };

            DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
        }*/

	}

    void UnloadPlayerTextures(Player& player)
    {
        UnloadTexture(player.texture);
    }
}