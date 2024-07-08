#include "include/Game/Entities/Entity.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

int Entity::MAX_HP = 3;

Entity::Entity() {
    selected = false;

    faction = "wilderness";
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init("purple pawn", 6);

    speed = 4;

    sheep = nullptr;

    hp = MAX_HP;
    healthBar = new LevelBar(MAX_HP, hp, 160);
    healthBar->active = false;

    type = UNKNOWN;
    setState(FREE);
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

    if (selected) {
        healthBar->setCurrentLevel(hp);
        healthBar->update();
        healthBar->place(
            collider->rect.x + (collider->rect.w - healthBar->width()) / 2,
            collider->rect.y + collider->rect.h + 4*(Window::fullscreen+1)
        );
    }
}

void Entity::draw() {
    sprite->draw();
    collider->draw();

    if (selected)
        healthBar->draw();
}

void Entity::kill() {
    sprite->destroy();
    delete sprite;
    sprite = nullptr;

    delete collider;
    collider = nullptr;

    healthBar->destroy();
    healthBar = nullptr;
}

void Entity::placeAt(const Vector2D& pos) {
    position = pos;
}

void Entity::setState(const State s) {
    state = s;

    switch (s) {
    case State::FREE:
        building = false;
        if (sheep)
            playAnimation("holding idle");
        else
            playAnimation("idle");
        break;
    case State::BUILDING:
        selected = false;
        releaseSheep();
        break;
    case State::MINING:
        Game::ui->hide("construction menu");
        break;
    case State::CHOPING_WOOD:
        Game::ui->hide("construction menu");
        selected = false;
        playAnimation("attack");
        setFlip(SDL_FLIP_NONE);
        break;
    default:
        break;
    }
}

void Entity::setFlip(const SDL_RendererFlip flip) {
    sprite->spriteFlip = flip;
}

void Entity::playAnimation(const std::string& a) {
    sprite->play(a);
}

void Entity::goTo(const Vector2D& pos, const bool force) {
    if (!Game::IsAllowedPosition(pos)) return;
    if (!reachedDestination() && pos == destination()) return;

    const Vector2D start = position / Tile::SIZE;

    pathToTravel = Game::FindPath(start, pos);
    pathToTravel.pop_back();

    if (pathToTravel.empty()) pathToTravel.push_back(pos);

    if (!selected) return;
    
    std::cout << "from" << start << " to " << pos << std::endl;
    for(auto& coordinate : pathToTravel)
        std::cout << "  - " << coordinate << std::endl;
}

void Entity::stopMovement() {
    pathToTravel.clear();
    setState(FREE);
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

void Entity::carrySheep(Sheep* s) {
    if (sheep) return;

    sheep = s;
    sheep->playAnimation("idle");
    Game::RemoveEntity(sheep);

    Castle* c = Game::playerFaction.getNearestCastle(position);
    if (c == nullptr) return;
    goTo(c->entry);
}

void Entity::consumeSheep() {
    if (!sheep) return;

    sheep->kill();
    sheep = nullptr;
}

void Entity::releaseSheep() {
    if (!sheep) return;

    sheep->removeHunter();
    sheep->placeAt(position);
    sheep->stopMovement();
    
    Game::AddEntity(sheep);
    sheep = nullptr;
}

bool Entity::died() {
    return false;
}

void Entity::updateFree() {
    if (faction != Game::playerFaction.name) return;

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
        else if (sheep)
            playAnimation("holding idle");
        else
            playAnimation("idle");
        return;
    }

    Vector2D dest = pathToTravel.back();
    dest = dest * Tile::SIZE;

    if (isAtPos(dest)) {
        pathToTravel.pop_back();
        return;
    }

        // rendering movement
    if (sheep)
        sprite->play("holding walk");
    else 
        sprite->play("walk");

    if (dest.x < position.x)
        setFlip(SDL_FLIP_HORIZONTAL);
    else setFlip(SDL_FLIP_NONE);
    
        // applying movement

    double d = std::sqrt(double(dist(position, dest)));
    double f = speed / d;

    position.x += (int)((dest.x - position.x) * f);
    position.y += (int)((dest.y - position.y) * f);
}

bool Entity::isAtPos(const Vector2D& pos) {
    return abs(pos.x - position.x) < speed && abs(pos.y - position.y) < speed;
}
