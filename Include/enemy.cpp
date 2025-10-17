#include "enemy.hpp"

#include <cmath>

#include "constants.hpp"
#include "player.hpp"
#include "enum.hpp"

namespace Enemys {
    std::vector<Enemy*> enemys;

    void CreateEnemy(EnemyType type ,int heath, Texture2D sprite, Vector2 postion, int spawnRadius, int collisionBoxYOffset) {
        Enemy *newEnemy = new Enemy(type,heath, sprite, postion, spawnRadius, collisionBoxYOffset);
        newEnemy->id = (int)enemys.size();
        enemys.push_back(newEnemy);
    }

    void CreateEnemyFromStruct(Enemy enemy) {
        CreateEnemy(enemy.type,enemy.heath,enemy.body.texture,enemy.body.position,enemy.spawnRadius,enemy.body.collisionBoxYOffset);
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
    void UpdateEnemy(Enemy &enemy, PlayerUtils::Player &player) {
        switch (enemy.type) {
            case EnemyType::Platform:
                enemy.body.position.x += enemy.moveSpeed;

                if (enemy.body.position.x < 0 + enemy.spawnRadius || enemy.body.position.x > SCREEN_WIDTH - enemy.spawnRadius) {
                    enemy.moveSpeed *= -1;
                }

                if (enemy.heath <= 0) {
                    DestroyEnemy(&enemy);
                }

                break;
            case EnemyType::Chaser:
                float dx = player.x - enemy.body.position.x;
                float dy = player.y - enemy.body.position.y;
                float dist = sqrtf(dx*dx + dy*dy);

                if (dist > 0.0001f) {
                    if (dist > 18.0f) {
                        float nx = dx / dist;
                        float ny = dy / dist;
                        enemy.body.position.x += nx * 1.8f;
                        enemy.body.position.y += ny * 1.8f;
                    }
                }
                break;
        }
    }

    void UpdateEnemies(PlayerUtils::Player &player) {
        for (auto enemy : enemys) {
            UpdateEnemy(*enemy,player);
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