#ifndef SPRITEUTILS_HPP
#define SPRITEUTILS_HPP

#include <raylib.h>
#include <vector>

namespace SpriteUtils {
    struct SpriteSheet{
        Texture2D texture;
        std::vector<Rectangle> frames;

        int currentFrame;
        float frameTimer = 0;
    };

    struct Sprite {
        Texture2D texture;
        Vector2 position;

        Sprite(Texture2D _texture, Vector2 _position) {
            this->texture = _texture;
            this->position = _position;
        }

        Rectangle AsRect() {
            return {position.x, position.y, (float)texture.width, (float)texture.height};
        }
    };

    Sprite CreateSprite(Texture2D _texture, Rectangle _rect);

    SpriteSheet CreateSpriteSheet(Texture2D sheet, int frameCount, int timeBetweenFrames);

    void DrawSpriteFrame(SpriteSheet &spriteSheet, Vector2 position);
}

#endif 
