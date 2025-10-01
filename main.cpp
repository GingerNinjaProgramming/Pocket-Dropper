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
    //Gust up variables

    player = CreatePlayer(200,200,10);

    Rectangle rec = CreateObstacle(Left, 100, 10);
    Rectangle rec2 = CreateObstacle(Middle, 100, 10);
    Rectangle rec3 = CreateObstacle(Right, 100, 10);
    
    bool isHoldingDown = false;

    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Drop");
    SetTargetFPS(60);


    while(!WindowShouldClose()){
        player.movementVelocity.y += gravity * GetFrameTime() : player.movementVelocity.y;
        if(player.movementVelocity.y > 2 && !isHoldingDown){
            player.movementVelocity.y = 2;
        }else if(player.movementVelocity.y > 5 && isHoldingDown){
            player.movementVelocity.y = 5;
        }
        
        isHoldingDown = false;

        if(IsKeyDown(KEY_W)) {
            player.y -= 5; 
        }
        if(IsKeyDown(KEY_A)) player.x -= 5;
        if(IsKeyDown(KEY_S)) {
            player.y += 5;
            isHoldingDown = true;
        }
        if(IsKeyDown(KEY_D)) player.x += 5;

        //cout << y << endl;
        cout << player.movementVelocity.y << endl;

        player.y += player.movementVelocity.y;

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