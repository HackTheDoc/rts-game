#include "include/Game/Buildings/Castle.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Castle::Castle(const std::string& faction, const Vector2D& pos) {
    this->faction = faction;
    type = CASTLE;
    
    position = pos;
    
    width = 5;
    height = 4;

    freeSpace = 4;

    texture = Window::manager->getTexture(faction+" castle");
}

Castle::~Castle() {}

Struct::Building Castle::getStructure() {
    return {Struct::Castle{faction, position}};
}
