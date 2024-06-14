#include "include/Game/Components/EntityCollider.h"

#include "include/Game/Entities/Entity.h"

EntityCollider::EntityCollider(Entity* o) {
    rect = { 0,0,0,0 };
    setOwner(o);
    rect.w = owner->width / 3;
    rect.h = owner->height / 3;
}

EntityCollider::~EntityCollider() {}

void EntityCollider::update() {
    position = owner->position;

    Collider::update();
}

void EntityCollider::setOwner(Entity* o) {
    owner = o;
}
