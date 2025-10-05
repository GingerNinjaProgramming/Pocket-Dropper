#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "constants.h"
#include "enums.h"

struct Player{
    Texture2D sprite;

    float x,y;
    Vector2 movementVelocity{0,0};
    int weight = 5;

    PlayerPosition mapPos = Center;

    float timeFallingDown = 0; //Time spent where the player is pressing to move down
    int maxFallingSpeed = 100;

    int fallingOffset = 0;

    bool isDashing = false;
    Vector2 dashPulse{1,1};

};

Player CreatePlayer(Texture2D sprite,float spawnX,float spawnY);

Vector2 GetPlayerLocAsVector2(const Player &player);

void DrawPlayer(const Player &player);

void DoDash(Player &player);
#endif