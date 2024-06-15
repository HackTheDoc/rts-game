#include "include/Game/Entities/Pawn.h"

Pawn::Pawn(const std::string& f) {
    faction = f;
    
    selected = false;
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init(faction+" pawn", 6);
}

Pawn::~Pawn() {}
