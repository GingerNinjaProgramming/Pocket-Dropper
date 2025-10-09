#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <raylib.h>

struct Projectile{
    Texture2D sprite;

    float x,y;
    float speed = 5;
    bool isActive = true;
};

Projectile CreateProjectile(float spawnX,float spawnY, float speed, Texture2D sprite);

#endif 