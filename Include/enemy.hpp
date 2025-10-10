# ifndef  ENEMY_HPP
#define ENEMY_HPP
#include "raylib.h"
#include "spriteUtils.hpp"
#include "player.hpp"

namespace Enemys {
    struct Enemy {
        SpriteUtils::Sprite body;
        int heath;
        int moveDirX = 5;
        int spawnRadius;

        Enemy(int heath, Texture2D sprite,Vector2 postion, int spawnRadius = 10, int collisionBoxYOffset = 0) : body(sprite,postion,collisionBoxYOffset) {
            this->spawnRadius = spawnRadius;
            this->heath = heath;
        }
    };

    void UpdateEnemy(Enemy &enemy);

    void HandlePlayerCollision(Enemy &enemy, PlayerUtils::Player &player);

    void DrawEnemy(Enemy &enemy);
}

#endif
