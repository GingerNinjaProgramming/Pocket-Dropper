#ifndef WEAPON_HPP
#define WEAPON_HPP
#include "spriteUtils.hpp"
#include "player.hpp"

namespace WeaponUtils {
    struct Bullet {
        SpriteUtils::Sprite body;
        int speed;
        int id = -1;

        Bullet(Texture2D tex, Vector2 position, int _speed) : body(tex, position) {
            this->speed = _speed;
        }
    };

    extern std::vector<Bullet*> bullets;

    void CreateBullet(Texture2D tex,PlayerUtils::Player shooter, int bulletSpeed = 10);

    void UpdateBullets();
}
#endif