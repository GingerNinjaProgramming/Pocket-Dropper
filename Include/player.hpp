#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>

#include "constants.hpp"
#include "enum.hpp"

namespace PlayerUtils {
    struct Player{
        float x,y,spawnRadius;
        Vector2 movementVelocity{0,1};
        int jumpHeight = 15;
        int weight = 20;

        int coyoteTime = 2 * TARGET_FPS; //How many frames after leaving a platform the player can still jump
        int coyoteTimer = 0; //Current frame count since leaving a platform

        float timeFallingDown = 0; //Time spent where the player is pressing to move down
        int maxFallingSpeed = 3;

        bool isTouchingGround = false;
        bool isFalling = true;

        FrictionLevel currentFriction = FrictionLevel::Normal;

        bool CanJump() {
            return isTouchingGround;
        }

        Vector2 AsVector2() {
            return Vector2(x,y);
        }
    };

    Player CreatePlayer(float spawnX,float spawnY, float spawnRadius);

    void UpdatePlayer(Player &player);

    void HandleFloorCollision(Player &player);

    void DrawPlayer(const Player &player);
}

#endif
