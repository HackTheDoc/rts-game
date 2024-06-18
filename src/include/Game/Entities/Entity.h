#pragma once

#include <vector>

#include "../Components/Vector2D.h"
#include "../Components/Sprite.h"
#include "../Components/EntityCollider.h"

namespace Struct {
    struct Entity;
}

class Entity {
public:
    enum State {
        FREE,
        BUILDING
    };
    State state;

    enum Type : char {
        UNKNOWN,
        PAWN,
        WARRIOR,
        ARCHER
    };

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

    void placeAt(const Vector2D& pos);

    void setState(const State s);
    void setFlip(const SDL_RendererFlip flip);

    virtual Struct::Entity getStructure();

protected:
    int speed;

    Sprite* sprite;

    std::vector<Vector2D> pathToTravel;

    void updateFree();
};
