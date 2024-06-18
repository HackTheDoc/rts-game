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
        CONSTRUCTION,
        HOUSE,
        TOWER,
        CASTLE,
    };

    Vector2D position;

    Building();
    ~Building();

    virtual void update();
    virtual void draw();
    virtual void destroy();

    Vector2D getPosition();
    int getWidth();
    int getHeight();

    virtual Struct::Building getStructure();

protected:
    std::string faction;

    SDL_Texture* texture;
    SDL_Rect rect;
    
    int width, height;
};
