#include <iostream>
#include <algorithm>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <queue>
#include <type_traits>
#include <concepts>
#include "player.hpp"
#include "enemy.hpp"
#include "constants.hpp"
#include "platform.hpp"
#include "backdrop.hpp"
#include "enum.hpp"

PlayerUtils::Player player;
int score;

void ClampRef(float &value, float min, float max) {
    value = Clamp(value, min, max);
}

void DrawBackdrop(BackgroundElements::Backdrop &backdrop, const PlayerUtils::Player &player, const Camera2D &camera) {
    if (backdrop.position.y + backdrop.texture.height < GetScreenToWorld2D({0,0},camera).y) {
        backdrop.position.y += backdrop.texture.height;
    }

    DrawTexture(backdrop.texture, 0, backdrop.position.y , WHITE);
    DrawTexture(backdrop.texture, 0, backdrop.position.y  + backdrop.texture.height, WHITE);
}

int main(){
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Drop");
    SetTargetFPS(TARGET_FPS);

    Camera2D camera = { 0 };
    player = PlayerUtils::CreatePlayer(200,200,10);

    camera.offset = { SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int frameCounter = 0;

    Texture2D background = LoadTexture("C:/Users/conne/CLionProjects/Pocket-Dropper/Resources/backDrop.png");
    Texture2D ice = LoadTexture("C:/Users/conne/CLionProjects/Pocket-Dropper/Resources/Ice-Block.png");
    Texture2D projectile = LoadTexture("Projectile_Nail.png");

    PlatformUtils::SummonPlatform(ice,player, camera, FrictionLevel::Slippery);

    Enemys::Enemy enemy(100, {SCREEN_WIDTH/2, PlatformUtils::platforms[0].body.position.y - 10}, 10);
    enemy.heath = 10;

    BackgroundElements::Backdrop backdrop(background, GetScreenToWorld2D({0,(float)background.height / 2},camera));

    while(!WindowShouldClose()){
        // Update camera target to player's world position so the camera follows the player
        camera.target = { SCREEN_WIDTH / 2, player.y };

        Vector2 topLeftWorld = GetScreenToWorld2D({ 0, 0 }, camera);
        PlatformUtils::SummonPlatform(ice,player, camera, FrictionLevel::Slippery);

        frameCounter++;

        //Ammend score every second 
        if(frameCounter % TARGET_FPS == 0){
           score += 1;
        } 

        if (IsKeyDown(KEY_A)) player.movementVelocity.x = -5;
        if (IsKeyDown(KEY_D)) player.movementVelocity.x = 5;

        if (IsKeyPressed(KEY_SPACE) && player.CanJump()) player.movementVelocity.y -= player.jumpHeight;

        if (player.x < 0 + player.spawnRadius) player.x = 0 + player.spawnRadius;
        if (player.x > SCREEN_WIDTH - player.spawnRadius) player.x = SCREEN_WIDTH - player.spawnRadius;

        if (PlatformUtils::CheckPlayerCollisions(player)) {
            PlayerUtils::HandleFloorCollision(player);
        }else {
            player.coyoteTimer += 1;

            if (!player.coyoteTimer <= player.coyoteTime) {
                player.isTouchingGround = false;
            }
        }

        PlayerUtils::UpdatePlayer(player);
        Enemys::UpdateEnemy(enemy);

        // Start drawing and apply camera transform
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
                DrawBackdrop(backdrop, player, camera);
                PlatformUtils::DrawPlatformsOnScreen(player,camera);
                PlayerUtils::DrawPlayer(player);
                Enemys::DrawEnemy(enemy);
                DrawText(std::to_string(score).c_str(),topLeftWorld.x + 10,topLeftWorld.y,100,GREEN);
            EndMode2D();
        EndDrawing();
    }
    
    UnloadTexture(background);
    CloseWindow();
    return 0;
}