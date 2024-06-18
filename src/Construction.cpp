#include "include/Game/Buildings/Construction.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Construction::Construction(const Building::Type type, const std::string& faction, const Vector2D& pos, const int lvl) {
    this->type = type;
    this->faction = faction;

    position = pos;

    builder = nullptr;

    int constructionTime, barWidth;
    switch (type) {
    case Building::Type::HOUSE:
        texture = Window::manager->getTexture("construction house");
        width = 2;
        height = 3;
        constructionTime = 60*5;
        barWidth = 128;
        break;
    case Building::Type::TOWER:
        texture = Window::manager->getTexture("construction tower");
        width = 2;
        height = 4;
        constructionTime = 60*10;
        barWidth = 192;
        break;
    case Building::Type::CASTLE:
        texture = Window::manager->getTexture("construction castle");
        width = 5;
        height = 4;
        constructionTime = 60*20;
        barWidth = 256;
        break;
    case Building::Type::CONSTRUCTION: // unreachable
    default:
        break;
    }

    level = new UILevelBar(constructionTime, lvl, barWidth);

    for (int y = 0; y < height-1; y++)
        for (int x = 0; x < width; x++)
            Game::AddCollider(position + Vector2D{x,y});
}

Construction::~Construction() {}

void Construction::update() {
    Building::update();

    builder->update();

    if (builder->reachedDestination()) {
        builder->setFlip(SDL_FLIP_NONE);
        level->active = true;
    }
    else level->active = false;

    level->place(
        rect.x + (rect.w - level->width()) / 2,
        rect.y + rect.h
    );
    level->update();

    if (level->isFinished())
        Game::FinishConstruction(type, position, "white");
}

void Construction::draw() {
    Building::draw();

    builder->draw();

    level->draw();
}

void Construction::destroy() {
    realeaseBuilder();

    Building::destroy();

    level->destroy();
}

void Construction::addBuilder(Entity* b) {
    if (builder) return;

    Vector2D pos = (position + Vector2D{0, height-1});
    
    b->selected = false;
    b->goTo(pos);
    b->setState(Entity::State::BUILDING);
    builder = b;

    Game::RemoveEntity(b);
}

void Construction::realeaseBuilder() {
    if (!builder) return;

    const Vector2D pos = (position + Vector2D{0, height-1}) * Tile::SIZE;

    builder->setState(Entity::State::FREE);
    builder->placeAt(pos);
    builder->setFlip(SDL_FLIP_NONE);

    Game::AddEntity(builder);

    builder = nullptr;
}

Struct::Building Construction::getStructure() {
    return {Struct::Construction{faction, position, level->getCurrentLevel(), type, builder->getStructure()}};
}
