#include "player.h"
#include "raylib.h"

Player CreatePlayer(float spawnX,float spawnY, float spawnRadius) {
    return { spawnX, spawnY, spawnRadius};
}

Vector2 GetPlayerLocAsVector2(const Player &player){
    Vector2 vec2 = {player.x,player.y};
    return vec2;
}

void HandlePlayerVelocity(Player &player){
    //Moving right
    if(player.movementVelocity.x > 2){
        player.movementVelocity.x = 2;
    }

    //Moving down
    if(player.movementVelocity.y > 5){
        player.movementVelocity.y = 2;
    }

    //Moving left
    if(player.movementVelocity.x < -2){
        player.movementVelocity.x = -2;
    }

    //Moving up 
    if(player.movementVelocity.y < 0){
        player.movementVelocity.y = 0;
    }

    player.x += player.movementVelocity.x;
    player.y += player.movementVelocity.y;
}

void DrawPlayer(Player &player) {
    DrawCircle((int)player.x, (int)player.y, (int)player.spawnRadius, WHITE);
}
