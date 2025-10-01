#include <iostream>
#include <algorithm>
#include <math.h>
#include <raylib.h>
#include "player.h"

using namespace std;

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 1000;

float gravity = 50.00f;

enum ScreenSide{Left,Middle,Right};

Player player;

Rectangle CreateObstacle(ScreenSide side,int width,int height){
    int spawnX = 0;

    switch(side){
        case Left:
            spawnX = 0;
            break;
        case Middle:
            spawnX = (SCREEN_WIDTH / 2) - (width / 2);
            break;
        case Right:
            spawnX = SCREEN_WIDTH - width;
            break;
        default:
            spawnX = 0;
            break;
    }

    return {spawnX, SCREEN_HEIGHT + height, width, height}; 
}

int main(){
    int drag;

    player = CreatePlayer(200,200,10);

    Rectangle rec = CreateObstacle(Left, 100, 10);
    Rectangle rec2 = CreateObstacle(Middle, 100, 10);
    Rectangle rec3 = CreateObstacle(Right, 100, 10);
    
    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isGusting = false;

    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Drop");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        drag = 2 * player.movementVelocity.y;
        cout << player.movementVelocity.y << endl;

        if(IsKeyDown(KEY_W)){
            player.y -= 2;

            isMovingUp = true;
            isMovingDown = false;
        }else if(IsKeyDown(KEY_S)){
            isMovingDown = true;
            isMovingUp = false;
        }

        if(IsKeyDown(KEY_A)) player.x -= 2;
        if(IsKeyDown(KEY_D)) player.x += 2;

        if(isMovingDown){
            player.movementVelocity.y += 0.5;
        }

        if(isMovingUp){
            player.movementVelocity.y -= 0.5;
        }

        HandlePlayerVelocity(player);

        rec.y -= 10;
        rec2.y -= 10;
        rec3.y -= 10;

        if(CheckCollisionCircleRec(GetPlayerLocAsVector2(player),player.spawnRadius,rec)){
            cout << "HIT" << endl;
        }

        BeginDrawing();
            ClearBackground(BLUE);
            DrawPlayer(player);
            DrawRectangleRec(rec,RED);
            DrawRectangleRec(rec2,GREEN);
            DrawRectangleRec(rec3,MAGENTA);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}