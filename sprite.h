#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include <queue>


struct SpriteSheet{
    Texture2D texture;
    std::queue<Rectangle> frames;
};

SpriteSheet CreateSpriteSheet(Texture2D sheet, int frameWidth, int frameHeight, int frameCount);



#endif 
