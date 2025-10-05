#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "constants.h"
#include "enums.h"

struct Player{
    float x,y,spawnRadius;
    Vector2 movementVelocity{0,0};
    int weight = 5;

    PlayerPosition mapPos = Center;

    float timeFallingDown = 0; //Time spent where the player is pressing to move down
    int maxFallingSpeed = 100;

};

Player CreatePlayer(float spawnX,float spawnY, float spawnRadius);

Vector2 GetPlayerLocAsVector2(const Player &player);

void DrawPlayer(const Player &player);


#endif