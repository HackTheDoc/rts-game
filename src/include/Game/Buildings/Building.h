#pragma once

#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include "../Components/Vector2D.h"

namespace Struct {
    struct Building;
}

class Building {
public:
    enum Type {
        CASTLE,
        HOUSE
    };

    Vector2D position;
    int width, height;

    Building();
    ~Building();

    void update();
    void draw();
    void destroy();

    virtual std::vector<Vector2D> tilesBlocked();

    virtual Struct::Building getStructure();

protected:
    std::string faction;

    SDL_Texture* texture;
    SDL_Rect rect;
};
