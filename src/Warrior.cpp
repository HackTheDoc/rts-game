#include "include/Game/Entities/Warrior.h"

#include "include/struct.h"

Warrior::Warrior(const std::string& f) {
    faction = f;

    state = FREE;
    
    selected = false;
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init(faction+" warrior", 4);
}

Warrior::~Warrior() {}

Struct::Entity Warrior::getStructure() {
    const Struct::Warrior w{faction, position, selected};
    return {w};
}
