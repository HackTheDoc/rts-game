#include "include/Game/Entities/Archer.h"

#include "include/struct.h"

Archer::Archer(const std::string& f) {
    faction = f;
    
    selected = false;
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init(faction+" archer", 2);
}

Archer::~Archer() {}

Struct::Entity Archer::getStructure() {
    const Struct::Archer a{faction, position, selected};
    return {a};
}
