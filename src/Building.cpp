#include "include/Game/Buildings/Building.h"

#include "include/Game/Game.h"
#include "include/Manager.h"
#include "include/struct.h"

Building::Building() {
    destroy();

    position.Zero();
    this->faction = "undefined";
}

Building::~Building() {}

void Building::update() {
    const int tileSize = Map::TileSize();

    rect.w = width * tileSize;
    rect.h = height * tileSize;

    rect.x = position.x * tileSize - Game::camera.pos.x;
    rect.y = position.y  * tileSize - Game::camera.pos.y;
}

void Building::draw() {
    Manager::Draw(texture, nullptr, &rect);
}

void Building::destroy() {
    faction = "undifined";
    texture = nullptr;
    rect = { 0, 0, 0, 0 };
    height = width = 0;
}

Vector2D Building::getPosition() {
    return position * Map::TileSize();
}

int Building::getWidth() {
    return width * Map::TileSize();
}

int Building::getHeight() {
    return height * Map::TileSize();
}

Struct::Building Building::getStructure() {
    return {Struct::House{faction, position}};
}
