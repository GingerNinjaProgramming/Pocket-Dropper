#include "enemy.hpp"
#include "constants.hpp"

void Enemys::UpdateEnemy(Enemy &enemy) {
    enemy.position.x += enemy.moveDirX;

    if (enemy.position.x < 0 + enemy.spawnRadius || enemy.position.x > SCREEN_WIDTH - enemy.spawnRadius) {
        enemy.moveDirX *= -1;
    }
}

void Enemys::DrawEnemy(const Enemy &enemy) {
    DrawCircle((int)(enemy.position.x), (int)(enemy.position.y), (int)enemy.spawnRadius, BLUE);
}
