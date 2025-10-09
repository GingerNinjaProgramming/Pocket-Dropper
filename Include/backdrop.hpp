
#ifndef BACKDROP_HPP
#define BACKDROP_HPP
#include "raylib.h"

namespace BackgroundElements {
    struct Backdrop {
        Texture2D texture;
        Vector2 position;

        Backdrop(Texture2D texture, Vector2 position) {
            this->texture = texture;
            this->position = position;
        }
    };
}

#endif