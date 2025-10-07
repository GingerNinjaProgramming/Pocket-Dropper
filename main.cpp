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
#include "constants.hpp"

PlayerUtils::Player player;
int score;

void ClampRef(float &value, float min, float max) {
    value = Clamp(value, min, max);
}

int main(){
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Drop");
    SetTargetFPS(TARGET_FPS);

    Camera2D camera = { 0 };
    player = PlayerUtils::CreatePlayer(200,200,10);
    Rectangle ground = {0,SCREEN_HEIGHT - 50,SCREEN_WIDTH,50};

    camera.offset = { SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int frameCounter = 0;

    Texture2D background = LoadTexture("C:/Users/conne/CLionProjects/Pocket-Dropper/Resources/backDrop.png");
    Texture2D projectile = LoadTexture("Projectile_Nail.png");

    while(!WindowShouldClose()){
        // Update camera target to player's world position so the camera follows the player
        camera.target = { SCREEN_WIDTH / 2, player.y };

        frameCounter++;

        //Ammend score every second 
        if(frameCounter % TARGET_FPS == 0){
           score += 1;
        } 

        if(IsKeyDown(KEY_A)) player.movementVelocity.x -= 5;
        if(IsKeyDown(KEY_D)) player.movementVelocity.x += 5;
        if (IsKeyPressed(KEY_SPACE) && player.CanJump()) player.movementVelocity.y -= 5;

        if (!CheckCollisionCircleRec({player.x,player.y},player.spawnRadius,ground)){
            ClampRef(player.movementVelocity.y += GRAVITY,0,player.maxFallingSpeed);
            player.isTouchingGround = false;
        }else{
            player.isTouchingGround = true;
        }

        PlayerUtils::UpdatePlayer(player);

        // Start drawing and apply camera transform
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
                DrawTexture(background,0,0,{ 150, 150, 150, 255 });
                DrawRectangleRec(ground, BLACK);
                PlayerUtils::DrawPlayer(player);
                DrawText(std::to_string(score).c_str(),10,0,100,GREEN);
            EndMode2D();
        EndDrawing();
    }
    
    UnloadTexture(background);
    CloseWindow();
    return 0;
}