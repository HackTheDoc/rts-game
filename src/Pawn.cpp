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
    if (sheep && !building && state != CHOPING_WOOD)
        sheep->drawSprite();

    Entity::draw();
}

void Pawn::update() {
    if (state == FREE && selected && Game::CountSelectedEntities() == 1)
        Game::ui->show("construction menu");

    if (sheep && !building && state != CHOPING_WOOD) {
        const int yOffset = 2 * Map::TileSize() / 3;
        sheep->placeAt(position - Vector2D{0, yOffset});
        sheep->updateSprite();

        Castle* c = Game::playerFaction.getNearestCastle(position);
        if (c && isAtPos(c->entry*Tile::SIZE)) {
            Game::playerFaction.storeFood(25, c);
            consumeSheep();
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
