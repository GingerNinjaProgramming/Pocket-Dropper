#include "platform.hpp"
#include "spriteUtils.hpp"
#include "player.hpp"
#include "constants.hpp"
#include <raylib.h>
#include <vector>

namespace PlatformUtils {

    std::vector<Platform> platforms;

    Platform SummonPlatform(Texture2D texture,const PlayerUtils::Player &player, const Camera2D &camera,FrictionLevel friction) {

        SpriteUtils::Sprite sprite = {texture, {0,0}};
        int screenBottom = GetScreenToWorld2D({0,SCREEN_HEIGHT},camera).y - 20;

        retry_platform_spawn:

        int spawnY = GetRandomValue(screenBottom, screenBottom + SCREEN_HEIGHT);
        int spawnWidth = GetRandomValue(100,SCREEN_WIDTH * 0.9);
        int spawnX = GetRandomValue(spawnWidth, GetScreenWidth() - spawnWidth);
        int spawnHeight = 50;

        Rectangle potentialPlatform = {(float)spawnX, (float)spawnY, (float)spawnWidth, (float)spawnHeight};

        for (auto platform : platforms) {
            if (platform.body.position.y > screenBottom && platform.body.position.y < screenBottom + SCREEN_HEIGHT) {
                return {SpriteUtils::Sprite{Texture2D{},{0,0}},-1};
            }

            platform.body.texture.width += 20;

            if (CheckCollisionRecs(platform.body.AsRect(),potentialPlatform)) {
                goto retry_platform_spawn;
            }
        }

        Platform newPlatform = {SpriteUtils::CreateSprite(texture,potentialPlatform), (int)platforms.size() + 1,friction};

        platforms.push_back(newPlatform);
        return newPlatform;
    }


    bool CheckPlayerCollisions(PlayerUtils::Player &player) {
        for (auto &platform : platforms) {
            if (CheckCollisionCircleRec({player.x,player.y}, player.spawnRadius, platform.body.AsRect()) && player.y < platform.body.position.y) {
                player.currentFriction = platform.friction;
                return true;
            }
        }

        return false;
    }

    void DrawPlatformsOnScreen(const PlayerUtils::Player &player, const Camera2D &camera) {
        int screenTopY = GetScreenToWorld2D({0,0},camera).y;
        int screenBottomY = GetScreenToWorld2D({0,SCREEN_HEIGHT},camera).y;

        for (auto &platform : platforms) {
            if (platform.body.position.y < screenBottomY && platform.body.position.y > screenTopY) {
                DrawTexture(platform.body.texture,platform.body.position.x,platform.body.position.y, DARKGRAY);
            }
        }
    }

}