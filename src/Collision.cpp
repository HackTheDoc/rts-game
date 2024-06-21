#include "include/Game/Components/Collision.h"

#include "include/Game/Game.h"

#include <algorithm>

bool Collision::AABB(const SDL_Rect& r1, const SDL_Rect& r2) {
    return  r1.x + r1.w >= r2.x &&
            r2.x + r2.w >= r1.x &&
            r1.y + r1.h >= r2.y &&
            r2.y + r2.h >= r1.y;
}

bool Collision::AABB(Collider* col, const SDL_Rect& r) {
    return AABB(col->rect, r);
}

bool Collision::AABB(Entity* e1, Entity* e2) {
    return AABB(e1->collider->rect, e2->collider->rect);
}

bool Collision::AABB_STRICT(const SDL_Rect& r1, const SDL_Rect& r2) {
    return  r1.x + r1.w > r2.x &&
            r2.x + r2.w > r1.x &&
            r1.y + r1.h > r2.y &&
            r2.y + r2.h > r1.y;
}

bool Collision::AABB_STRICT(Collider* col, const SDL_Rect& r) {
    return AABB_STRICT(col->rect, r);
}

bool Collision::AABB_STRICT(Entity* e1, Entity* e2) {
    return AABB_STRICT(e1->collider->rect, e2->collider->rect);
}

bool Collision::IsValidBuildingPosition(const Vector2D& pos, const Vector2D& size) {
    const Vector2D& m_size = Game::GetMapSize();

    for (int y = 0; y < size.y; y++)
        for (int x = 0; x < size.x; x++) {
            Vector2D p = pos + Vector2D{x,y};
            if (y < size.y / 2)
                p.y = std::clamp(p.y, 0, m_size.y);
            if (Game::generator.detectCollision(p))
                return false;
        }
    
    return !BuildingWithEntity(pos, size);
}

bool Collision::BuildingWithEntity(const Vector2D& pos, const Vector2D& size) {
    std::vector<Entity*> entities = Game::GetEntities();

    const int tileSize = Map::TileSize();
    const SDL_Rect r = {
        pos.x  * tileSize - Game::camera.pos.x,
        pos.y  * tileSize - Game::camera.pos.y,
        size.x  * tileSize,
        size.y  * tileSize
    };

    for (auto e : entities)
        if (e->type != Entity::Type::TREE && AABB_STRICT(e->collider, r))
            return true;
    
    return false;
}
