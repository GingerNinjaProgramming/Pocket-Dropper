#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>

struct Player{
    float x,y,spawnRadius;
    Vector2 movementVelocity{0,0};
};

Player CreatePlayer(float spawnX,float spawnY, float spawnRadius);

Vector2 GetPlayerLocAsVector2(const Player &player);

void HandlePlayerVelocity(Player &player);

void DrawPlayer(Player &player);

#endif