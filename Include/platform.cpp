#include "platform.hpp"
#include "player.hpp"
#include <raylib.h>

namespace PlatformUtils {
    bool CheckPlayerCollisions(Platform _this,PlayerUtils::Player &player) {
        if (CheckCollisionCircleRec({player.x,player.y}, player.spawnRadius, _this.body)) {
            return true;
        }

        return false;
    }
}