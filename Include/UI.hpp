#ifndef UI_HPP
#define UI_HPP
#include "raylib.h"
#include "constants.hpp"

namespace BackgroundElements {
    struct Backdrop {
        Texture2D texture;
        Vector2 position;

        Backdrop(Texture2D texture, Vector2 position) {
            this->texture = texture;
            this->position = position;
        }
    };

    Rectangle GetCenterRectangleGUI(int width, int height);
}

#endif