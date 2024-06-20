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
        BUILDING,
        GOING_TO_MINE,
        MINING
    };
    State state;

    enum Type {
        UNKNOWN,
        PAWN,
        WARRIOR,
        ARCHER
    };
    Type type;

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

    /// @brief apply pathfinding algo & store path in pathToTravel
    /// @param pos in grid
    void goTo(const Vector2D& pos);
    void stopMovement();
    bool reachedDestination();

    virtual Struct::Entity getStructure();

    bool died();

protected:
    int speed;

    Sprite* sprite;

    std::vector<Vector2D> pathToTravel;

    void travel();
    void updateFree();
};
