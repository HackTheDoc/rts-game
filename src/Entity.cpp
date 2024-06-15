#include "include/Game/Entities/Entity.h"

#include "include/Game/Game.h"
#include "include/Window.h"

Entity::Entity() {
    selected = false;
    
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

void Entity::placeAt(const int x, const int y) {
    setPosition(x*Tile::SIZE, y*Tile::SIZE);
}

void Entity::setPosition(const int x, const int y) {
    position = {x,y};
}
