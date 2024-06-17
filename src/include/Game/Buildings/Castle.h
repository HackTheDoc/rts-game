#pragma once

#include "Building.h"

class Castle : public Building {
public:
    Castle(const std::string& faction, const Vector2D& pos);
    ~Castle();

    Struct::Building getStructure() override;
};
