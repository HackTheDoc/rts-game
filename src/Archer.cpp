#include "include/Game/Entities/Archer.h"

#include "include/struct.h"

Archer::Archer(const std::string& f) {
    faction = f;

    state = FREE;
    
    selected = false;
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init(faction+" archer", 2);
    
    type = ARCHER;

    setState(FREE);
}

Archer::~Archer() {}

Struct::Object Archer::getStructure() {
    Struct::Archer a{faction, position, selected, Vector2D{0,0}};
    
    if (!reachedDestination())
        a.dest = pathToTravel.front();

    return Struct::Object{a};
}
