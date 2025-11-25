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
#include "memory.hpp"
#include "weapon.hpp"
#include "raylib-aseprite.h"
#include "raygui.h"
#include "sound.hpp"

PlayerUtils::Player player;
bool hasGameStarted = false;

struct GameOptions {
    bool isSoundOn = true;
    bool loadData = false;
};

void ClampRef(float &value, float min, float max) {
    value = Clamp(value, min, max);
}


void HandlePlayingLoop(Camera2D &camera, Texture2D ice, Enemys::Enemy enemys[], BackgroundElements::Backdrop &backdrop, Music &bgm) {
    // Update camera target to player's world position so the camera follows the player
    camera.target = { SCREEN_WIDTH / 2, player.y - player.movementVelocity.y };

    Vector2 topLeftWorld = GetScreenToWorld2D({ 0, 0 }, camera);

    PlatformUtils::SummonPlatform(ice,player, camera, FrictionLevel::Slippery,GetRandomValue(0,10) > 7 ? enemys[GetRandomValue(0,1)] : Enemys::Enemy{});

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) player.movementVelocity.x = -5;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) player.movementVelocity.x = 5;

    if (IsKeyPressed(KEY_SPACE)) {
        if (player.CanJump()) PlayerUtils::DoJump(player);
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
        BackgroundElements::DrawBackdrop(backdrop, player, camera);
        PlatformUtils::DrawPlatformsOnScreen(player,camera);
        PlayerUtils::DrawPlayer(player);
        Enemys::DrawEnemiesOnScreen();
        DrawText(std::to_string(player.score).c_str(),topLeftWorld.x + 10,topLeftWorld.y,100,GREEN);
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
    SetMusicVolume(bgm,0.1f);
    if (options.isSoundOn) PlayMusicStream(bgm);

    Sounds::LoadSound("Resources/sfx/playerJump.wav", SoundType::PlayerJump, 0.5);
    Sounds::LoadSound("Resources/sfx/playerJump02.wav", SoundType::PlayerJump, 0.5);
    Sounds::LoadSound("Resources/sfx/playerJump03.wav", SoundType::PlayerJump, 0.5);
    Sounds::LoadSound("Resources/sfx/groundHit.wav", SoundType::PlayerLand);
    Sounds::LoadSound("Resources/sfx/groundHit02.wav", SoundType::PlayerLand);
    Sounds::LoadSound("Resources/sfx/enemyHit.wav", SoundType::EnemyHit);
    Sounds::LoadSound("Resources/sfx/explosion.wav", SoundType::EnemyDeath);
    Sounds::LoadSound("Resources/sfx/gunFire.wav", SoundType::PlayerShoot);

    GameState gameState = MainMenu;
    GameState beforeOptionsState = MainMenu;
    Camera2D camera = { 0 };
    player = PlayerUtils::CreatePlayer(LoadAseprite("Resources/asprite/LittleDude.aseprite"),200,200,10);

    camera.offset = { SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    //Loads all needed textures into SpriteUtils namespace
    SpriteUtils::InitalizeTextures();

    //Load GUI Theme
    GuiLoadStyle("Resources/style_cyber.rgs");

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

    bool isOpen = true;
    while(isOpen){
        switch (gameState) {
            case MainMenu: {
                beforeOptionsState = gameState;

                Rectangle playButtonRect = BackgroundElements::GetCenterRectangleGUI(200,100);
                Rectangle optionsButtonRect = BackgroundElements::GetCenterRectangleGUI(200,100);
                optionsButtonRect.y += 150;
                Rectangle quitButtonRect = BackgroundElements::GetCenterRectangleGUI(200,100);
                quitButtonRect.y += 300;

                BeginDrawing();
                DrawTexture(SpriteUtils::mainMenu,0,0, WHITE);
                GuiButton(playButtonRect,"Play Game") ? gameState = GameState::Playing : 0;
                GuiButton(optionsButtonRect, "Options") ? gameState = GameState::Options : 0;
                GuiButton(quitButtonRect, "Quit Game") ? gameState = GameState::Quit : 0;
                ClearBackground(RAYWHITE);
                EndDrawing();
                break;
            }
            case Quit:
                CloseWindow();
                break;
            case Playing:
                beforeOptionsState = gameState;
                if (IsKeyDown(KEY_P) || IsKeyDown(KEY_ESCAPE)) {
                    gameState = Paused;
                    PauseMusicStream(bgm);
                    break;
                }


                if (!hasGameStarted) {
                    json data = JSON::loadData();

                    player.score = data["Score"];
                    hasGameStarted = true;
                }

                HandlePlayingLoop(camera, SpriteUtils::ice, enemys, backdrop,bgm);
                break;
            case Paused: {
                //Temp Menu Rect
                int width = 350;
                int height = 300;
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

                GuiButton({windowRect.x + ((windowRect.width / 4)),windowRect.y  + ((windowRect.height / 6) * 1), windowRect.width / 2, windowRect.height / 6},"Resume")
                ? gameState = GameState::Playing : 0;

                GuiButton({windowRect.x + ((windowRect.width / 4)),(windowRect.y + 25) + ((windowRect.height / 6) * 2), windowRect.width / 2, windowRect.height / 6},"Options")
                ? gameState = GameState::Options : 0;

                GuiButton({windowRect.x + ((windowRect.width / 4)),(windowRect.y + 50) + ((windowRect.height / 6) * 3), windowRect.width / 2, windowRect.height / 6},"Quit Game")
                ? gameState = GameState::Quit : 0;

                EndDrawing();
                break;
            }
            case Options:
                Rectangle soundOnCheckRect = {SCREEN_WIDTH / 2 - 100, 100, 100, 50};
                Rectangle loadSaveDataCheckRect = {SCREEN_WIDTH / 2 - 100, 160, 100, 50};
                Rectangle backButtonRect = {SCREEN_WIDTH / 2 - 100, 260, 100, 100};

                BeginDrawing();
                    GuiLabel({SCREEN_WIDTH / 2 - 100,50,SCREEN_WIDTH,50},"Options");
                    GuiCheckBox(soundOnCheckRect,"Sound On", &options.isSoundOn);

                    if (!hasGameStarted) GuiCheckBox(loadSaveDataCheckRect,"Load Save Data", &options.loadData);

                    GuiButton(backButtonRect,"Back") ? gameState = beforeOptionsState : 0;
                    ClearBackground(RED);
                EndDrawing();
                break;
        }
        if (WindowShouldClose() && !IsKeyDown(KEY_ESCAPE)) {
            isOpen = false;
            break;
        }
    }

    JSON::AmendScoreJson(player.score);
    UnloadTexture(SpriteUtils::background);
    UnloadMusicStream(bgm);
    CloseWindow();
    return 0;
}
