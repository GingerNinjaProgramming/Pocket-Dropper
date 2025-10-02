#include <iostream>
#include <algorithm>
#include <math.h>
#include <raylib.h>
#include <vector>
#include <queue>
#include <type_traits>
#include <concepts>
#include "player.h"
#include "enums.h"
#include "constants.h"
#include "obstacle.h"

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

void DrawBackDropScroll(Texture2D background, Vector2 &backdropLoc){
    int playerFallingScrollOffset = Clamp(player.movementVelocity.y,-10,10);

    backdropLoc.y -= 10 + player.movementVelocity.y;

    // Reset when the texture has fully scrolled out
    if (backdropLoc.y <= -SCREEN_HEIGHT) {
        backdropLoc.y = 0;
    }

    // Draw two textures: one at current position, one just below it
    DrawTexture(background, backdropLoc.x, backdropLoc.y, { 150, 150, 150, 255 });
    DrawTexture(background, backdropLoc.x, backdropLoc.y + SCREEN_HEIGHT, { 150, 150, 150, 255 });
}


int main(){
    player = CreatePlayer(200,200,10);

    Vector2 backdropLoc = {0,0};

    queue<Obstacle> obstacles;
    vector<Obstacle*> obstaclesInScene;

    Obstacle rec = CreateObstacle(Left, 100, 100);
    Obstacle rec2 = CreateObstacle(Middle, 100, 100);
    Obstacle rec3 = CreateObstacle(Right, 100, 100);

    obstacles.push(rec);
    obstacles.push(rec2);
    obstacles.push(rec3);

    Obstacle* currentObstacle = GetObstacleFromQueue(obstacles, obstaclesInScene);

    int frameCounter = 0;

    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Drop");
    SetTargetFPS(TARGET_FPS);
    
    Texture2D background = LoadTexture("backDrop.png");
    

    while(!WindowShouldClose()){
        frameCounter++;

        //Ammend score every second 
        if(frameCounter == TARGET_FPS){
           frameCounter = 0; 

           score += 1;
        } 

        //if(IsKeyDown(KEY_W)) player.y -= 5;
        if(IsKeyDown(KEY_A)) player.x -= 5;
       // if(IsKeyDown(KEY_S)) player.y += 5;
        if(IsKeyDown(KEY_D)) player.x += 5;

        player.timeFallingDown += GetFrameTime();

        cout << player.timeFallingDown <<  endl;

        if(IsKeyDown(KEY_S)) player.movementVelocity.y = GRAVITY * player.timeFallingDown;
        else if (player.movementVelocity.y > 1) player.movementVelocity.y *= -1;

        player.y += Clamp(player.movementVelocity.y,-3,3);

        if(PlayerPosition::Top > player.y) player.y = PlayerPosition::Top;
        else if(PlayerPosition::Bottom < player.y) player.y = PlayerPosition::Bottom;

        if(CheckCollisionCircleRec(GetPlayerLocAsVector2(player),player.spawnRadius,currentObstacle->body)){
            cout << "HIT" << endl;
        }
        
        if(HasObstacleLeftScreen(*currentObstacle) && currentObstacle->hasEnteredScreen){
            obstaclesInScene.erase(obstaclesInScene.begin() + currentObstacle->id);

            if(obstacles.empty()){
                obstacles.push(rec);
            }

            currentObstacle = GetObstacleFromQueue(obstacles, obstaclesInScene);
        }

        UpdateAllObstacles(obstaclesInScene);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawBackDropScroll(background,backdropLoc);

            DrawPlayer(player);
            DrawRectangleRec(currentObstacle->body,RED);
            DrawText(to_string(score).c_str(),10,0,100,GREEN);
        EndDrawing();
    }
    
    UnloadTexture(background);
    CloseWindow();
    return 0;
}