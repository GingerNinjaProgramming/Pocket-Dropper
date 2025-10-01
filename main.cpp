#include <iostream>
#include <algorithm>
#include <math.h>
#include <raylib.h>
#include <vector>
#include <queue>
#include "player.h"
#include "enums.h"
#include "constants.h"
#include "obstacle.h"

using namespace std;

Player player;
int score;

int main(){
    player = CreatePlayer(200,200,10);

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

        if(CheckCollisionCircleRec(GetPlayerLocAsVector2(player),player.spawnRadius,currentObstacle->body)){
            cout << "HIT" << endl;
        }
        
        if(HasObstacleLeftScreen(*currentObstacle) && currentObstacle->hasEnteredScreen){
            obstaclesInScene.erase(obstaclesInScene.begin() + currentObstacle->id);

            if(obstacles.empty()){
                obstacles.push(rec);
            }

            currentObstacle = GetObstacleFromQueue(obstacles, obstaclesInScene);
            cout << "Its has left the board type shih" << endl;
        }

        UpdateAllObstacles(obstaclesInScene);

        cout << obstaclesInScene.size() << endl;
 
        BeginDrawing();
            ClearBackground(BLUE);
            DrawPlayer(player);
            DrawRectangleRec(currentObstacle->body,RED);
            DrawText(to_string(score).c_str(),10,0,100,GREEN);
        EndDrawing();
    }
 
    CloseWindow();
    return 0;
}