#include "include/Game/Buildings/Castle.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Castle::Castle(const std::string& faction, const Vector2D& pos) {
    this->faction = faction;

    position = pos;
    
    width = 5;
    height = 4;

    texture = Window::manager->getTexture(faction+" castle");

    addCollidersOnMap();
}

Castle::~Castle() {}

Struct::Building Castle::getStructure() {
    return {Struct::Castle{faction, position}};
}
