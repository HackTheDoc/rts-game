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

    speed = 4;
}

Entity::~Entity() {}

void Entity::update() {
    sprite->update();
    collider->update();

    // check if new path

    if (selected && Window::event.mouseClickRight()) {
        pathToTravel = Game::FindPath(position / Tile::SIZE, Game::cursor.getPosOnMap());
    }

    // to travel
    
    if (pathToTravel.empty()) {
        sprite->play("idle");
        return;
    }

    Vector2D dest = pathToTravel.back();
    dest = dest * Tile::SIZE;
    if (dest == position) {
        pathToTravel.pop_back();
        return;
    }

        // rendering movement

    sprite->play("walk");
    if (dest.x < position.x)
        sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
    else sprite->spriteFlip = SDL_FLIP_NONE;
    
        // applying movement

    double d = std::sqrt(double(dist(position, dest)));
    double f = speed / d;

    position.x += (int)((dest.x - position.x) * f);
    position.y += (int)((dest.y - position.y) * f);
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
