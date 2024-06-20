#include "include/serialization.h"

#include <iostream>

namespace serialize {
    template<typename T1, typename T2>
    void pair(std::ofstream& outfile, const std::pair<T1, T2>& pair) {
        size_t fsize = pair.first.size();
        var(outfile, fsize);
        outfile.write(pair.first.data(), fsize);

        size_t ssize = pair.second.size();
        var(outfile, ssize);
        outfile.write(pair.second.data(), ssize);
    }

    template <typename T>
    void var(std::ofstream& outfile, const T& var) {
        outfile.write(reinterpret_cast<const char*>(&var), sizeof(T));
    }

    void vector2D(std::ofstream& outfile, const Vector2D& v) {
        var(outfile, v.x);
        var(outfile, v.y);
    }

    void string(std::ofstream& outfile, const std::string& s) {
        size_t size = s.size();
        var(outfile, size);
        outfile.write(s.data(), size);
    }

    void archer(std::ofstream& outfile, const Struct::Archer& a) {
        var(outfile, Entity::Type::ARCHER);

        string(outfile, a.faction);
        vector2D(outfile, a.pos);
        vector2D(outfile, a.dest);
        var(outfile, a.selected);
    }

    void warrior(std::ofstream& outfile, const Struct::Warrior& w) {
        var(outfile, Entity::Type::WARRIOR);
        
        string(outfile, w.faction);
        vector2D(outfile, w.pos);
        vector2D(outfile, w.dest);
        var(outfile, w.selected);
    }

    void pawn(std::ofstream& outfile, const Struct::Pawn& p) {
        var(outfile, Entity::Type::PAWN);
        
        string(outfile, p.faction);
        vector2D(outfile, p.pos);
        vector2D(outfile, p.dest);
        var(outfile, p.selected);
    }

    void entity(std::ofstream& outfile, const Struct::Entity& e) {
        struct EntityVisitor {
            std::ofstream& outfile;

            void operator()(const Struct::Archer& a) {
                serialize::archer(outfile, a);
            }
            void operator()(const Struct::Warrior& w) {
                serialize::warrior(outfile, w);
            }
            void operator()(const Struct::Pawn& p) {
                serialize::pawn(outfile, p);
            }
        };

        EntityVisitor visitor{outfile};
        std::visit(visitor, e.e);
    }

    void construction(std::ofstream& outfile, const Struct::Construction& c) {
        var(outfile, Building::Type::CONSTRUCTION);
        
        string(outfile, c.faction);
        vector2D(outfile, c.pos);
        var(outfile, c.type);
        var(outfile, c.level);
        entity(outfile, c.builder);
    }
    
    void house(std::ofstream& outfile, const Struct::House& h) {
        var(outfile, Building::Type::HOUSE);
        
        string(outfile, h.faction);
        vector2D(outfile, h.pos);
    }
    
    void tower(std::ofstream& outfile, const Struct::Tower& t) {
        var(outfile, Building::Type::TOWER);
        
        string(outfile, t.faction);
        vector2D(outfile, t.pos);
    }
    
    void castle(std::ofstream& outfile, const Struct::Castle& c) {
        var(outfile, Building::Type::CASTLE);
        
        string(outfile, c.faction);
        vector2D(outfile, c.pos);
    }

    void mine(std::ofstream& outfile, const Struct::Mine& m) {
        var(outfile, Building::Type::MINE);
        
        vector2D(outfile, m.pos);
    }

    void building(std::ofstream& outfile, const Struct::Building& b) {
        struct BuildingVisitor {
            std::ofstream& outfile;

            void operator()(const Struct::Construction& c) {
                serialize::construction(outfile, c);
            }
            void operator()(const Struct::House& h) {
                serialize::house(outfile, h);
            }
            void operator()(const Struct::Tower& t) {
                serialize::tower(outfile, t);
            }
            void operator()(const Struct::Castle& c) {
                serialize::castle(outfile, c);
            }
            void operator()(const Struct::Mine& m) {
                serialize::mine(outfile, m);
            }
        };

        BuildingVisitor visitor{outfile};
        std::visit(visitor, b.b);
    }

    void tile(std::ofstream& outfile, const Struct::Tile& t) {
        vector2D(outfile, t.pos);
        var(outfile, t.type);
    }

