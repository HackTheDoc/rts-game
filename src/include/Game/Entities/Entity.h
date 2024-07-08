#pragma once

#include <vector>

#include "../Components/Vector2D.h"
#include "../Components/Sprite.h"
#include "../Components/EntityCollider.h"
#include "../Components/LevelBar.h"

namespace Struct {
    struct Entity;
}

class Sheep;

class Entity {
public:
    static int MAX_HP;
    
    enum State {
        FREE,
        BUILDING,
        MINING,
        CHOPING_WOOD,
    };
    State state;

    enum Type {
        UNKNOWN,
        PAWN,
        WARRIOR,
        ARCHER,
        TREE,
        SHEEP
    };
    Type type;

    // blue, red, yellow, purple, wilderness
    std::string faction;
    
    bool selected;

    Vector2D position;
    int width, height;

    int hp;

    EntityCollider* collider;

    bool building;

    Entity();
    ~Entity();

    virtual void update();
    virtual void draw();
    virtual void kill();

    void placeAt(const Vector2D& pos);

    void setState(const State s);
    void setFlip(const SDL_RendererFlip flip);
    void playAnimation(const std::string& a);

    /// @brief apply pathfinding algo & store path in pathToTravel
    /// @param pos in grid
    void goTo(const Vector2D& pos, const bool force = false);
    void stopMovement();
    bool reachedDestination();
    bool isAtPos(const Vector2D& pos);
    Vector2D destination();

    virtual Struct::Entity getStructure();

    void carrySheep(Sheep* s);
    void releaseSheep();
    void consumeSheep();

    bool died();

protected:
    int speed;

    Sprite* sprite;

    std::vector<Vector2D> pathToTravel;

    Sheep* sheep; // sheep carrying

    LevelBar* healthBar;

    void travel();
    void updateFree();
};
