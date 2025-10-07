#include "player.hpp"
#include "raylib.h"

namespace PlayerUtils {
    Player CreatePlayer(float spawnX,float spawnY, float spawnRadius) {
        return { spawnX, spawnY, spawnRadius};
    }

    Vector2 GetPlayerLocAsVector2(const Player &player){
        Vector2 vec2 = {player.x,player.y};
        return vec2;
    }

    void UpdatePlayer(Player &player) {
        player.x += player.movementVelocity.x;
        player.y += player.movementVelocity.y;

        player.movementVelocity.x = 0;
    }


    void DrawPlayer(const Player &player) {
        DrawCircle((int)player.x, (int)player.y, (int)player.spawnRadius, WHITE);
    }
}