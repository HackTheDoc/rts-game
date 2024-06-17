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
    rect.x = position.x * Game::camera.zoom - Game::camera.pos.x;
    rect.y = position.y * Game::camera.zoom - Game::camera.pos.y;

    rect.w = width * Game::camera.zoom;
    rect.h = height * Game::camera.zoom;
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

std::vector<Vector2D> Building::tilesBlocked() {
    return {};
}

Struct::Building Building::getStructure() {
    return {Struct::Castle{faction, position}};
}
