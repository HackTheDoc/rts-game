#pragma once

#include "../Components/Vector2D.h"
#include "../Components/Sprite.h"
#include "../Components/EntityCollider.h"

class Entity {
public:
    // blue, red, yellow, purple
    std::string faction;
    
    bool selected;

    Vector2D position;
    int width, height;

    EntityCollider* collider;

    Entity();
    ~Entity();

    virtual void update();
    virtual void draw();
    virtual void kill();

    void placeAt(const int x, const int y);
    void setPosition(const int x, const int y);

protected:
    Sprite* sprite;
};
