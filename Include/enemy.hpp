#ifndef  ENEMY_HPP
#define ENEMY_HPP
#include "raylib.h"
#include "spriteUtils.hpp"
#include "player.hpp"
#include <vector>

namespace Enemys {
    struct Enemy {
        SpriteUtils::Sprite body;
        int heath;
        int moveDirX = 5;
        int spawnRadius;
        int id = -1;

        Enemy() : body(SpriteUtils::Sprite{Texture2D{0}, {0,0}}) {
            this->heath = 0;
            this->spawnRadius = 10;
            this->id = -1;
            this->moveDirX = 0;
        }

        Enemy(int heath, Texture2D sprite,Vector2 postion, int spawnRadius = 10, int collisionBoxYOffset = 0) : body(sprite,postion,collisionBoxYOffset) {
            this->spawnRadius = spawnRadius;
            this->heath = heath;
        }

        bool operator==(const Enemy& other) const {
            return body == other.body &&
                   heath == other.heath &&
                   moveDirX == other.moveDirX &&
                   spawnRadius == other.spawnRadius &&
                   id == other.id;
        }

    };

    extern std::vector<Enemy*> enemys;

    void CreateEnemy(int heath, Texture2D sprite,Vector2 postion, int spawnRadius = 10, int collisionBoxYOffset = 0);
    void CreateEnemyFromStruct(Enemy enemy);

    void UpdateEnemies();

    void HandleAllEnemyCollision(PlayerUtils::Player &player);

    void DrawEnemiesOnScreen();
}

#endif
