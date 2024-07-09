#pragma once

#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include "../Components/Object.h"

class Entity;

class Building : public Object {
public:
    Building();
    ~Building() override;

    void update() override;
    void draw() override;
    void destroy() override;

    Vector2D getPosition();
    int getWidth();
    int getHeight();

    Struct::Object getStructure() override;

    int freeSpace; // freeSpace for units;
    void addUnit(Entity* u);

protected:
    std::string faction;

    SDL_Texture* texture;
    SDL_Rect rect;

    std::vector<Entity*> units;

    void drawUnitSelectorIndicator();

    void addColliders();
};
