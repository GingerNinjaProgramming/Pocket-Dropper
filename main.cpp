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
#include "projectile.h"

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

void DrawBackDropScroll(Texture2D background, Vector2 &backdropLoc){
    int playerFallingScrollOffset = Clamp(abs(player.movementVelocity.y) / 4,1,30);

    backdropLoc.y -= playerFallingScrollOffset;

    // Reset when the texture has fully scrolled out
    if (backdropLoc.y <= -SCREEN_HEIGHT){
        backdropLoc.y = 0;
    }

    // Draw two textures: one at current position, one just below it, and one above
    DrawTexture(background, backdropLoc.x, backdropLoc.y, { 150, 150, 150, 255 });
    DrawTexture(background, backdropLoc.x, backdropLoc.y + SCREEN_HEIGHT, { 150, 150, 150, 255 });
}


int main(){
    Vector2 backdropLoc = {0,0};

    queue<Obstacle> obstacles;
    vector<Obstacle*> obstaclesInScene;

    vector<Projectile*> projectiles;

    obstacles.push(CreateObstacle(Random, 100, 100));

    Obstacle* currentObstacle = GetObstacleFromQueue(obstacles, obstaclesInScene);

    int frameCounter = 0;

    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Drop");
    SetTargetFPS(TARGET_FPS);
    

    player = CreatePlayer(LoadTexture("Player.png"),200,200,10);
    Texture2D background = LoadTexture("backDrop.png");
    //Texture2D projectile = LoadTexture("Projectile_Nail.png");


    while(!WindowShouldClose()){
        frameCounter++;

        //Ammend score every second 
        if(frameCounter % TARGET_FPS == 0){
           score += 1;
        } 


        //if(IsKeyDown(KEY_W)) player.y -= 5;
        if(IsKeyDown(KEY_A)) player.x -= 5;
       // if(IsKeyDown(KEY_S)) player.y += 5;
        if(IsKeyDown(KEY_D)) player.x += 5;

        if(IsKeyPressed(KEY_SPACE)){
            Projectile* newProjectile = new Projectile(CreateProjectile(player.x,player.y,10,LoadTexture("Pin.png")));
            projectiles.push_back(newProjectile);
        }

        player.timeFallingDown = Clamp(player.timeFallingDown + GetFrameTime(),1,player.timeFallingDown + GetFrameTime());

        player.movementVelocity.y += GRAVITY * player.timeFallingDown;
        ClampRef(player.movementVelocity.y,0,player.maxFallingSpeed);

        //cout << player.movementVelocity.y << endl;

        player.y = SCREEN_HEIGHT / 2;

        if(CheckCollisionCircleRec(GetPlayerLocAsVector2(player),player.spawnRadius,currentObstacle->body)){
            cout << "HIT" << endl;
        }
        
        if(HasObstacleLeftScreen(*currentObstacle) && currentObstacle->hasEnteredScreen){
            obstaclesInScene.erase(obstaclesInScene.begin() + currentObstacle->id);

            if(obstacles.empty()){
                obstacles.push(CreateObstacle(Random, 100, 100));
            }

            currentObstacle = GetObstacleFromQueue(obstacles, obstaclesInScene);
        }

        UpdateAllObstacles(obstaclesInScene,player);

        for(auto& projectile : projectiles){
            projectile->y += (projectile->speed);
            ClampRef(projectile->y,player.y,SCREEN_HEIGHT);

            for(const auto& obstacle : obstaclesInScene){
                if(CheckCollisionCircleRec(GetPlayerLocAsVector2(player),player.spawnRadius,obstacle->body)){
                    cout << "Projectile Hit" << endl;
                }
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawBackDropScroll(background,backdropLoc);

            DrawPlayer(player);
            for(const auto& projectile : projectiles){
                DrawTexture(projectile->sprite, (int)projectile->x, (int)projectile->y, WHITE);
            }
            DrawRectangleRec(currentObstacle->body, RED);
            DrawText(to_string(score).c_str(),10,0,100,GREEN);
        EndDrawing();
    }
    
    UnloadTexture(background);
    CloseWindow();
    return 0;
}