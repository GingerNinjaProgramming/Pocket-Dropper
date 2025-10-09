#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>

namespace PlayerUtils {
    struct Player{
        float x,y,spawnRadius;
        Vector2 movementVelocity{0,1};
        int jumpHeight = 15;
        int weight = 20;

        float timeFallingDown = 0; //Time spent where the player is pressing to move down
        int maxFallingSpeed = 3;

        bool isTouchingGround = false;
        bool isFalling = true;

        bool CanJump() {
            return isTouchingGround;
        }
    };

    Player CreatePlayer(float spawnX,float spawnY, float spawnRadius);

    void UpdatePlayer(Player &player);

    void HandleFloorCollision(Player &player);

    void DrawPlayer(const Player &player);
}

#endif
