#pragma once

#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include "../Components/Vector2D.h"

namespace Struct {
    struct Building;
}

class Entity;

class Building {
public:
    enum Type {
        CONSTRUCTION,
        HOUSE,
        TOWER,
        CASTLE,
    };
    Type type;

    Vector2D position;
    int width, height;

    Building();
    ~Building();

    virtual void update();
    virtual void draw();
    virtual void destroy();

    Vector2D getPosition();
    int getWidth();
    int getHeight();

    virtual Struct::Building getStructure();

    int freeSpace; // freeSpace for units;
    void addUnit(Entity* u);

protected:
    std::string faction;

    SDL_Texture* texture;
    SDL_Rect rect;

    std::vector<Entity*> units;
};
