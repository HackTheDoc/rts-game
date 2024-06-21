#pragma once

#include "Building.h"

class Castle : public Building {
public:
    int foodStorage;
    int goldStorage;
    int woodStorage;

    Castle(const std::string& faction, const Vector2D& pos);
    ~Castle();

    void update() override;

    Struct::Building getStructure() override;
};
