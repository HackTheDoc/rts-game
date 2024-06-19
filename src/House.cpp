#include "include/Game/Buildings/House.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

House::House(const std::string& faction, const Vector2D& pos) {
    this->faction = faction;
    type = HOUSE;
    
    position = pos;
    
    width = 2;
    height = 3;

    freeSpace = 2;

    texture = Window::manager->getTexture(faction+" house");
}

House::~House() {}

Struct::Building House::getStructure() {
    return {Struct::House{faction, position}};
}
