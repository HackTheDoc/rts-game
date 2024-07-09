#pragma once

#include "Entity.h"

class Sheep : public Entity {
public:
    Sheep();
    ~Sheep() override;

    void drawSprite();
    void updateSprite();
    void update() override;

    Struct::Object getStructure() override;

    void removeHunter();

private:
    Entity* hunter;

    Vector2D hunterDestination();

    void updateWithHunter();
    void updateWithoutHunter();
};
