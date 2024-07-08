#include "include/Game/Entities/Tree.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

constexpr int TREE_MAX_HP = 10;
constexpr int TREE_DAMAGE = 1;
constexpr int TREE_DAMAGE_SPEED = 60;

Tree::Tree() {
    type = TREE;
    faction = "wilderness";

    hp = TREE_MAX_HP;
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init("tree", 3);

    entryPosition.Zero();

    lumberjack = nullptr;
    isLumberjackWorking = false;

    healthBar = new LevelBar(TREE_DAMAGE_SPEED, 0, 128);
}

Tree::~Tree() {}

void Tree::update() {
    sprite->update();
    collider->update();

    if (hp == 0) {
        Game::RemoveCollider(position / Map::TileSize() - Vector2D{0,1});
        Game::RemoveCollider(entryPosition / Map::TileSize());
        Game::RemoveCollider(position / Map::TileSize());
        freeLumberjack();
        sprite->play("dead");
        return;
    }
    
    if (lumberjack) updateWithLumberjack();
    else updateWithoutLumberjack();

    if (!Cursor::enable) return;
    
    if (Builder::active) return;
    
    if (Game::CountSelectedEntities() != 1) return;

    if (!Game::cursor.inRect(&collider->rect)) return;

    if (!Window::event.mouseClickLeft()) return;

    freeLumberjack();
}

void Tree::draw() {
    Entity::draw();

    if (!isLumberjackWorking) return;

    healthBar->draw();
    lumberjack->draw();
}

void Tree::kill() {
    Entity::kill();

    healthBar->destroy();

    if (lumberjack && isLumberjackWorking)
        lumberjack->kill();
}

void Tree::placeAt(const Vector2D& pos) {
    position = pos;
    entryPosition = pos - Vector2D{Tile::SIZE, 0};
    
    Vector2D p = pos / Tile::SIZE;

    Game::AddCollider(p);
    Game::AddCollider(p - Vector2D{0,1});
}

Struct::Entity Tree::getStructure() {
    return {Struct::Tree{position, hp}};
}

void Tree::freeLumberjack() {
    if (!lumberjack) return;

    if (isLumberjackWorking) {    
        lumberjack->setState(Entity::State::FREE);
    
        Game::AddEntity(lumberjack);

        isLumberjackWorking = false;
    }
    else lumberjack->stopMovement();

    lumberjack = nullptr;
}

void Tree::updateWithLumberjack() {
    if (isLumberjackWorking) {
        sprite->play("damaged");

        lumberjack->update();

        healthBar->update();
        healthBar->place(
            collider->rect.x + (collider->rect.w - healthBar->width()) / 2,
            collider->rect.y + collider->rect.h - Map::TileSize() / 4
        );
        
        if (healthBar->isFinished()) {
            Game::playerFaction.storeWood(TREE_DAMAGE, entryPosition/Tile::SIZE);
            hp -= TREE_DAMAGE;
            healthBar->setCurrentLevel(0);
        }
    }
    else if (lumberjack->isAtPos(entryPosition)) {
        lumberjack->setState(Entity::State::CHOPING_WOOD);
        Game::RemoveEntity(lumberjack);
        
        isLumberjackWorking = true;
        healthBar->setCurrentLevel(0);
        healthBar->active = true;

        Game::AddCollider(entryPosition / Tile::SIZE);
    }
    else if (lumberjack->destination() * Tile::SIZE != entryPosition) {
        lumberjack = nullptr;
    }
}

void Tree::updateWithoutLumberjack() {
    sprite->play("idle");
    
    if (Builder::active) return;

    if (Game::CountSelectedEntities() != 1) return;

    if (Game::GetSelectedEntity()->type != Entity::Type::PAWN) return;
    
    if (!Game::cursor.inRect(&collider->rect)) return;
    
    if (!Window::event.mouseClickRight()) return;

    lumberjack = Game::GetSelectedEntity();
    
    lumberjack->goTo(entryPosition/Tile::SIZE);
    
    lumberjack->releaseSheep();

    isLumberjackWorking = false;
}
