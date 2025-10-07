#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "constants.hpp"

namespace PlayerUtils {
    struct Player{
        float x,y,spawnRadius;
        Vector2 movementVelocity{0,0};
        int weight = 5;

        float timeFallingDown = 0; //Time spent where the player is pressing to move down
        int maxFallingSpeed = 3;

        bool isTouchingGround = false;

        bool CanJump() {
            return isTouchingGround;
        }
    };

    Player CreatePlayer(float spawnX,float spawnY, float spawnRadius);

    void UpdatePlayer(Player &player);

    Vector2 GetPlayerLocAsVector2(const Player &player);

    void DrawPlayer(const Player &player);
}

#endif
