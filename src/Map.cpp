#include "include/Game/Map/Map.h"

#include "include/Window.h"
#include "include/struct.h"
#include "include/Game/Game.h"
#include "include/Game/Components/Collision.h"

#include <algorithm>

int Map::TileSize() {
    return Tile::SIZE * Game::camera.zoom;
}

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

    // loading colliders
    std::vector<std::vector<bool>> map;
    map.resize(m_height, {});
    for (int i = 0; i < m_height; i++)
        map[i].resize(m_width, true);
    
    for (Tile* t : layers[LayerID::GRASS])
        map[t->position.y][t->position.x] = false;

    for (int y = 0; y < m_height; y++)
        for (int x = 0; x < m_width; x++)
            if (map[y][x])
                Game::AddCollider(Vector2D{x,y});

    for (const Struct::Entity& e : m.entities)
        addEntity(e);

    for (const Struct::Building& b : m.buildings)
        addBuilding(b);

    std::cout << "map initialized" << std::endl;
}

void Map::update() {
    updateLayer(LayerID::FOAM);
    updateLayer(LayerID::SAND);
    updateLayer(LayerID::STONE);
    updateLayer(LayerID::GRASS);

    for (Building* b : buildings)
        b->update();

    for (Entity* e : entities)
        e->update();
}

void Map::render() {
    renderLayer(LayerID::FOAM);
    renderLayer(LayerID::SAND);
    renderLayer(LayerID::STONE);
    renderLayer(LayerID::GRASS);

    for (Building* b : buildings)
        b->draw();

    for (Entity* e : entities)
        e->draw();
}

void Map::destroy() {
    for (Building* b : buildings)
        b->destroy();
    buildings.clear();

    for (Entity* e : entities)
        e->kill();
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
    return m_width;
}

int Map::height() {
    return m_height;
}

bool Map::isTileOccupied(const Vector2D& pos) {
    std::vector<Entity*>::iterator it = std::find_if(entities.begin(), entities.end(), [&pos](Entity* entity) {
        return entity->position == pos;
    });
    
    return it != entities.end();
}

std::vector<Entity*> Map::getEntities() {
    return entities;
}

std::vector<Entity*> Map::getEntitiesInRect(const SDL_Rect& rect) {
    std::vector<Entity*> temp;

    for (Entity* e : entities)
        if (e->state == Entity::State::FREE && Collision::AABB(e->collider, rect))
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
        {},
        {}
    };

    for (auto e : entities)
        m.entities.push_back(e->getStructure());

    for (auto B : buildings)
        m.buildings.push_back(B->getStructure());

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
            map->addPawn(p.faction, p.pos, p.selected, p.dest);
        }
        void operator()(const Struct::Warrior& w) {
            map->addWarrior(w.faction, w.pos, w.selected, w.dest);
        }
        void operator()(const Struct::Archer& a) {
            map->addArcher(a.faction, a.pos, a.selected, a.dest);
        }
        void operator()(const Struct::Tree& t) {
            map->addTree(t.pos, t.hp);
        }
    };

    EntityVisitor visitor{this};
    std::visit(visitor, e.e);
}

void Map::addEntity(Entity* e) {
    entities.push_back(e);
}

void Map::removeEntity(Entity* e) {
    std::vector<Entity*>::iterator it = std::find_if(entities.begin(), entities.end(), [&e](Entity* entity) {
        return entity == e;
    });

    if (it == entities.end()) return;

    entities.erase(it);
}

Pawn* Map::addPawn(const std::string& f, const Vector2D& pos, const bool selected, Vector2D dest) {
    Pawn* p = new Pawn(f);
    p->placeAt(pos);
    p->selected = selected;
    
    if (!dest.isZero())
        p->goTo(dest);
    
    addEntity(p);

    if (f == Game::playerFaction.name)
        Game::playerFaction.pawns.push_back(p);
    
    return p;
}

Warrior* Map::addWarrior(const std::string& f, const Vector2D& pos, const bool selected, Vector2D dest) {
    Warrior* w = new Warrior(f);
    w->placeAt(pos);
    w->selected = selected;
    
    if (!dest.isZero())
        w->goTo(dest);
    
    addEntity(w);

    if (f == Game::playerFaction.name)
        Game::playerFaction.warriors.push_back(w);
    
    return w;
}

Archer* Map::addArcher(const std::string& f, const Vector2D& pos, const bool selected, Vector2D dest) {
    Archer* a = new Archer(f);
    a->placeAt(pos);
    a->selected = selected;
    
    if (!dest.isZero())
        a->goTo(dest);
    
    addEntity(a);

    if (f == Game::playerFaction.name)
        Game::playerFaction.archers.push_back(a);

    return a;
}

Tree* Map::addTree(const Vector2D& pos, const int hp) {
    Tree* t = new Tree();
    t->placeAt(pos);
    t->hp = hp;
    
    addEntity(t);

    return t;
}

void Map::addBuilding(const Struct::Building& b) {
    struct BuildingVisitor {
        Map* map;

        void operator()(const Struct::Construction& c) {
            map->addConstruction(c.type, c.faction, c.pos, c.level, c.builder);
        }
        void operator()(const Struct::House& h) {
            map->addHouse(h.faction, h.pos);
        }
        void operator()(const Struct::Tower& t) {
            map->addTower(t.faction, t.pos);
        }
        void operator()(const Struct::Castle& c) {
            map->addCastle(c.faction, c.pos, c.foodStorage, c.goldStorage, c.woodStorage);
        }
        void operator()(const Struct::Mine& m) {
            map->addMine(m.pos);
        }
    };

    BuildingVisitor visitor{this};
    std::visit(visitor, b.b);
}

void Map::removeBuilding(const Vector2D& pos) {
    std::vector<Building*>::iterator it = std::find_if(buildings.begin(), buildings.end(), [&pos](Building* building) {
        return building->position == pos;
    });

    if (it == buildings.end()) return;

    (*it)->destroy();
    buildings.erase(it);
}

Construction* Map::addConstruction(const Building::Type type, const std::string& f, const Vector2D& pos, const int clevel) {
    Construction* c = new Construction(type, f, pos, clevel);
    buildings.push_back(c);
    return c;
}

void Map::addConstruction(const Building::Type type, const std::string& f, const Vector2D& pos, const int clevel, const Struct::Entity& builder) {
    Construction* c = new Construction(type, f, pos, clevel);

    addEntity(builder);
    c->addBuilder(entities.back());

    buildings.push_back(c);
}

void Map::addHouse(const std::string& f, const Vector2D& pos) {
    House* h = new House(f, pos);
    buildings.push_back(h);
}

void Map::addTower(const std::string& f, const Vector2D& pos) {
    Tower* t = new Tower(f, pos);    
    buildings.push_back(t);
}

void Map::addCastle(const std::string& f, const Vector2D& pos, const int foodStorage, const int goldStorage, const int woodStorage) {
    Castle* c = new Castle(f, pos);
    c->foodStorage = foodStorage;
    c->goldStorage = goldStorage;
    c->woodStorage = woodStorage;
    
    buildings.push_back(c);

    if (f == Game::playerFaction.name)
        Game::playerFaction.castles.push_back(c);
}

void Map::addMine(const Vector2D& pos) {
    Mine* m = new Mine(pos);
    buildings.push_back(m);
}
