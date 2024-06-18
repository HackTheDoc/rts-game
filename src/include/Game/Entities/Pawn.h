#pragma once

#include "Entity.h"

class Pawn : public Entity {
public:
    Pawn(const std::string& f);
    ~Pawn();

    void update() override;

    Struct::Entity getStructure() override;
};
