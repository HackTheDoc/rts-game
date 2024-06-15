#pragma once

#include "Entity.h"

/// @brief TODO: FIX THE SPRITE
class Archer : public Entity {
public:
    Archer(const std::string& f);
    ~Archer();

    Struct::Entity getStructure() override;
};
