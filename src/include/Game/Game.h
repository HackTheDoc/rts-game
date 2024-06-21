#pragma once

#include "Components/AStar.h"

#include "Cursor.h"
#include "Camera.h"
#include "Components/Builder.h"

#include "../UI/UI.h"

#include "Map/Map.h"
#include "Faction.h"

#include "../WindowStates/WindowState.h"

namespace Struct {
    struct Game;
}

class Game : public WindowState {
public:
    static AStar::Generator generator;

    static Cursor cursor;
    static Camera camera;
    
    static Builder builder;

    static UI* ui;

    static Faction playerFaction;

    Game();
    ~Game();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

    static void AddUnitsFromBuilding(const int pawnCount, const int warriorCount, const int archerCount);
    static void AddEntity(Entity* e);
    static void RemoveEntity(Entity* e);
    
    static void ActiveBuilder(const Building::Type type);
    static void AddBuilding(const Building::Type type, const Vector2D& pos, const std::string& fac);
    static void BeginConstruction(const Building::Type type, const Vector2D& pos, const std::string& fac);
    static void FinishConstruction(const Building::Type type, const Vector2D& pos, const std::string& fac);

    static Entity* GetSelectedEntity(const int i = 0);
    static int CountSelectedEntities();
    static void ReleaseSelectedEntities();
    static void SelectEntities();
    static void SelectEntityAt(const Vector2D* pos);

    static int GetSelectedBuildingFreeSpace();
    static void SelectBuilding(Building* b);

    static Struct::Game GetStructure();

    static Vector2D GetMapSize();
    static std::vector<Entity*> GetEntities();
        
    static void AddCollider(const Vector2D& pos);
    static void RemoveCollider(const Vector2D& pos);
    static std::vector<Vector2D> FindPath(const Vector2D& start, const Vector2D& end);

    static bool IsAllowedPosition(const Vector2D& pos);
    static bool IsTileOccupied(const Vector2D& pos);

private:
    static Building* selectedBuilding;
    
    static Map* map;
    static std::vector<Entity*> selectedEntities;
};
