#include "UI.hpp"
#include "constants.hpp"
#include "player.hpp"
#include "raygui.h"


namespace BackgroundElements {
    Rectangle GetCenterRectangleGUI(int width, int height) {
        Vector2 pos = {(SCREEN_WIDTH / 2) - (width / 2),(SCREEN_HEIGHT / 2) - height};
        Rectangle windowRect = {pos.x, pos.y, width, height};

        return windowRect;
    }

    void DrawBackdrop(BackgroundElements::Backdrop &backdrop, const PlayerUtils::Player &player, const Camera2D &camera) {
        if (backdrop.position.y + backdrop.texture.height < GetScreenToWorld2D({0,0},camera).y) {
            backdrop.position.y += backdrop.texture.height;
        }

        DrawTexture(backdrop.texture, 0, backdrop.position.y , WHITE);
        DrawTexture(backdrop.texture, 0, backdrop.position.y  + backdrop.texture.height, WHITE);
    }

}
