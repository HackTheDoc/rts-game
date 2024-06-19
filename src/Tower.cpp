#include "include/Game/Buildings/Tower.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Tower::Tower(const std::string& faction, const Vector2D& pos) {
    this->faction = faction;
    type = TOWER;
    
    position = pos;
    
    width = 2;
    height = 4;
    
    freeSpace = 0;

    texture = Window::manager->getTexture(faction+" tower");
}

Tower::~Tower() {}

Struct::Building Tower::getStructure() {
    return {Struct::Tower{faction, position}};
}
