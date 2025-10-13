#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <raylib.h>
#include <vector>

#include "enemy.hpp"
#include "enum.hpp"
#include "player.hpp"
#include "spriteUtils.hpp"

namespace PlatformUtils {
    struct Platform {
        SpriteUtils::Sprite body;
        int index;
        FrictionLevel friction = FrictionLevel::Normal;
    };

    extern std::vector<Platform> platforms;

    Platform SummonPlatform(Texture2D texture,const PlayerUtils::Player &player, const Camera2D &camera,FrictionLevel friction = FrictionLevel::Normal, Enemys::Enemy potentialEnemy = Enemys::Enemy{});

    bool CheckPlayerCollisions(PlayerUtils::Player &player);

    void HandlePlatformDespawn(const Camera2D camera);

    void DrawPlatformsOnScreen(const PlayerUtils::Player &player, const Camera2D &camera);
}

#endif
