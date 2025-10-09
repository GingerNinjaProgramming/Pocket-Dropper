#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <raylib.h>
#include <vector>
#include "player.hpp"

namespace PlatformUtils {
    struct Platform {
        Rectangle body;
        int index;
    };

    extern std::vector<Platform> platforms;

    Platform SummonPlatform(const PlayerUtils::Player &player, const Camera2D &camera);

    bool CheckPlayerCollisions(PlayerUtils::Player &player);

    void DrawPlatformsOnScreen(const PlayerUtils::Player &player, const Camera2D &camera);
}

#endif
