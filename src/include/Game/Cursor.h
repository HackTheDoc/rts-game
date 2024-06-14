#pragma once

#include "Components/Vector2D.h"

#include <SDL2/SDL.h>

class Cursor {
public:
    Vector2D pos;

    Cursor();
    ~Cursor();

    void update();

    void reset();

    bool inRect(const SDL_Rect* r);
};
