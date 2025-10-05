#include "player.h"
#include "raylib.h"

Player CreatePlayer(Texture2D sprite,float spawnX,float spawnY, float spawnRadius) {
    return { sprite, spawnX, spawnY, spawnRadius};
}

Vector2 GetPlayerLocAsVector2(const Player &player){
    Vector2 vec2 = {player.x,player.y};
    return vec2;
}

void DrawPlayer(const Player &player) {
    DrawTexture(player.sprite, (int)player.x, (int)player.y, WHITE);
}

