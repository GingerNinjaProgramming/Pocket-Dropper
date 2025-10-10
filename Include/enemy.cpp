#include "enemy.hpp"
#include "constants.hpp"
#include "player.hpp"

namespace Enemys {
    void UpdateEnemy(Enemy &enemy) {
        enemy.body.position.x += enemy.moveDirX;

        if (enemy.body.position.x < 0 + enemy.spawnRadius || enemy.body.position.x > SCREEN_WIDTH - enemy.spawnRadius) {
            enemy.moveDirX *= -1;
        }
    }

    void HandlePlayerCollision(Enemy &enemy, PlayerUtils::Player &player) {
        if (CheckCollisionCircleRec({player.x,player.y}, player.spawnRadius, enemy.body.AsRect()) && player.y < enemy.body.AsRect().y){
            player.movementVelocity.y -= player.jumpHeight - 5;
            player.movementVelocity.x *= 1.5;
        }
    }


    void DrawEnemy(Enemy &enemy) {
        // DrawTexture(enemy.texture, (int)enemy.position.x,(int)enemy.position.y, WHITE);
        DrawTextureEx(enemy.body.texture, {(int)enemy.body.position.x,(int)enemy.body.position.y - 20},0,0.9, WHITE);
        DrawRectangleLinesEx(enemy.body.AsRect(), 2, WHITE);
        //DrawCircle((int)(enemy.position.x), (int)(enemy.position.y), (int)enemy.spawnRadius, BLUE);
    }
}