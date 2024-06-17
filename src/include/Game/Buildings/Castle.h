#pragma once

#include "Building.h"

class Castle : public Building {
public:
    Castle(const std::string& faction, const Vector2D& pos);
    ~Castle();

    std::vector<Vector2D> tilesBlocked() override;

    Struct::Building getStructure() override;
};
