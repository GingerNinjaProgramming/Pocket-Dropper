# ifndef  ENEMY_HPP
#define ENEMY_HPP
#include "raylib.h"

namespace Enemys {
    struct Enemy {
        int heath;
        Vector2 position;
        int moveDirX = 5;
        int spawnRadius;

        Enemy(int heath,Vector2 spawnLoc, int spawnRadius = 10) {
            this ->position = spawnLoc;
            this->spawnRadius = spawnRadius;
            this->heath = heath;
        }
    };

    void UpdateEnemy(Enemy &enemy);

    void DrawEnemy(const Enemy &enemy);
}

#endif
