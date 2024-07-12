#pragma once

#include "Vector2D.h"

#include "Sprite.h"

#include "Collider.h"
#include "EntityCollider.h"

#include "LevelBar.h"

namespace Struct {
    struct Object;
}

class Object {
public:
    enum Type {
        HOUSE,
        TOWER,
        CASTLE,
        CONSTRUCTION,
        MINE,

        PAWN,
        WARRIOR,
        ARCHER,
        TREE,
        SHEEP,
        
        UNKNOWN,
    };
    Type type;

    Vector2D position;
    int width, height;

    Object();
    virtual ~Object();
    
    virtual void update();
    virtual void draw();
    virtual void destroy();

    virtual Struct::Object getStructure();
};
