#include "projectile.h"
#include "raylib.h"

Projectile CreateProjectile(float spawnX,float spawnY, float speed, Texture2D sprite){
    return {sprite, spawnX, spawnY, speed};
}

