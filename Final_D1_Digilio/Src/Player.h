#pragma once

#include "raylib.h"

#include "GameData.h"


using namespace GameData;

static const int maxBulletsQnty = 30;

struct Player
{
    Vector2 position{};
    Vector2 velocity{};
    float rotation = 0.0f;
    float maxSpeed{};

    bool isAlive = true;

    Texture2D texture{};
    Rectangle source{};
    int frame{};
    double lastFrame{};
    bool isWalking = false;
    float lastCollide = 0.0f;


    Vector2 GetCenter()
    {
        return { position.x + (texture.width / 2), position.y + (texture.width / 2) };
    }
};

namespace PlayerUtilities
{
    extern void LoadPlayer(Player& player1, Player& player2, Player& player3);

    extern void GetPlayerInput(Player& player, GameSceen& currentSceen);

    extern void UpdatePlayer(Player& player, Rectangle level);

    extern void DrawPlayer(Player& player);

    extern void UnloadPlayerTexture(Player& player);
}