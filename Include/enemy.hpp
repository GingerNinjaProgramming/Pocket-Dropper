#ifndef  ENEMY_HPP
#define ENEMY_HPP
#include "raylib.h"
#include "spriteUtils.hpp"
#include "player.hpp"
#include "enum.hpp"
#include <vector>

namespace Enemys {
    struct Enemy {
        SpriteUtils::Sprite body;
        int heath;
        int moveSpeed = 5;
        int spawnRadius;
        int id = -1;
        EnemyType type;

        Enemy() : body(SpriteUtils::Sprite{Texture2D{0}, {0,0}}) {
            this->heath = 0;
            this->spawnRadius = 10;
            this->id = -1;
            this->moveSpeed = 0;
            this->type = EnemyType::Platform;
        }

        Enemy(EnemyType enemyType,int heath, Texture2D sprite,Vector2 postion, int spawnRadius = 10, int collisionBoxYOffset = 0) : body(sprite,postion,collisionBoxYOffset) {
            this->spawnRadius = spawnRadius;
            this->heath = heath;
            this->type = enemyType;
        }

        bool operator==(const Enemy& other) const {
            return body == other.body &&
                   heath == other.heath &&
                   moveSpeed == other.moveSpeed &&
                   spawnRadius == other.spawnRadius &&
                   id == other.id && type == other.type;
        }

    };

    extern std::vector<Enemy*> enemys;

    void CreateEnemy(int heath, Texture2D sprite,Vector2 postion, int spawnRadius = 10, int collisionBoxYOffset = 0);
    void CreateEnemyFromStruct(Enemy enemy);

    void UpdateEnemies(PlayerUtils::Player &player);

    void HandleAllEnemyCollision(PlayerUtils::Player &player);

    void DrawEnemiesOnScreen();
}

#endif
