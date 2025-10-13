#include "enemy.hpp"
#include "constants.hpp"
#include "player.hpp"

namespace Enemys {
    std::vector<Enemy*> enemys;

    void CreateEnemy(int heath, Texture2D sprite, Vector2 postion, int spawnRadius, int collisionBoxYOffset) {
        Enemy *newEnemy = new Enemy(heath, sprite, postion, spawnRadius, collisionBoxYOffset);
        newEnemy->id = (int)enemys.size();
        enemys.push_back(newEnemy);
    }

    void CreateEnemyFromStruct(Enemy enemy) {
        CreateEnemy(enemy.heath,enemy.body.texture,enemy.body.position,enemy.spawnRadius,enemy.body.collisionBoxYOffset);
    }


    void DestroyEnemy(Enemy* enemy) {
        for (size_t i = 0; i < enemys.size(); i++) {
            if (enemys[i]->id == enemy->id) {
                enemys.erase(enemys.begin() + i);
                delete enemy;
                break;
            }
        }
    }
    void UpdateEnemy(Enemy &enemy) {
        enemy.body.position.x += enemy.moveDirX;

        if (enemy.body.position.x < 0 + enemy.spawnRadius || enemy.body.position.x > SCREEN_WIDTH - enemy.spawnRadius) {
            enemy.moveDirX *= -1;
        }

        if (enemy.heath <= 0) {
            DestroyEnemy(&enemy);
        }
    }

    void UpdateEnemies() {
        for (auto enemy : enemys) {
            UpdateEnemy(*enemy);
        }
    }

    void HandlePlayerCollision(Enemy &enemy, PlayerUtils::Player &player) {
        if (CheckCollisionCircleRec({player.x,player.y}, player.spawnRadius, enemy.body.AsRect()) && player.y < enemy.body.AsRect().y){
            player.movementVelocity.y = -(player.jumpHeight + 5);
            player.movementVelocity.x *= 1.5;
            enemy.heath -= 1;
        }
    }

    void HandleAllEnemyCollision(PlayerUtils::Player &player) {
        for (auto enemy : enemys) {
            HandlePlayerCollision(*enemy, player);
        }
    }

    void DrawEnemy(Enemy &enemy) {
        // DrawTexture(enemy.texture, (int)enemy.position.x,(int)enemy.position.y, WHITE);
        DrawTextureEx(enemy.body.texture, {(int)enemy.body.position.x,(int)enemy.body.position.y - 20},0,0.9, WHITE);
        DrawRectangleLinesEx(enemy.body.AsRect(), 2, WHITE);
        //DrawCircle((int)(enemy.position.x), (int)(enemy.position.y), (int)enemy.spawnRadius, BLUE);
    }

    void DrawEnemiesOnScreen() {
        for (auto enemy : enemys) {
            DrawEnemy(*enemy);
        }
    }
}