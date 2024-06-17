#include "include/Game/Buildings/Castle.h"

#include "include/Game/Map/Tile.h"
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

Struct::Building Castle::getStructure() {
    return {Struct::Castle{faction, position}};
}
