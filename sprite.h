#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include <vector>


struct SpriteSheet{
    Texture2D texture;
    std::vector<Rectangle> frames;

    int currentFrame;
    float frameTimer = 0;
};

SpriteSheet CreateSpriteSheet(Texture2D sheet, int frameCount, int timeBetweenFrames);

void DrawSpriteFrame(SpriteSheet &spriteSheet, Vector2 position);

#endif 
