#include "include/Game/Components/Collision.h"

#include "include/Game/Components/Collider.h"

bool Collision::AABB(const SDL_Rect& r1, const SDL_Rect& r2) {
    return  r1.x + r1.w >= r2.x &&
            r2.x + r2.w >= r1.x &&
            r1.y + r1.h >= r2.y &&
            r2.y + r2.h >= r1.y;
}

bool Collision::AABB(Collider* col, const SDL_Rect& r) {
    return AABB(col->rect, r);
}
