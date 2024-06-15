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
    
    static void ReleaseSelectedEntities();
    static void SelectEntities();
    static void SelectEntityAt(const Vector2D* pos);

private:
    static Map* map;
    static std::vector<Entity*> selectedEntities;
};
