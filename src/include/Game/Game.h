#pragma once

#include "Map/Map.h"

#include "../WindowStates/WindowState.h"

class Game : public WindowState {
public:
    static SDL_Rect camera;

    Game();
    ~Game();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    Map* map;
};
