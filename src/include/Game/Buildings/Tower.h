#pragma once

#include "Building.h"

class Tower : public Building {
public:
    Tower(const std::string& faction, const Vector2D& pos);
    ~Tower() override;

    Struct::Object getStructure() override;
};
