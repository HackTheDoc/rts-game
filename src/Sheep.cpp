#include "include/Game/Entities/Sheep.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Sheep::Sheep() {
    faction = "wilderness";

    state = FREE;
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init("sheep", 2);

    speed = 2;

    type = SHEEP;
}

Sheep::~Sheep() {}

void Sheep::update() {
    Entity::update();
}

Struct::Entity Sheep::getStructure() {
    return {Struct::Sheep{position}};
}