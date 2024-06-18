#pragma once

#include "Building.h"
#include "../../UI/UILevelBar.h"

class Construction : public Building {
public:
    Construction(const Building::Type type, const std::string& faction, const Vector2D& pos, const int lvl = 0);
    ~Construction();

    void update() override;
    void draw() override;
    void destroy() override;

    Struct::Building getStructure() override;

private:
    Building::Type type;
    UILevelBar* level;
};
