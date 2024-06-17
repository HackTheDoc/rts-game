#include "include/Game/Buildings/Castle.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Castle::Castle(const std::string& faction, const Vector2D& pos) {
    this->faction = faction;

    position = pos;

    width = 5 * Tile::SIZE;
    height = 4 * Tile::SIZE;

    texture = Window::manager->getTexture(faction+" castle");
}

Castle::~Castle() {}

std::vector<Vector2D> Castle::tilesBlocked() {
    std::vector<Vector2D> p;

    const Vector2D pos = position / Tile::SIZE;

    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 5; x++)
            p.push_back(pos + Vector2D{x,y});

    return p;
}

Struct::Building Castle::getStructure() {
    return {Struct::Castle{faction, position}};
}
