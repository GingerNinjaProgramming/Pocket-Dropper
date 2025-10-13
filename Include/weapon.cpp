//
// Created by 2500411 on 13/10/2025.
//

#include "weapon.hpp"
#include "player.hpp"

namespace WeaponUtils {
    std::vector<Bullet*> bullets;

    void CreateBullet(Texture2D tex,PlayerUtils::Player shooter) {
        Bullet *newBullet(tex,shooter.AsVector2(), 5);
        newBullet->id = bullets.size();
        bullets.push_back(newBullet);
    }
}