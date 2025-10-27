#include "UI.hpp"
#include "constants.hpp"

namespace BackgroundElements {
    Rectangle GetCenterRectangleGUI(int width, int height) {
        Vector2 pos = {(SCREEN_WIDTH / 2) - (width / 2),(SCREEN_HEIGHT / 2) - height};
        Rectangle windowRect = {pos.x, pos.y, width, height};

        return windowRect;
    }

}