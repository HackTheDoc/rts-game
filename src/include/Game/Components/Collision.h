#pragma once

#include <SDL2/SDL.h>

class Collider;

class Collision {
public:
    static bool AABB(const SDL_Rect& r1, const SDL_Rect& r2);
    static bool AABB(Collider* col, const SDL_Rect& r);
};
