#include "include/Game/Map/Map.h"

#include "include/Window.h"
#include "include/struct.h"
#include "include/Game/Game.h"
#include "include/Game/Components/Collision.h"

Map::Map() {
    m_name = "undefined";
    m_height = 0;
    m_width = 0;
}

Map::~Map() {}

void Map::init(const Struct::Map& m) {
    m_name = m.name;
    m_width = m.width;
    m_height = m.height;

    loadLayer(FOAM, m.layers[FOAM]);
    loadLayer(SAND, m.layers[SAND]);
    loadLayer(STONE, m.layers[STONE]);
    loadLayer(GRASS, m.layers[GRASS]);

    for (const Struct::Entity& e : m.entities)
        addEntity(e);
}

void Map::update() {
    updateLayer(LayerID::FOAM);
    updateLayer(LayerID::SAND);
    updateLayer(LayerID::STONE);
    updateLayer(LayerID::GRASS);

    for (Entity* e : entities)
        e->update();
}

void Map::render() {
    renderLayer(LayerID::FOAM);
    renderLayer(LayerID::SAND);
    renderLayer(LayerID::STONE);
    renderLayer(LayerID::GRASS);

    for (Entity* e : entities)
        e->draw();
}

void Map::destroy() {
    for (Entity* e : entities) {
        e->kill();
    }
    entities.clear();

    destroyLayer(LayerID::FOAM);
    destroyLayer(LayerID::SAND);
    destroyLayer(LayerID::STONE);
    destroyLayer(LayerID::GRASS);
    
    m_name = "undefined";
    m_height = 0;
    m_width = 0;
}

int Map::width() {
    return m_width * Tile::SIZE;
}

int Map::height() {
    return m_height * Tile::SIZE;
}

std::vector<Entity*> Map::getEntitiesInRect(const SDL_Rect& rect) {
    std::vector<Entity*> temp;

    for (Entity* e : entities)
        if (Collision::AABB(e->collider, rect))
            temp.push_back(e);

    return temp;
}

std::optional<Entity*> Map::getEntitiesAt(const Vector2D* pos) {
    for (Entity* e : entities)
        if (PointInRect(pos, &e->collider->rect))
            return e;
    return {};
}

void Map::addTile(const LayerID lid, const Vector2D& pos, const Tile::Type ttype) {
    if (ttype == Tile::Type::NONE) return;

    if (ttype == Tile::Type::FOAM) {
        Foam* t = new Foam();
        t->place(pos);
        layers[lid].push_back(t);

    }
    else {
        Tile* t = new Tile(ttype);
        t->place(pos);
        layers[lid].push_back(t);
    }
}

void Map::loadLayer(const LayerID lid, const Struct::Layer& l) {
    for (const Struct::Tile& t : l.tiles)
        addTile(lid, t.pos, t.type);
}

void Map::updateLayer(const LayerID lid) {
    for (auto t : layers[lid])
        t->update();
}

void Map::renderLayer(const LayerID lid) {
    for (auto t : layers[lid])
        t->draw();
}

void Map::destroyLayer(const LayerID lid) {
    for (auto t : layers[lid])
        t->destroy();
    layers[lid].clear();
}

Struct::Map Map::getStructure() {
    Struct::Map m{
        m_name,
        m_width,
        m_height,
        {
            getLayerStructure(LayerID::FOAM),
            getLayerStructure(LayerID::SAND),
            getLayerStructure(LayerID::STONE),
            getLayerStructure(LayerID::GRASS)
        },
        {}
    };

    for (auto e : entities)
        m.entities.push_back(e->getStructure());

    return m;
}

Struct::Layer Map::getLayerStructure(const LayerID lid) {
    Struct::Layer l;
    l.tiles.resize(layers[lid].size());
    
    for (size_t i = 0; i < layers[lid].size(); i++)
        l.tiles[i] = layers[lid][i]->getStructure();
    
    return l;
}

void Map::addEntity(const Struct::Entity& e) {
    struct EntityVisitor {
        Map* map;

        void operator()(const Struct::Pawn& p) {
            map->addPawn(p.faction, p.pos, p.selected);
        }
        void operator()(const Struct::Warrior& w) {
            map->addWarrior(w.faction, w.pos, w.selected);
        }
        void operator()(const Struct::Archer& a) {
            map->addArcher(a.faction, a.pos, a.selected);
        }
    };

    EntityVisitor visitor{this};
    std::visit(visitor, e.e);
}

void Map::addPawn(const std::string& f, const Vector2D& pos, const bool selected) {
    Pawn* p = new Pawn(f);
    p->placeAt(pos);
    p->selected = selected;
    
    entities.push_back(p);

    if (f == Game::playerFaction.name)
        Game::playerFaction.pawns.push_back(p);
}

void Map::addWarrior(const std::string& f, const Vector2D& pos, const bool selected) {
    Warrior* w = new Warrior(f);
    w->placeAt(pos);
    w->selected = selected;
    
    entities.push_back(w);

    if (f == Game::playerFaction.name)
        Game::playerFaction.warriors.push_back(w);
}

void Map::addArcher(const std::string& f, const Vector2D& pos, const bool selected) {
    Archer* a = new Archer(f);
    a->placeAt(pos);
    a->selected = selected;
    
    entities.push_back(a);

    if (f == Game::playerFaction.name)
        Game::playerFaction.archers.push_back(a);
}
