#include "platform.hpp"
#include "player.hpp"
#include "constants.hpp"
#include <raylib.h>
#include <vector>

namespace PlatformUtils {

    std::vector<Platform> platforms;

    Platform SummonPlatform(const PlayerUtils::Player &player, const Camera2D &camera) {

        int screenBottom = GetScreenToWorld2D({0,SCREEN_HEIGHT},camera).y - 20;

        retry_platform_spawn:

        int spawnY = GetRandomValue(screenBottom, screenBottom + SCREEN_HEIGHT);
        int spawnWidth = GetRandomValue(20,SCREEN_WIDTH / 2);
        int spawnX = GetRandomValue(spawnWidth, GetScreenWidth() - spawnWidth);
        int spawnHeight = 50;

        Rectangle potentialPlatform = {(float)spawnX, (float)spawnY, (float)spawnWidth, (float)spawnHeight};

        for (auto &platform : platforms) {
            if (platform.body.y > screenBottom && platform.body.y < screenBottom + SCREEN_HEIGHT) {
                return {Rectangle{},-1};
            }

            if (CheckCollisionRecs(platform.body,potentialPlatform)) {
                goto retry_platform_spawn;
            }
        }

        Platform newPlatform = {potentialPlatform, (int)platforms.size() + 1};

        platforms.push_back(newPlatform);
        return newPlatform;
    }



    bool CheckPlayerCollisions(PlayerUtils::Player &player) {
        for (const auto &platform : platforms) {
            if (CheckCollisionCircleRec({player.x,player.y}, player.spawnRadius, platform.body)) {
                return true;
            }
        }

        return false;
    }

    void DrawPlatformsOnScreen(const PlayerUtils::Player &player, const Camera2D &camera) {
        int screenTopY = GetScreenToWorld2D({0,0},camera).y;
        int screenBottomY = GetScreenToWorld2D({0,SCREEN_HEIGHT},camera).y;

        for (auto &platform : platforms) {
            if (platform.body.y < screenBottomY && platform.body.y > screenTopY) {
                DrawRectangleRec(platform.body, DARKGRAY);
            }
        }
    }

}