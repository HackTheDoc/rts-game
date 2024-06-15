#include "include/Game/Entities/Entity.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Entity::Entity() {
    selected = false;

    faction = "unknown";
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init("purple pawn", 6);
}

Entity::~Entity() {}

void Entity::update() {
    sprite->update();
    collider->update();
}

void Entity::draw() {
    sprite->draw();
    collider->draw();
}

void Entity::kill() {
    sprite->destroy();
    delete sprite;
    sprite = nullptr;

    delete collider;
    collider = nullptr;
}

void Entity::placeAt(const Vector2D& pos) {
    position = pos;
}

Struct::Entity Entity::getStructure() {
    const Struct::Pawn p{faction, position, selected};
    return {p};
}
