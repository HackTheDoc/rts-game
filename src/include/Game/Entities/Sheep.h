#pragma once

#include "Entity.h"

class Sheep : public Entity {
public:
    Sheep();
    ~Sheep();

    void update() override;

    Struct::Entity getStructure() override;

private:
    Entity* hunter;

    void updateWithHunter();
    void updateWithoutHunter();
};
