#include "include/Game/Entities/Warrior.h"

#include "include/struct.h"

Warrior::Warrior(const std::string& f) {
    faction = f;
    
    selected = false;
    
    position.Zero();
    
    width = 384;
    height = 384;

    collider = new EntityCollider(this);

    sprite = new Sprite(this);
    sprite->init(faction+" warrior", 4);

    type = WARRIOR;

    setState(FREE);
}

Warrior::~Warrior() {}

Struct::Object Warrior::getStructure() {
    Struct::Warrior w{faction, position, selected, Vector2D{0,0}};
    
    if (!reachedDestination())
        w.dest = pathToTravel[0];

    return Struct::Object{w};
}
