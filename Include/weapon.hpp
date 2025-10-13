#ifndef WEAPON_HPP
#define WEAPON_HPP
#include "spriteUtils.hpp"

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

    void CreateBullet();

    void UpdateBullets();
}
#endif