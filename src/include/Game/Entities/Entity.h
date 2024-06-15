#pragma once

#include "../Components/Vector2D.h"
#include "../Components/Sprite.h"
#include "../Components/EntityCollider.h"

class Entity {
public:
    bool selected;

    Vector2D position;
    int width, height;

    EntityCollider* collider;

    Entity();
    ~Entity();

    void update();
    void draw();
    void kill();

    void placeAt(const int x, const int y);
    void setPosition(const int x, const int y);

private:
    Sprite* sprite;
};
