#include <iostream>
#include <algorithm>
#include <raylib.h>
#include <player.h>

using namespace std;

Player player;

int main(){
    player = CreatePlayer();

    InitWindow(400,1000,"Drop");
    SetTargetFPS(60);


    while(!WindowShouldClose()){

        if(IsKeyDown(KEY_W)) player.y -= 10;
        if(IsKeyDown(KEY_A)) player.x -= 10;
        if(IsKeyDown(KEY_S)) player.y += 10;
        if(IsKeyDown(KEY_D)) player.x += 10;

        BeginDrawing();
        DrawPlayer(player);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}