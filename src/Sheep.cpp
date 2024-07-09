#include "include/Game/Entities/Sheep.h"

#include "include/Game/Components/Collision.h"
#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

constexpr int MOVEMENT_SPAN = 1;

Sheep::Sheep() {
    faction = "wilderness";

    type = SHEEP;
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init("sheep", 2);

    speed = 2;

    building = false;

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

    if (reachedDestination()) {
        Vector2D dest;

        do {
            std::uniform_int_distribution<int> dist(-MOVEMENT_SPAN, MOVEMENT_SPAN);

            Vector2D offset{dist(Window::randomEngine), dist(Window::randomEngine)};

            dest = position / Tile::SIZE + offset;
        } while (!Game::IsAllowedPosition(dest));

        goTo(dest);   
    }

    if (hunter) updateWithHunter();
    else updateWithoutHunter();
}

void Sheep::removeHunter() {
    hunter = nullptr;
}

Struct::Object Sheep::getStructure() {
    return Struct::Object{Struct::Sheep{position}};
}

Vector2D Sheep::hunterDestination() {
    Vector2D dest = position / Tile::SIZE;

    if (position.x % Tile::SIZE > Tile::SIZE / 2)
        dest.x++;
    if (position.y % Tile::SIZE > Tile::SIZE / 2)
        dest.y++;

    return dest;
}

void Sheep::updateWithHunter() {
    hunter->goTo(hunterDestination());
    if (Collision::AABB(hunter, this))
        hunter->carrySheep(this);
    else if (hunter->destination() != hunterDestination())
        removeHunter();
}

void Sheep::updateWithoutHunter() {
    sprite->play("walk");
    
    if (Builder::active) return;

    if (Game::CountSelectedEntities() != 1) return;

    if (Game::GetSelectedEntity()->type != Entity::Type::PAWN) return;
    
    if (!Game::cursor.inRect(&collider->rect)) return;
    
    if (!Window::event.mouseClickRight()) return;

    hunter = Game::GetSelectedEntity();

    hunter->releaseSheep();
    
    hunter->goTo(hunterDestination());
}
