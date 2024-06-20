#pragma once

#include "Components/Vector2D.h"

#include <SDL2/SDL.h>

class Cursor {
public:
    static bool enable;
    
    Vector2D pos;
    
    bool selecting;
    SDL_Rect selectionRect;

    Cursor();
    ~Cursor();

    void update();
    void draw();

    void reset();

    bool inRect(const SDL_Rect* r);

    Vector2D getPosOnMap();
};
