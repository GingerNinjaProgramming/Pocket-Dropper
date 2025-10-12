#include "player.hpp"
#include "constants.hpp"
#include "platform.hpp"
#include "raymath.h"
#include <raylib.h>
#include <iostream>

namespace PlayerUtils {
    Player CreatePlayer(float spawnX,float spawnY, float spawnRadius) {
        return { spawnX, spawnY, spawnRadius};
    }

    void HandleFloorCollision(Player &player) {
        if (player.isTouchingGround) {
            return;
        }

        player.isTouchingGround = true;
        player.isFalling = false;
        player.coyoteTimer = 0;
        player.movementVelocity.y = 0;
        player.movementVelocity.x = 0;
        player.timeFallingDown = 0;
    }

    void HandleMissedCollision(Player &player,Vector2 previousPos) {
        float x = fminf(player.x, previousPos.x);
        float y = fminf(player.y, previousPos.y);
        float width = fabsf(player.x - previousPos.x);
        float height = fabsf(player.y - previousPos.y);

        Rectangle checkRect = {x,y,width,height};

        for (auto platform : PlatformUtils::platforms) {
            if (CheckCollisionRecs(checkRect, platform.body.AsRect())){
                //Collision should of happened but didnt
                PlayerUtils::HandleFloorCollision(player); //Run regular collision code
                player.y = platform.body.position.y - player.spawnRadius; //Put player ontop of collided platform
                std::cout << "Collision missed" << std::endl;
                return; //Collision has been found
            }
        }
    }

    void UpdatePlayer(Player &player){
        Vector2 previousPos(player.x,player.y);

        if (!player.isTouchingGround && player.movementVelocity.y >= 0) {
            player.isFalling = true;
            player.timeFallingDown += GetFrameTime();
            player.movementVelocity.y = GRAVITY * player.weight * (1 + player.timeFallingDown) * GetFrameTime();
        }else if (player.movementVelocity.y < 0) {
            player.movementVelocity.y += 1;
        }else {
            player.isFalling = false;
        }

        player.x += player.movementVelocity.x;
        player.y += player.movementVelocity.y;

        HandleMissedCollision(player, previousPos);

        player.movementVelocity.x *= (float)player.currentFriction / 10;
    }

    void DrawPlayer(const Player &player) {
        DrawCircle((int)player.x, (int)player.y, player.spawnRadius, RED);
        DrawCircleLines((int)player.x, (int)player.y, player.spawnRadius, GREEN);
    }
}

