#ifndef SPRITEUTILS_HPP
#define SPRITEUTILS_HPP

#include <raylib.h>
#include <vector>
#include "raylib-aseprite.h"

namespace SpriteUtils {

    extern Texture2D background;
    extern Texture2D ice;
    extern Texture2D enemyTex01;
    extern Texture2D enemyTex02;
    extern Texture2D mainMenu;

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

    /// Extended AsepriteTag struct with frame amount for easier animation handling
    struct AsepriteTagEX {
        AsepriteTag baseTag;
        int frameAmount;
        bool requireAnimationComplete = false;

        AsepriteTagEX() {
            this->baseTag = AsepriteTag{};
            this->frameAmount = 0;
            this->requireAnimationComplete = false;
        }

        AsepriteTagEX (AsepriteTag _tag, bool requireAnimationComplete = false) {
            this->baseTag = _tag;
            ase_tag_t* tagData = _tag.tag;
            this->frameAmount = (tagData->to_frame - tagData->from_frame) + 1;
            this->requireAnimationComplete = requireAnimationComplete;

            if (requireAnimationComplete) {
                baseTag.loop = false;
            }
        }

        bool IsAnimComplete() {
            return (baseTag.currentFrame - baseTag.tag->from_frame) + 1 >= frameAmount;
        }
    };

    void InitalizeTextures();

    Sprite CreateSprite(Texture2D _texture, Rectangle _rect);

    SpriteSheet CreateSpriteSheet(Texture2D sheet, int frameCount, int timeBetweenFrames);

    AsepriteTagEX CreateAsepriteTagEX(Aseprite aseprite, const char* name, bool requireAnimationComplete = false);

    void DrawSpriteFrame(SpriteSheet &spriteSheet, Vector2 position);

    ///Modifyied version of DrawAsepriteTagEX with extra params to ensure the sprite is on center
    void DrawAsepriteTagOffset(AsepriteTag tag, Vector2 position, float rotation, float scale, Color tint);

}

#endif 
