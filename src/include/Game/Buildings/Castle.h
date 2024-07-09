#pragma once

#include "Building.h"

class Castle : public Building {
public:
    int foodStorage;
    int goldStorage;
    int woodStorage;

    Vector2D entry;

    Castle(const std::string& faction, const Vector2D& pos);
    ~Castle() override;

    void update() override;

    Struct::Object getStructure() override;
};
