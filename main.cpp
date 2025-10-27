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
#include "UI.hpp"
#include "enum.hpp"
#include "weapon.hpp"
#include "raylib-aseprite.h"
#include "raygui.h"
#include "sound.hpp"

PlayerUtils::Player player;
int score;

struct GameOptions {
    bool isSoundOn = true;
};

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

void HandlePlayingLoop(Camera2D &camera, int frameCounter, Texture2D ice, Enemys::Enemy enemys[], BackgroundElements::Backdrop &backdrop, Music &bgm) {
    // Update camera target to player's world position so the camera follows the player
    camera.target = { SCREEN_WIDTH / 2, player.y - player.movementVelocity.y };

    Vector2 topLeftWorld = GetScreenToWorld2D({ 0, 0 }, camera);

    PlatformUtils::SummonPlatform(ice,player, camera, FrictionLevel::Slippery,GetRandomValue(0,10) > 7 ? enemys[0] : Enemys::Enemy{});

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

    if (IsKeyDown(KEY_M)) {
        enemys[1].body.position = GetScreenToWorld2D({SCREEN_WIDTH/2,0}, camera);
        Enemys::CreateEnemyFromStruct(enemys[1]);
    }

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

    UpdateMusicStream(bgm);
    Enemys::HandleAllEnemyCollision(player);
    PlayerUtils::UpdatePlayer(player);
    WeaponUtils::UpdateBullets();
    Enemys::UpdateEnemies(player);
    PlatformUtils::HandlePlatformDespawn(camera);


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
    GameOptions options;

    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Drop");
    SetTargetFPS(TARGET_FPS);


    //Load background music
    InitAudioDevice();
    Music bgm = LoadMusicStream("Resources/music/Pixel Peeker Polka - faster.mp3");
    SetMusicVolume(bgm,0.25f);
    if (options.isSoundOn) PlayMusicStream(bgm);

    Sounds::LoadSound("Resources/sfx/groundHit.wav", SoundType::PlayerLand);
    Sounds::LoadSound("Resources/sfx/groundHit02.wav", SoundType::PlayerLand);
    Sounds::LoadSound("Resources/sfx/enemyHit.wav", SoundType::EnemyHit);
    Sounds::LoadSound("Resources/sfx/explosion.wav", SoundType::EnemyDeath);
    Sounds::LoadSound("Resources/sfx/gunFire.wav", SoundType::PlayerShoot);

    GameState gameState = Playing;
    Camera2D camera = { 0 };
    player = PlayerUtils::CreatePlayer(LoadAseprite("Resources/asprite/LittleDude.aseprite"),200,200,10);

    camera.offset = { SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int frameCounter = 0;

    //Loads all needed textures into SpriteUtils namespace
    SpriteUtils::InitalizeTextures();

    //This exists more a pre-contructed enemy to be used on platforms - Move into Enemy namespace later
    Enemys::Enemy basePlatformEnemy(
        EnemyType::Platform,
        1,
         SpriteUtils::enemyTex01,
        {SCREEN_WIDTH/2, 0},
        10,
        SpriteUtils::enemyTex01.height / 2
    );

    Enemys::Enemy trackerEnemy(
        EnemyType::Chaser,
        1,
        SpriteUtils::enemyTex02,
        {SCREEN_WIDTH/2, 0},
        10,
        SpriteUtils::enemyTex02.height / 2
    );
    trackerEnemy.moveSpeed = 15;

    Enemys::Enemy enemys[] =  {basePlatformEnemy,trackerEnemy};

    BackgroundElements::Backdrop backdrop(SpriteUtils::background, GetScreenToWorld2D({0,(float)SpriteUtils::background.height / 2},camera));

    while(!WindowShouldClose()){
        switch (gameState) {
            case Playing:
                if (IsKeyDown(KEY_P)) {
                    gameState = Paused;
                    PauseMusicStream(bgm);
                    break;
                }
                HandlePlayingLoop(camera, frameCounter, SpriteUtils::ice, enemys, backdrop,bgm);
                break;
            case Paused:
                //Temp Menu Rect
                int width = 350;
                int height = 150;
                Rectangle windowRect = BackgroundElements::GetCenterRectangleGUI(width, height);

                BeginDrawing();
                ClearBackground(RAYWHITE);
                BeginMode2D(camera);
                    DrawBackdrop(backdrop, player, camera);
                    PlatformUtils::DrawPlatformsOnScreen(player, camera);
                    PlayerUtils::DrawPlayer(player);
                    Enemys::DrawEnemiesOnScreen();
                EndMode2D();

                GuiWindowBox(windowRect,"Game Paused");
                GuiButton({windowRect.x + ((windowRect.width / 4)),windowRect.y + (windowRect.height / 2), windowRect.width / 2, windowRect.height / 4},"Options")
                ? gameState = GameState::Options : 0;

                EndDrawing();
                break;
            /*case Options:
                BeginDrawing();
                ClearBackground(RAYWHITE);
                EndDrawing();
                break;*/
        }

    }
    
    UnloadTexture(SpriteUtils::background);
    UnloadMusicStream(bgm);
    CloseWindow();
    return 0;
}
