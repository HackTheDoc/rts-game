#pragma once

#include <array>
#include <vector>
#include <optional>

#include "Tile.h"

#include "../Entities/Entities.h"
#include "../Buildings/Buildings.h"

using Layer = std::vector<Tile*>;

enum LayerID {
    FOAM,
    SAND,
    STONE,
    GRASS,
    NUMBER_OF_LAYER
};

namespace Struct {
    struct Map;
    struct Layer;
    struct Entity;
    struct Building;
}

class Map {
public:
    Map();
    ~Map();

    void init(const Struct::Map& m);
    void update();
    void render();
    void destroy();

    int width();
    int height();

    void addPawn(const std::string& f, const Vector2D& pos, const bool selected = false);
    void addWarrior(const std::string& f, const Vector2D& pos, const bool selected = false);
    void addArcher(const std::string& f, const Vector2D& pos, const bool selected = false);

    void addHouse(const std::string& f, const Vector2D& pos);
    void addTower(const std::string& f, const Vector2D& pos);
    void addCastle(const std::string& f, const Vector2D& pos);

    std::vector<Entity*> getEntities();
    std::vector<Entity*> getEntitiesInRect(const SDL_Rect& rect);
    std::optional<Entity*> getEntitiesAt(const Vector2D* pos);

    Struct::Map getStructure();

    static int TileSize();

private:
    std::string m_name;
    std::array<Layer, NUMBER_OF_LAYER> layers;
    int m_height, m_width;

    std::vector<Entity*> entities;
    std::vector<Building*> buildings;

    void addTile(const LayerID lid, const Vector2D& pos, const Tile::Type ttype);

    void loadLayer(const LayerID lid, const Struct::Layer& l);
    void updateLayer(const LayerID lid);
    void renderLayer(const LayerID lid);
    void destroyLayer(const LayerID lid);

    Struct::Layer getLayerStructure(const LayerID lid);
    
    void addEntity(const Struct::Entity& e);
    void addBuilding(const Struct::Building& b);
};
