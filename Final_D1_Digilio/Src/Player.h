#pragma once

#include "raylib.h"

#include "GameData.h"


using namespace GameData;


struct Player
{
    Vector2 position{};
    Vector2 velocity{};
    //float rotation = 0.0f;
    float maxSpeed = 150.0f;

    bool isAlive = true;

    Texture2D texture{};
    Rectangle source{};
    int frame{};
    double lastFrame = 0.0f;
    bool isWalking = false;
    float lastCollide = 0.0f;


    Vector2 GetCenter()
    {
        return { position.x + (texture.width / 2), position.y + (texture.width / 2) };
    }
};

namespace PlayerUtilities
{
    extern void LoadPlayer(Player& player);

    extern void GetPlayerInput(Player& player, GameScreen& currentScreen);

    extern void UpdatePlayer(Player& player, GameScreen& currentScreen);

    extern void DrawPlayer(Player& player);

    extern void UnloadPlayerTexture(Player& player);
}