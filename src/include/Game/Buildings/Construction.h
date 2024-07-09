#pragma once

#include "Building.h"

#include <vector>

class Entity;
class Pawn;

class Construction : public Building {
public:
    Construction(const Building::Type type, const std::string& faction, const Vector2D& pos, const int lvl = 0);
    ~Construction() override;

    void update() override;
    void draw() override;
    void destroy() override;

    void addBuilder(Entity* b);
    void realeaseBuilder();

    Struct::Object getStructure() override;

private:
    Building::Type constructionType;
    LevelBar* level;

    Pawn* builder;
};
