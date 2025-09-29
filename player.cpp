#include "player.h"
#include "raylib.h"

Player CreatePlayer() {
    return { 100, 100 };
}

void DrawPlayer(const Player &player) {
    DrawCircle((int)player.x, (int)player.y, 20, BLUE);
}
