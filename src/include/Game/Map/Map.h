#pragma once

#include <array>
#include <vector>
#include <optional>

#include "Tile.h"

#include "../Entities/Entities.h"

using Layer = std::vector<Tile*>;
using RawLayer = std::vector<std::vector<int>>;

enum LayerID {
    FOAM,
    SAND,
    STONE,
    GRASS,
    NUMBER_OF_LAYER
};

class Map {
public:
    Map();
    ~Map();

    void init(const std::string& mname);
    void update();
    void render();
    void destroy();

    int width();
    int height();

    std::vector<Entity*> getEntitiesInRect(const SDL_Rect& rect);
    std::optional<Entity*> getEntitiesAt(const Vector2D* pos);

private:
    std::string m_name;
    std::array<Layer, NUMBER_OF_LAYER> layers;
    int m_height, m_width;

    std::vector<Entity*> entities;

    void addTile(const LayerID lid, const int x, const int y, const Tile::Type ttype);

    void create(const int w, const int h, const std::array<RawLayer, NUMBER_OF_LAYER>& rmap);

    void createLayer(const LayerID lid, const RawLayer& rlayer);
    void updateLayer(const LayerID lid);
    void renderLayer(const LayerID lid);
    void destroyLayer(const LayerID lid);

    void createTestMap();
};
