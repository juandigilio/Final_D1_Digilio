#pragma once

#include "raylib.h"

#include "GameData.h"


using namespace GameData;


struct Player
{
    Vector2 position{};
    Vector2 velocity{};
    float maxSpeed = 150.0f;

    int line = 2;

    Texture2D texture{};
    Rectangle source{};
    Rectangle collisionBox{};
    int frame{};
    double lastFrame = 0.0f;
    bool isWalking = false;
    bool lookingRight = false;
    bool lookingLeft = true;

    Texture carTexture{};
    Vector2 carPosition{};


    Vector2 GetCenter()
    {
        return { position.x + (texture.width / 2), position.y + (texture.width / 2) };
    }
};

namespace PlayerUtilities
{
    extern void LoadPlayer(Player& player);

    extern void GetPlayerInput(Player& player);

    extern void UpdatePlayer(Player& player);

    extern void DrawPlayer(Player& player);

    extern void UnloadPlayerTexture(Player& player);
}