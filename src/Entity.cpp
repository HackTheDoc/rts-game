#include "include/Game/Entities/Entity.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Entity::Entity() {
    state = FREE;

    selected = false;

    faction = "wilderness";
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init("purple pawn", 6);

    speed = 4;

    type = UNKNOWN;
}

Entity::~Entity() {}

void Entity::update() {
    sprite->update();
    collider->update();

    if (state == CHOPING_WOOD || state == MINING)
        return;
    
    if (state == State::FREE)
        updateFree();
    
    travel();
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

void Entity::setState(const State s) {
    state = s;

    switch (s) {
    case State::FREE:
        sprite->play("idle");
        break;
    case State::BUILDING:
        break;
    case State::MINING:
        Game::ui->hide("construction menu");
        break;
    case State::CHOPING_WOOD:
        Game::ui->hide("construction menu");
        sprite->play("attack");
        selected = false;
        sprite->spriteFlip = SDL_FLIP_NONE;
        break;
    default:
        break;
    }
}

void Entity::setFlip(const SDL_RendererFlip flip) {
    sprite->spriteFlip = flip;
}

void Entity::goTo(const Vector2D& pos) {
    pathToTravel = Game::FindPath(position / Tile::SIZE, pos);
}

void Entity::stopMovement() {
    pathToTravel.clear();
    sprite->play("idle");
}

bool Entity::reachedDestination() {
    return pathToTravel.empty();
}

Vector2D Entity::destination() {
    return pathToTravel.front();
}

Struct::Entity Entity::getStructure() {
    const Struct::Pawn p{faction, position, selected};
    return {p};
}

bool Entity::died() {
    return false;
}

void Entity::updateFree() {
    // check if new path

    const Vector2D p = Game::cursor.getPosOnMap();
    if (selected && Window::event.mouseClickRight() && Game::IsAllowedPosition(p)) {
        goTo(p);
    }
}

void Entity::travel() {
    if (reachedDestination()) {
        if (state == BUILDING)
            sprite->play("build");
        else
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
