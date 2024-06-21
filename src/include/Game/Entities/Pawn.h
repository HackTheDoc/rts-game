#pragma once

#include "Entity.h"

class Pawn : public Entity {
public:
    Pawn(const std::string& f);
    ~Pawn();

    void draw() override;
    void update() override;

    Struct::Entity getStructure() override;
};
