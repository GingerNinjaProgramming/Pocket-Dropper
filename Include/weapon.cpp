//
// Created by 2500411 on 13/10/2025.
//

#include "weapon.hpp"
#include "player.hpp"

namespace WeaponUtils {
    std::vector<Bullet*> bullets;

    void CreateBullet(Texture2D tex,PlayerUtils::Player shooter, int bulletSpeed) {
        Bullet *newBullet = new Bullet(
            tex,
            {shooter.x, shooter.y - shooter.spawnRadius},
            bulletSpeed
        );
        newBullet->id = bullets.size();
        bullets.push_back(newBullet);
    }

    void UpdateBullet(Bullet &bullet) {
        bullet.body.position.y += bullet.speed;

        if (bullet.body.position.y < 0 - bullet.body.texture.height) {
            for (size_t i = 0; i < bullets.size(); i++) {
                if (bullets[i]->id == bullet.id) {
                    bullets.erase(bullets.begin() + i);
                    delete &bullet;
                    break;
                }
            }
        }
    }

    void UpdateBullets() {
        if (bullets.empty()) return;

        for (const auto& bullet : bullets) {
            UpdateBullet(*bullet);
        }
    }

}