#include "include/Game/Entities/Pawn.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Pawn::Pawn(const std::string& f) {
    faction = f;
    
    selected = false;
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init(faction+" pawn", 6);

    speed = 4;
    
    sheep = nullptr;

    type = PAWN;

    setState(FREE);
}

Pawn::~Pawn() {}

void Pawn::draw() {
    Entity::draw();

    if (sheep && !building && state != CHOPING_WOOD)
        sheep->draw();
}

void Pawn::update() {
    if (state == FREE && selected && Game::CountSelectedEntities() == 1)
        Game::ui->show("construction menu");

    if (sheep && !building && state != CHOPING_WOOD) {
        sheep->placeAt(position - Vector2D{0, 2 * Map::TileSize() / 3});
        sheep->update();

        Castle* c = Game::playerFaction.getNearestCastle(position);
        if (c && position == c->entry*Tile::SIZE) {
            Game::playerFaction.storeFood(25, c);
            sheep->kill();
            sheep = nullptr;
        }
    }

    Entity::update();
}

Struct::Entity Pawn::getStructure() {
    Struct::Pawn p{faction, position, selected, Vector2D{0,0}, false};
    
    if (!reachedDestination() && state == FREE)
        p.dest = pathToTravel.front();

    if (sheep)
        p.carryingSheep = true;

    return {p};
}
