#pragma once

#include <SDL2/SDL.h>

#include "Vector2D.h"

class Collider;
class Entity;

class Collision {
public:
    static bool AABB(const SDL_Rect& r1, const SDL_Rect& r2);
    static bool AABB(Collider* col, const SDL_Rect& r);
    static bool AABB(Entity* e1, Entity* e2);
    
    static bool AABB_STRICT(const SDL_Rect& r1, const SDL_Rect& r2);
    static bool AABB_STRICT(Collider* col, const SDL_Rect& r);
    static bool AABB_STRICT(Entity* e1, Entity* e2);
    
    static bool IsValidBuildingPosition(const Vector2D& pos, const Vector2D& size);
    static bool BuildingWithEntity(const Vector2D& pos, const Vector2D& size);
};
