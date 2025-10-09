#include "player.hpp"
#include "constants.hpp"
#include "raymath.h"
#include <raylib.h>

namespace PlayerUtils {
    Player CreatePlayer(float spawnX,float spawnY, float spawnRadius) {
        return { spawnX, spawnY, spawnRadius};
    }

    void HandleFloorCollision(Player &player) {
        if (player.isTouchingGround) return;

        player.isTouchingGround = true;
        player.isFalling = false;
        player.movementVelocity.y = 0;
        player.movementVelocity.x = 0;
        player.timeFallingDown = 0;
    }

    void UpdatePlayer(Player &player) {
        if (!player.isTouchingGround && player.movementVelocity.y >= 0) {
            player.isFalling = true;
            player.timeFallingDown += GetFrameTime();
            player.movementVelocity.y = GRAVITY * player.weight * (1 + player.timeFallingDown) * GetFrameTime();
        }else if (player.movementVelocity.y < 0) {
            player.movementVelocity.y += 1;;
        }else {
            player.isFalling = false;
        }

        player.x += player.movementVelocity.x;
        player.y += player.movementVelocity.y;

        player.movementVelocity.x = 0;
    }

    void DrawPlayer(const Player &player) {
        DrawCircle((int)player.x, (int)player.y, player.spawnRadius, RED);
    }
}