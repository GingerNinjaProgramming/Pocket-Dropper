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

    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Drop");
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        //if(IsKeyDown(KEY_W)) player.y -= 5;
        if(IsKeyDown(KEY_A)) player.x -= 5;
       // if(IsKeyDown(KEY_S)) player.y += 5;
        if(IsKeyDown(KEY_D)) player.x += 5;

        /*for(int i = 0; i < GetRandomValue(1,3); i++){
            
        }*/
        if(CheckCollisionCircleRec(GetPlayerLocAsVector2(player),player.spawnRadius,currentObstacle->body)){
            cout << "HIT" << endl;
        }
        /*
        if(HasObstacleLeftScreen(*currentObstacle)){
            currentObstacle = GetObstacleFromQueue(obstacles, obstaclesInScene);
        }*/

        UpdateAllObstacles(obstaclesInScene);
        cout << currentObstacle->body.y << "||" << obstaclesInScene.back()->body.y << endl;
 
        BeginDrawing();
            ClearBackground(BLUE);
            DrawPlayer(player);
            DrawRectangleRec(currentObstacle->body,RED);
        EndDrawing();
    }
 
    CloseWindow();
    return 0;
}