#pragma once

#include <vector>

#include "../Components/Object.h"

class Sheep;

class Entity : public Object {
public:
    static int MAX_HP;

    enum State {
        FREE,
        BUILDING,
        MINING,
        CHOPING_WOOD,
    };
    State state;

    // blue, red, yellow, purple, wilderness
    std::string faction;

    bool selected;

    int hp;

    EntityCollider* collider;

    bool building;

    Entity();
    ~Entity() override;

    void update() override;
    void draw() override;
    void destroy() override;

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

    Struct::Object getStructure() override;

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
