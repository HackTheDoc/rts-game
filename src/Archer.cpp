#include "include/Game/Entities/Archer.h"

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
