#include "include/Game/Buildings/Building.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Building::Building() {
    destroy();

    position.Zero();
    this->faction = "undefined";
    type = Type::CONSTRUCTION;
}

Building::~Building() {}

void Building::update() {
    const int tileSize = Map::TileSize();

    rect.w = width * tileSize;
    rect.h = height * tileSize;

    rect.x = position.x * tileSize - Game::camera.pos.x;
    rect.y = position.y  * tileSize - Game::camera.pos.y;

    for (size_t i = 0; i < units.size(); i++)
        if (units[i]->died()) {
            units.erase(units.begin() + i);
            freeSpace++;
        }
}

void Building::draw() {
    Manager::Draw(texture, nullptr, &rect);

    if (type != CONSTRUCTION && freeSpace > 0)
        drawUnitSelectorIndicator();
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

void Building::addUnit(Entity* u) {
    units.push_back(u);
    freeSpace--;
}

void Building::drawUnitSelectorIndicator() {
    SDL_Texture* t = Window::manager->getTexture("unit selector indicator");
    
    SDL_Rect r;
    r.w = r.h = 256 * Game::camera.zoom;
    r.x = rect.x + rect.w - 3 * r.w / 4;
    r.y = rect.y + rect.h - r.h;

    Manager::Draw(t, nullptr, &r);
}

void Building::addColliders() {
    for (int y = 0; y < height-1; y++)
        for (int x = 0; x < width; x++)
            Game::AddCollider(position + Vector2D{x,y});
}
