#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <ostream>
#include <raylib.h>
#include "raylib-aseprite.h"
#include "constants.hpp"
#include "enum.hpp"
#include "spriteUtils.hpp"

namespace PlayerUtils {
    struct Player{
        Aseprite sprite;
        float x,y,spawnRadius;
        Vector2 movementVelocity{0,1};
        int jumpHeight = 15;
        int weight = 20;

        PlayerState currentState = PlayerState::Falling;
        SpriteUtils::AsepriteTagEX currentAnimation;
        SpriteUtils::AsepriteTagEX newAnimation;

        int coyoteTime = 2 * TARGET_FPS; //How many frames after leaving a platform the player can still jump
        int coyoteTimer = 0; //Current frame count since leaving a platform

        float timeFallingDown = 0; //Time spent where the player is pressing to move down
        int maxFallingSpeed = 3;

        bool isTouchingGround = false;
        bool isFalling = true;

        FrictionLevel currentFriction = FrictionLevel::Normal;

        Player () {
            this->sprite = Aseprite{nullptr};
            this->x = 0;
            this->y = 0;
            this->spawnRadius = 10;
        }

        Player (Aseprite sprite,int x, int y, int spawnRadius ) : currentAnimation(LoadAsepriteTag(sprite,GetStateAsChar()),false), newAnimation(currentAnimation) {
            this->sprite = sprite;
            this->x = x;
            this->y = y;
            this->spawnRadius = spawnRadius;
        } ;

        bool CanJump() const{
            return isTouchingGround;
        }

        Vector2 AsVector2() const{
            return Vector2(x,y);
        }

        void ChangeState(PlayerState newState) {
            if (currentState == newState) return;

            currentState = newState;
            std::cout << GetStateAsChar() << "||" << currentAnimation.baseTag.name << std::endl;
            std::cout << currentAnimation.frameAmount << std::endl;

            if (currentAnimation.requireAnimationComplete) {
                if (currentAnimation.IsAnimComplete()) {
                    std::cout << "True" << std::endl;
                    currentAnimation = newAnimation;
                    newAnimation = SpriteUtils::AsepriteTagEX{};
                }
                newAnimation = SpriteUtils::CreateAsepriteTagEX(sprite, GetStateAsChar(),DoesAnimationRequireCompletion());
            }else {
                currentAnimation = SpriteUtils::CreateAsepriteTagEX(sprite, GetStateAsChar(),DoesAnimationRequireCompletion());
            }

            //currentAnimation = SpriteUtils::CreateAsepriteTagEX(sprite, "Falling_Start",false);
        }

        char* GetStateAsChar() const{
            switch (currentState) {
                case PlayerState::Idle:
                    return "Idle";
                case PlayerState::Jumping:
                    return "Jump";
                case PlayerState::Falling:
                    return "Falling_Loop";
                case PlayerState::Landed:
                    return "Landing";
                case PlayerState::Moving_L:
                    return "Moving_L";
                case PlayerState::Moving_R:
                    return "Moving_R";
                default:
                    return "Unknown";
            }
        }

        bool DoesAnimationRequireCompletion() const{
            switch (currentState) {
                case PlayerState::Landed:
                    return true;
                default:
                    return false;
            }
        }
    };

    Player CreatePlayer(Aseprite sprite,float spawnX,float spawnY, float spawnRadius);

    void UpdatePlayer(Player &player);

    void HandleFloorCollision(Player &player);

    void DoJump(Player &player);

    void FireBullet(Player &player);

    void DrawPlayer(const Player &player);
}

#endif