    void layer(std::ofstream& outfile, const Struct::Layer& l) {
        size_t size = l.tiles.size();
        var(outfile, size);

        for (const Struct::Tile& t : l.tiles)
            tile(outfile, t);
    }

    void map(std::ofstream& outfile, const Struct::Map& m) {
        string(outfile, m.name);

        var(outfile, m.width);
        var(outfile, m.height);

        for (const Struct::Layer& l : m.layers)
            layer(outfile, l);
        
        size_t esize = m.entities.size();
        var(outfile, esize);
        for (const Struct::Entity& e : m.entities)
            entity(outfile, e);
        
        size_t bsize = m.buildings.size();
        var(outfile, bsize);
        for (const Struct::Building& b : m.buildings)
            building(outfile, b);
    }

    void camera(std::ofstream& outfile, const Struct::Camera& c) {
        vector2D(outfile, c.pos);
        var(outfile, c.zoom);
    }

    void faction(std::ofstream& outfile, const Struct::Faction& f) {
        string(outfile, f.name);
        var(outfile, f.food);
        var(outfile, f.gold);
        var(outfile, f.wood);
    }

    void game(const Struct::Game& g, const fs::path& path) {
        std::ofstream outfile(path, std::ios::binary);

        camera(outfile, g.camera);

        map(outfile, g.map);

        faction(outfile, g.faction);

        outfile.close();
    }

    void config(const Struct::Config& config) {
        std::ofstream outfile("config", std::ios::binary);

        var(outfile, config.autosave);

        var(outfile, config.window_mode);

        const size_t mcsize = config.controls.size();
        outfile.write(reinterpret_cast<const char*>(&mcsize), sizeof(size_t));

        for (const auto& [key, value] : config.controls) {
            outfile.write(reinterpret_cast<const char*>(&key), sizeof(Event::ID));
            outfile.write(reinterpret_cast<const char*>(&value), sizeof(SDL_Scancode));
        }

        outfile.close();
    }

}; // namespace serialize

namespace deserialize {
    template<typename T1, typename T2>
    void pair(std::ifstream& infile, std::pair<T1, T2>& pair) {
        size_t fsize;
        var(infile, fsize);
        std::string firstData(fsize, '\0');
        infile.read(&firstData[0], fsize);
        pair.first = std::move(firstData);

        size_t ssize;
        var(infile, ssize);
        std::string secondData(ssize, '\0');
        infile.read(&secondData[0], ssize);
        pair.second = std::move(secondData);
    }

    template <typename T>
    void var(std::ifstream& infile, T& var) {
        infile.read(reinterpret_cast<char*>(&var), sizeof(T));
    }

    void vector2D(std::ifstream& infile, Vector2D& v) {
        var(infile, v.x);
        var(infile, v.y);
    }

    void string(std::ifstream& infile, std::string& s) {
        size_t size;
        var(infile, size);
        s.resize(size);
        infile.read(&s[0], size);
    }

    void archer(std::ifstream& infile, Struct::Archer& a) {
        string(infile, a.faction);
        vector2D(infile, a.pos);
        vector2D(infile, a.dest);
        var(infile, a.selected);
    }

    void warrior(std::ifstream& infile, Struct::Warrior& w) {
        string(infile, w.faction);
        vector2D(infile, w.pos);
        vector2D(infile, w.dest);
        var(infile, w.selected);
    }

    void pawn(std::ifstream& infile, Struct::Pawn& p) {
        string(infile, p.faction);
        vector2D(infile, p.pos);
        vector2D(infile, p.dest);
        var(infile, p.selected);
    }

    void entity(std::ifstream& infile, Struct::Entity& e) {
        Entity::Type t{Entity::Type::UNKNOWN};
        var(infile, t);
        switch (t) {
        case Entity::Type::ARCHER:
            e.e = Struct::Archer{};
            break;
        case Entity::Type::WARRIOR:
            e.e = Struct::Warrior{};
            break;
        case Entity::Type::PAWN:
            e.e = Struct::Pawn{};
            break;
        default:
            break;
        }

        struct EntityVisitor {
            std::ifstream& infile;

            void operator()(Struct::Archer& a) {
                deserialize::archer(infile, a);
            }
            void operator()(Struct::Warrior& w) {
                deserialize::warrior(infile, w);
            }
            void operator()(Struct::Pawn& p) {
                deserialize::pawn(infile, p);
            }
        };

        EntityVisitor visitor{infile};
        std::visit(visitor, e.e);
    }

