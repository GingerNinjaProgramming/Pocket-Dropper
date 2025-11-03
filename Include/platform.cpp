#include "platform.hpp"
#include "spriteUtils.hpp"
#include "player.hpp"
#include "constants.hpp"
#include <raylib.h>
#include <vector>

namespace PlatformUtils {

    std::vector<Platform> platforms;

    Platform SummonPlatform(Texture2D texture,const PlayerUtils::Player &player, const Camera2D &camera,FrictionLevel friction, Enemys::Enemy potentialEnemy) {

        SpriteUtils::Sprite sprite = {texture, {0,0}};
        int screenBottom = GetScreenToWorld2D({0,SCREEN_HEIGHT},camera).y - 20;

        retry_platform_spawn:

        int spawnY = GetRandomValue(screenBottom, screenBottom + SCREEN_HEIGHT);
        int spawnWidth = GetRandomValue(80,SCREEN_WIDTH * 0.75);
        int spawnX = GetRandomValue(0, GetScreenWidth() - spawnWidth);
        int spawnHeight = 50;

        Rectangle potentialPlatform = {(float)spawnX, (float)spawnY, (float)spawnWidth, (float)spawnHeight};

        if (platforms.empty()) goto skip_platform_check; //Skip the platform check if there are no platforms

        for (auto platform : platforms) {
            //Why did I do this? - Conner 2025 O I C this is to prevent platforms spawing in the player vision - Conner 2025 like 5 minutes later
            if (platform.body.position.y > screenBottom && platform.body.position.y < screenBottom + SCREEN_HEIGHT) {
                return {SpriteUtils::Sprite{Texture2D{},{0,0}},-1};
            }

            if (CheckCollisionRecs(platform.body.AsRect({0,100}),potentialPlatform)) {
                goto retry_platform_spawn;
            }
        }

        skip_platform_check:

        Platform newPlatform = {SpriteUtils::CreateSprite(texture,potentialPlatform), (int)platforms.size() + 1,friction};

        if (potentialEnemy != Enemys::Enemy{}) {
            switch (potentialEnemy.type) {
                case EnemyType::Platform:
                    potentialEnemy.body.position = {
                        SCREEN_WIDTH / 2, newPlatform.body.AsRect().y - (potentialEnemy.body.texture.height - 10)
                    };
                case EnemyType::Chaser:
                    Rectangle platformRect = newPlatform.body.AsRect();
                    int enemyX = GetRandomValue(platformRect.x, platformRect.x + platformRect.width);
                    int enemyY = platformRect.y + platformRect.height;

                    potentialEnemy.body.position = {enemyX,enemyY};
                    break;
            }

            Enemys::CreateEnemyFromStruct(potentialEnemy);
        }

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


    void HandlePlatformDespawn(const Camera2D camera) {
        int screenTopY = GetScreenToWorld2D({0,0},camera).y;

        for (size_t i = 0; i < platforms.size(); ) {
            auto &platform = platforms[i];
            if (platform.body.position.y + platform.body.texture.height < screenTopY) {
                platforms.erase(platforms.begin() + i);
                // Do not increment i, as the next element shifts into position i
            } else {
                ++i;
            }
        }
    }


    void DrawPlatformsOnScreen(const PlayerUtils::Player &player, const Camera2D &camera) {
        int screenBottomY = GetScreenToWorld2D({0,SCREEN_HEIGHT},camera).y;

        for (auto &platform : platforms) {
            if (platform.body.position.y < screenBottomY) {
                DrawTexture(platform.body.texture,platform.body.position.x,platform.body.position.y, RAYWHITE);
                DrawRectangleLinesEx(platform.body.AsRect(), 2, GREEN);
            }
        }
    }

}