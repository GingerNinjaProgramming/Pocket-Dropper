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

void HandlePlayingLoop(Camera2D &camera, int frameCounter, Texture2D ice, Enemys::Enemy basePlatformEnemy, BackgroundElements::Backdrop &backdrop) {
    // Update camera target to player's world position so the camera follows the player
    camera.target = { SCREEN_WIDTH / 2, player.y - player.movementVelocity.y };

    Vector2 topLeftWorld = GetScreenToWorld2D({ 0, 0 }, camera);


    PlatformUtils::SummonPlatform(ice,player, camera, FrictionLevel::Slippery,GetRandomValue(0,10) > 7 ? basePlatformEnemy : Enemys::Enemy{});

    if (IsKeyDown(KEY_A)) player.movementVelocity.x = -5;
    if (IsKeyDown(KEY_D)) player.movementVelocity.x = 5;

    if (IsKeyPressed(KEY_SPACE) && player.CanJump()) player.movementVelocity.y -= player.jumpHeight;

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
        DrawText(std::to_string((int)(player.y / 100)).c_str(),topLeftWorld.x + 10,topLeftWorld.y,100,GREEN);
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

    Texture2D background = LoadTexture("Resources/backDrop.png");
    Texture2D ice = LoadTexture("Resources/Ice-Block.png");
    Texture2D enemyTex = LoadTexture("Resources/Enemy_01.png");

    //This exists more a pre-contructed enemy to be used on platforms - Move into Enemy namespace later
    Enemys::Enemy basePlatformEnemy(
        1,
         enemyTex,
        {SCREEN_WIDTH/2, 0},
        10,
        enemyTex.height / 2);

    BackgroundElements::Backdrop backdrop(background, GetScreenToWorld2D({0,(float)background.height / 2},camera));

    while(!WindowShouldClose()){
        switch (gameState) {
            case Playing:
                HandlePlayingLoop(camera, frameCounter, ice, basePlatformEnemy, backdrop);
                if (IsKeyReleased(KEY_P)) gameState = Paused;
                break;
            case Paused:
                if (IsKeyReleased(KEY_L)) gameState = Playing;

                Vector2 textSpawnLoc = GetScreenToWorld2D({SCREEN_WIDTH/2,SCREEN_HEIGHT/2}, camera);
                int textWidth = MeasureText("Wow what a cool piece of pausing you did there well done champ",15);

                BeginDrawing();
                BeginMode2D(camera);
                    DrawText("Wow what a cool piece of pausing you did there well done champ",textSpawnLoc.x - (textWidth / 2),textSpawnLoc.y,15,BLACK);
                EndMode2D();
                EndDrawing();
                break;
        }

    }
    
    UnloadTexture(background);
    CloseWindow();
    return 0;
}
