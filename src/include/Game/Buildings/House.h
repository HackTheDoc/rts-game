#pragma once

#include "Building.h"

class House : public Building {
public:
    House(const std::string& faction, const Vector2D& pos);
    ~House();

    void update() override;
    
    Struct::Building getStructure() override;
};
