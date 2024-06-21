#include "include/Game/Entities/Sheep.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Sheep::Sheep() {
    faction = "wilderness";

    type = SHEEP;
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init("sheep", 3);

    speed = 2;

    hunter = nullptr;

    setState(FREE);
}

Sheep::~Sheep() {}

void Sheep::drawSprite() {
    sprite->draw();
}

void Sheep::updateSprite() {
    sprite->update();
}

void Sheep::update() {
    Entity::update();

    if (hunter) updateWithHunter();
    else updateWithoutHunter();
}

Struct::Entity Sheep::getStructure() {
    return {Struct::Sheep{position}};
}

void Sheep::updateWithHunter() {
    if (hunter->reachedDestination()) {
        if (hunter->position == position)
            hunter->carrySheep(this);
        else hunter = nullptr;
    }
    else if (hunter->destination() * Tile::SIZE != position) {
        hunter = nullptr;
    }
}

void Sheep::updateWithoutHunter() {
    sprite->play("idle");
    
    if (Builder::active) return;

    if (Game::CountSelectedEntities() != 1) return;

    if (Game::GetSelectedEntity()->type != Entity::Type::PAWN) return;
    
    if (!Game::cursor.inRect(&collider->rect)) return;
    
    if (!Window::event.mouseClickRight()) return;

    hunter = Game::GetSelectedEntity();
    
    hunter->goTo(position/Tile::SIZE);
}
