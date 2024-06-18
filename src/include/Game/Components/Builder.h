#pragma once

#include "../Buildings/Buildings.h"

#include <array>

class Builder {
public:    
    static bool active;
    static Building::Type type;

    bool justActived;
    Vector2D position;

    void update();
    void draw();

private:
    static std::array<Vector2D, 3> dimensions; 
    SDL_Texture* texture;
    SDL_Rect rect;
};
