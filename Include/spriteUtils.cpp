#include "raylib.h"
#include "spriteUtils.hpp"
#include "raymath.h"
#include  <iostream>

namespace SpriteUtils {

    Texture2D background;
    Texture2D ice;
    Texture2D enemyTex01;
    Texture2D enemyTex02;
    Texture2D mainMenu;

    void InitalizeTextures() {
        background = LoadTexture("Resources/backDrop.png");
        ice = LoadTexture("Resources/Ice-Block.png");
        enemyTex01 = LoadTexture("Resources/Enemy_01.png");
        enemyTex02 = LoadTexture("Resources/Player.png");
        mainMenu = LoadTexture("Resources/MainMenu.png");
    }

    Sprite CreateSprite(Texture2D _texture, Rectangle _rect)
    {
        _texture.width = _rect.width;
        _texture.height = _rect.height;

        return {_texture, {_rect.x, _rect.y}};
    }

    SpriteSheet CreateSpriteSheet(Texture2D sheet, int frameCount, int timeBetweenFrames)
    {
        SpriteSheet spriteSheet;
        spriteSheet.texture = sheet;
        spriteSheet.currentFrame = 0;

        for (int i = 1; i <= frameCount; i++)
        {
            float frameWidth = sheet.width / frameCount;
            Rectangle frame = {frameWidth * i ,0,frameWidth, (float)sheet.height};
            spriteSheet.frames.push_back(frame);
        }

        return spriteSheet;
    }

    AsepriteTagEX CreateAsepriteTagEX(Aseprite aseprite, const char *name, bool requireAnimationComplete) {
        return {LoadAsepriteTag(aseprite, name), requireAnimationComplete};
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

    void DrawAsepriteTagOffset(AsepriteTag tag, Vector2 position,  float rotation, float scale, Color tint) {
        Vector2 offset{
            static_cast<float>(tag.aseprite.ase->w / 2) * scale,
            static_cast<float>(tag.aseprite.ase->h) * scale - 10
        };
        position -= offset;

        DrawAsepriteTagEx(tag, position,0,scale, tint);
    }

}

