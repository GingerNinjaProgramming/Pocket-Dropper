#include <iostream>
#include <algorithm>
#include <math.h>
#include <raylib.h>
#include <vector>
#include <queue>
#include <type_traits>
#include <concepts>
#include "player.hpp"
#include "enums.hpp"
#include "constants.hpp"
#include "obstacle.hpp"

using namespace std;

Player player;
int score;

float Clamp(float value,float min, float max){
    if(value < min){
        value = min;
        return value;
    }

    if(value > max){
        value = max;
        return value;
    }

    return value;
}

void ClampRef(float &value,float min, float max){
    if(value < min){
        value = min;
    }

    if(value > max){
        value = max;
    }
}

int main(){
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Drop");
    SetTargetFPS(TARGET_FPS);

    Camera2D camera = { 0 };
    player = CreatePlayer(200,200,10);

    // Proper camera setup: offset places the target on screen (center by default),
    // rotation 0, zoom 1. If zoom is left at 0 (camera = {0}), nothing will be visible.
    camera.offset = { SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int frameCounter = 0;
    
    //Texture2D projectile = LoadTexture("Projectile_Nail.png");


    while(!WindowShouldClose()){
    // Update camera target to player's world position so the camera follows the player
    camera.target = { SCREEN_WIDTH / 2, player.y };
        frameCounter++;

        //Ammend score every second 
        if(frameCounter % TARGET_FPS == 0){
           score += 1;
        } 

        if(IsKeyDown(KEY_A)) player.x -= 5;

        if(IsKeyDown(KEY_D)) player.x += 5;

        player.y += GRAVITY;

        if(CheckCollisionCircleRec(GetPlayerLocAsVector2(player),player.spawnRadius,currentObstacle->body)){
            cout << "HIT" << endl;
        }
        

        // Start drawing and apply camera transform
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);

                DrawTexture(background,backdropLoc.x + player.y,player.y, WHITE);
                DrawPlayer(player);
                DrawText(to_string(score).c_str(),10,0,100,GREEN);

            EndMode2D();

        EndDrawing();
    }
    
    UnloadTexture(background);
    CloseWindow();
    return 0;
}