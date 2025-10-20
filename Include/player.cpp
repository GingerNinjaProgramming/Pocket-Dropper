#include "player.hpp"
#include "constants.hpp"
#include "platform.hpp"
#include "raylib-aseprite.h"
#include "weapon.hpp"
#include "raymath.h"
#include <raylib.h>
#include <iostream>

namespace PlayerUtils {
    Player CreatePlayer(Aseprite sprite,float spawnX,float spawnY, float spawnRadius) {
        Player player(sprite, spawnX, spawnY, spawnRadius);
        player.currentAnimation = SpriteUtils::CreateAsepriteTagEX(player.sprite, player.GetStateAsChar(),player.DoesAnimationRequireCompletion());
        return player;
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

        for (auto enemy : Enemys::enemys) {
            if (CheckCollisionRecs(checkRect, enemy->body.AsRect())){
                //Collision should of happened but didnt
                PlayerUtils::HandleFloorCollision(player); //Run regular collision code
                player.y = enemy->body.AsRect().y - player.spawnRadius; //Put player ontop of collided platform
                std::cout << "Collision missed" << std::endl;
                return; //Collision has been found
            }
        }
    }

    void FireBullet(Player &player) {
        WeaponUtils::CreateBullet(SpriteUtils::ice, player );

        player.movementVelocity.y = -(10);
        player.movementVelocity.x *= 1.25;
    }

    void HandlePlayerState(Player &player) {
        if (!player.isTouchingGround) {
            //Player is in the air
            if (player.isFalling && player.timeFallingDown >= 0.125f) {
                //Player is falling in air
                player.ChangeState(PlayerState::Falling);
                return;
            }

            //Player is going up in air
            player.ChangeState(PlayerState::Jumping);
            return;
        }

        //Player is on the ground
        if (player.currentState == PlayerState::Falling) {
            //Player has just landed
            player.ChangeState(PlayerState::Landed);
            return;
        }

        if (player.currentState == PlayerState::Landed) {
            //Player has landed and is now idle
            player.ChangeState(PlayerState::Idle);
            return;
        }

        if (player.movementVelocity.x > 0) {
            //Player is moving on ground to the right
            player.ChangeState(PlayerState::Moving_R);
            return;
        }

        if (player.movementVelocity.x < 0) {
            //Player is moving on ground to the left
            player.ChangeState(PlayerState::Moving_L);
            return;
        }

        //Player is idle on ground
        player.ChangeState(PlayerState::Idle);
    }


    void UpdatePlayer(Player &player){
        UpdateAsepriteTag(&player.currentAnimation.baseTag);
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
        HandlePlayerState(player);

        player.movementVelocity.x *= (float)player.currentFriction / 10;

        //Works to ensure that it clamps at zero for purposes of some checks
        if (abs (player.movementVelocity.x) < 0.1f) {
            player.movementVelocity.x = 0;
        }

    }

    void DrawPlayer(const Player &player) {
        BeginBlendMode(BLEND_ALPHA);
        SpriteUtils::DrawAsepriteTagOffset(player.currentAnimation.baseTag, {(int)player.x, (int)player.y},0,8.0f, WHITE);
        //DrawCircle((int)player.x, (int)player.y, player.spawnRadius, RED);
        EndBlendMode();
        DrawCircleLines((int)player.x, (int)player.y, player.spawnRadius, GREEN);
    }
}

