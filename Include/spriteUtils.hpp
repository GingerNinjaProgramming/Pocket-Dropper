#ifndef SPRITEUTILS_HPP
#define SPRITEUTILS_HPP

#include <raylib.h>
#include <vector>

namespace SpriteUtils {

    extern Texture2D background;
    extern Texture2D ice;
    extern Texture2D enemyTex;

    struct SpriteSheet{
        Texture2D texture;
        std::vector<Rectangle> frames;

        int currentFrame;
        float frameTimer = 0;
    };

    struct Sprite {
        Texture2D texture;
        Vector2 position;
        int collisionBoxYOffset = 0;

        Sprite(Texture2D _texture, Vector2 _position, int _collisionBoxYOffset = 0) {
            this->collisionBoxYOffset = _collisionBoxYOffset;
            this->texture = _texture;
            this->position = _position;
        }

        Rectangle AsRect(Vector2 sizeOffset = {0,0}) const {
            return {position.x, position.y - collisionBoxYOffset, (float)texture.width + sizeOffset.x, (float)texture.height + sizeOffset.y};
        }

        bool operator==(const Sprite &other) const {
            return texture.id == other.texture.id &&
                   position.x == other.position.x &&
                   position.y == other.position.y &&
                   collisionBoxYOffset == other.collisionBoxYOffset;
        }
    };

    void InitalizeTextures();

    Sprite CreateSprite(Texture2D _texture, Rectangle _rect);

    SpriteSheet CreateSpriteSheet(Texture2D sheet, int frameCount, int timeBetweenFrames);

    void DrawSpriteFrame(SpriteSheet &spriteSheet, Vector2 position);
}

#endif 
