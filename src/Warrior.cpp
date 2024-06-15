#include "include/Game/Entities/Warrior.h"

Warrior::Warrior(const std::string& f) {
    faction = f;
    
    selected = false;
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init(faction+" warrior", 4);
}

Warrior::~Warrior() {}
