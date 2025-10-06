#include "player.h"
#include "raylib.h"
#include <iostream>

Player CreatePlayer(Texture2D sprite,float spawnX,float spawnY) {
    return { sprite, spawnX, spawnY};
}

Vector2 GetPlayerLocAsVector2(const Player &player){
    Vector2 vec2 = {player.x,player.y};
    return vec2;
}

void DrawPlayer(const Player &player) {
    DrawTexture(player.sprite, (int)player.x + player.movementVelocity.x, (int)player.y, WHITE);
}

void DoDash(Player &player){
    std::cout << "DASH" << std::endl;
    player.isDashing = true;

    player.dashPulse.x = 5;
}