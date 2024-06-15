#pragma once

#include "Entity.h"

class Pawn : public Entity {
public:
    Pawn(const std::string& f);
    ~Pawn();

    Struct::Entity getStructure() override;
};
