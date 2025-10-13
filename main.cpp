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
#include "weapon.hpp"

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

void HandlePlayingLoop(Camera2D &camera, int frameCounter, Texture2D ice, Enemys::Enemy basePlatformEnemy, BackgroundElements::Backdrop backdrop) {
    // Update camera target to player's world position so the camera follows the player
    camera.target = { SCREEN_WIDTH / 2, player.y - player.movementVelocity.y };

    Vector2 topLeftWorld = GetScreenToWorld2D({ 0, 0 }, camera);


    PlatformUtils::SummonPlatform(ice,player, camera, FrictionLevel::Slippery,GetRandomValue(0,10) > 7 ? basePlatformEnemy : Enemys::Enemy{});

    frameCounter++;

    //Ammend score every second
    if(frameCounter % TARGET_FPS == 0){
        score += 1;
    }

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) player.movementVelocity.x = -5;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) player.movementVelocity.x = 5;

    if (IsKeyPressed(KEY_SPACE)) {
        if (player.CanJump()) player.movementVelocity.y -= player.jumpHeight;
        else PlayerUtils::FireBullet(player);
    };

    if (player.x < 0 + player.spawnRadius) player.x = 0 + player.spawnRadius;
    if (player.x > SCREEN_WIDTH - player.spawnRadius) player.x = SCREEN_WIDTH - player.spawnRadius;

    if (PlatformUtils::CheckPlayerCollisions(player)) {
        PlayerUtils::HandleFloorCollision(player);
    }else {
        //Handle Coyote Time
        player.coyoteTimer += 1;

        if (player.coyoteTimer <= player.coyoteTime) {
            player.isTouchingGround = false;
        }
    }


    Enemys::HandleAllEnemyCollision(player);
    PlayerUtils::UpdatePlayer(player);
    WeaponUtils::UpdateBullets();
    Enemys::UpdateEnemies();
    PlatformUtils::HandlePlatformDespawn(camera);

    std::cout << PlatformUtils::platforms.size() << std::endl;

    // Start drawing and apply camera transform
    BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        DrawBackdrop(backdrop, player, camera);
        PlatformUtils::DrawPlatformsOnScreen(player,camera);
        PlayerUtils::DrawPlayer(player);
        Enemys::DrawEnemiesOnScreen();
        DrawText(std::to_string(score).c_str(),topLeftWorld.x + 10,topLeftWorld.y,100,GREEN);
        EndMode2D();
    EndDrawing();
}

int main(){
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Drop");
    SetTargetFPS(TARGET_FPS);

    GameState gameState = Playing;
    Camera2D camera = { 0 };
    player = PlayerUtils::CreatePlayer(200,200,10);

    camera.offset = { SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int frameCounter = 0;

    //Loads all needed textures into SpriteUtils namespace
    SpriteUtils::InitalizeTextures();

    //This exists more a pre-contructed enemy to be used on platforms - Move into Enemy namespace later
    Enemys::Enemy basePlatformEnemy(
        1,
         SpriteUtils::enemyTex,
        {SCREEN_WIDTH/2, 0},
        10,
        SpriteUtils::enemyTex.height / 2);

    BackgroundElements::Backdrop backdrop(SpriteUtils::background, GetScreenToWorld2D({0,(float)SpriteUtils::background.height / 2},camera));

    while(!WindowShouldClose()){
        switch (gameState) {
            case Playing:
                HandlePlayingLoop(camera, frameCounter, SpriteUtils::ice, basePlatformEnemy, backdrop);
                if (IsKeyDown(KEY_P)) gameState = Paused;
                break;
            case Paused:
                BeginDrawing();
                ClearBackground(RAYWHITE);
                BeginMode2D(camera);
                    DrawText("Wow what a cool piece of pausing you did there well done champ", 100,100,20,BLACK);
                EndMode2D();
                EndDrawing();
                break;
        }

    }
    
    UnloadTexture(SpriteUtils::background);
    CloseWindow();
    return 0;
}
