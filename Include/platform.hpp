#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <raylib.h>
#include "player.hpp"

namespace PlatformUtils {
    struct Platform {
        Rectangle body;
    };

    bool CheckPlayerCollisions(Platform _this,PlayerUtils::Player &player);
}

#endif
