#pragma once

#include "Cursor.h"
#include "Camera.h"

#include "Map/Map.h"

#include "../WindowStates/WindowState.h"

class Game : public WindowState {
public:
    static Cursor cursor;
    static Camera camera;

    Game();
    ~Game();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    Map* map;
};
