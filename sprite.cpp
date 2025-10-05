#include "sprite.h"
#include "constants.h"

SpriteSheet CreateSpriteSheet(Texture2D sheet, int frameCount, int timeBetweenFrames)
{
    SpriteSheet spriteSheet;
    spriteSheet.texture = sheet;
    spriteSheet.currentFrame = 0;

    for (int i = 1; i <= frameCount; i++)
    {
        float frameWidth = sheet.width / frameCount;
        Rectangle frame = {frameWidth * i ,0,frameWidth, sheet.height};
        spriteSheet.frames.push_back(frame);
    }

    return spriteSheet;
}

void DrawSpriteFrame(SpriteSheet &spriteSheet, Vector2 position){

    Rectangle currentRec = spriteSheet.frames[spriteSheet.currentFrame];
    float scale = 8.0f; // 800%
    DrawTexturePro(
        spriteSheet.texture,
        currentRec,
        {position.x, position.y, currentRec.width * scale, currentRec.height * scale},
        {0, 0},
        0,
        WHITE
    );

    if(spriteSheet.frameTimer > 2.0f){
        spriteSheet.currentFrame++;
        spriteSheet.frameTimer = 0;
    };

    if(spriteSheet.currentFrame >= spriteSheet.frames.size()){
        spriteSheet.currentFrame = 0;
    }

}

