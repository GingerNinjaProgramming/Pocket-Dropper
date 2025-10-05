#include "sprite.h"

SpriteSheet CreateSpriteSheet(Texture2D sheet, int frameWidth, int frameHeight, int frameCount)
{
    SpriteSheet spriteSheet;

    int lastFrameX = 0;

    for (int i = 1; i <= frameCount; i++)
    {
        Rectangle frameRec = { i * frameWidth, 0, frameWidth, frameHeight };
        spriteSheet.frames.push(frameRec); // Use push_back for std::vector
    }

    return spriteSheet;
}