    void construction(std::ifstream& infile, Struct::Construction& c) {
        string(infile, c.faction);
        vector2D(infile, c.pos);
        var(infile, c.type);
        var(infile, c.level);
        entity(infile, c.builder);
    }

    void house(std::ifstream& infile, Struct::House& h) {
        string(infile, h.faction);
        vector2D(infile, h.pos);
    }

    void tower(std::ifstream& infile, Struct::Tower& t) {
        string(infile, t.faction);
        vector2D(infile, t.pos);
    }

    void castle(std::ifstream& infile, Struct::Castle& c) {
        string(infile, c.faction);
        vector2D(infile, c.pos);
    }

    void mine(std::ifstream& infile, Struct::Mine& m) {
        vector2D(infile, m.pos);
    }

    void building(std::ifstream& infile, Struct::Building& b) {
        Building::Type t;
        var(infile, t);
        switch (t) {
        case Building::Type::CONSTRUCTION:
            b.b = Struct::Construction{};
            break;
        case Building::Type::HOUSE:
            b.b = Struct::House{};
            break;
        case Building::Type::TOWER:
            b.b = Struct::Tower{};
            break;
        case Building::Type::CASTLE:
            b.b = Struct::Castle{};
            break;
        case Building::Type::MINE:
            b.b = Struct::Mine{};
            break;
        default:
            break;
        }

        struct BuildingVisitor {
            std::ifstream& infile;

            void operator()(Struct::Construction& c) {
                deserialize::construction(infile, c);
            }
            void operator()(Struct::House& h) {
                deserialize::house(infile, h);
            }
            void operator()(Struct::Tower& t) {
                deserialize::tower(infile, t);
            }
            void operator()(Struct::Castle& c) {
                deserialize::castle(infile, c);
            }
            void operator()(Struct::Mine& m) {
                deserialize::mine(infile, m);
            }
        };

        BuildingVisitor visitor{infile};
        std::visit(visitor, b.b);
    }

    void tile(std::ifstream& infile, Struct::Tile& t) {
        vector2D(infile, t.pos);
        var(infile, t.type);
    }

    void layer(std::ifstream& infile, Struct::Layer& l) {
        size_t size;
        var(infile, size);

        l.tiles.resize(size);
        for (size_t i = 0; i < size; i++)
            tile(infile, l.tiles[i]);
    }

    void map(std::ifstream& infile, Struct::Map& m) {
        string(infile, m.name);

        var(infile, m.width);
        var(infile, m.height);

        for (Struct::Layer& l : m.layers)
            layer(infile, l);
        
        size_t esize;
        var(infile, esize);
        m.entities.resize(esize);
        for (size_t i = 0; i < esize; i++)
            entity(infile, m.entities[i]);
        
        size_t bsize;
        var(infile, bsize);
        m.buildings.resize(bsize);
        for (size_t i = 0; i < bsize; i++)
            building(infile, m.buildings[i]);
    }

    void camera(std::ifstream& infile, Struct::Camera& c) {
        vector2D(infile, c.pos);
        var(infile, c.zoom);
    }

    void faction(std::ifstream& infile, Struct::Faction& f) {
        string(infile, f.name);
        var(infile, f.food);
        var(infile, f.gold);
        var(infile, f.wood);
    }

    void game(Struct::Game& g, const fs::path& path) {
        std::ifstream infile(path, std::ios::binary);

        camera(infile, g.camera);

        map(infile, g.map);

        faction(infile, g.faction);

        infile.close();
    }

    Struct::Config config() {
        Struct::Config cstruct;

        std::ifstream infile("config", std::ios::binary);

        var(infile, cstruct.autosave);

        var(infile, cstruct.window_mode);

        size_t mcsize;
        infile.read(reinterpret_cast<char*>(&mcsize), sizeof(size_t));

        for (size_t i = 0; i < mcsize; ++i) {
            Event::ID key;
            infile.read(reinterpret_cast<char*>(&key), sizeof(Event::ID));
            SDL_Scancode value;
            infile.read(reinterpret_cast<char*>(&value), sizeof(SDL_Scancode));

            cstruct.controls[key] = value;
        }

        infile.close();

        return cstruct;
    }

}; // namepsace deserialize
