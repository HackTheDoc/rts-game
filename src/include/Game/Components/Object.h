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
        UNKNOWN,

        PAWN,
        WARRIOR,
        ARCHER,
        TREE,
        SHEEP,

        CONSTRUCTION,
        HOUSE,
        TOWER,
        CASTLE,
        MINE,
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
