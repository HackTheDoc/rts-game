#include "include/Game/Entities/Pawn.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Pawn::Pawn(const std::string& f) {
    faction = f;

    state = FREE;
    
    selected = false;
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init(faction+" pawn", 6);

    speed = 4;
}

Pawn::~Pawn() {}

void Pawn::update() {
    if (selected && Game::CountSelectedEntities() == 1)
        Game::ui->show("construction menu");

    Entity::update();
}

Struct::Entity Pawn::getStructure() {
    const Struct::Pawn p{faction, position, selected};
    return {p};
}