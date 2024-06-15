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
        var(outfile, a.selected);
    }

    void warrior(std::ofstream& outfile, const Struct::Warrior& w) {
        var(outfile, Entity::Type::WARRIOR);
        
        string(outfile, w.faction);
        vector2D(outfile, w.pos);
        var(outfile, w.selected);
    }

    void pawn(std::ofstream& outfile, const Struct::Pawn& p) {
        var(outfile, Entity::Type::PAWN);
        
        string(outfile, p.faction);
        vector2D(outfile, p.pos);
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
        
        size_t size = m.entities.size();
        var(outfile, size);
        for (const Struct::Entity& e : m.entities)
            entity(outfile, e);
    }

    void camera(std::ofstream& outfile, const Struct::Camera& c) {
        vector2D(outfile, c.pos);
        var(outfile, c.zoom);
    }

    void game(const Struct::Game& g, const fs::path& path) {
        std::ofstream outfile(path, std::ios::binary);

        camera(outfile, g.camera);

        map(outfile, g.map);

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
        var(infile, a.selected);
    }

    void warrior(std::ifstream& infile, Struct::Warrior& w) {
        string(infile, w.faction);
        vector2D(infile, w.pos);
        var(infile, w.selected);
    }

    void pawn(std::ifstream& infile, Struct::Pawn& p) {
        string(infile, p.faction);
        vector2D(infile, p.pos);
        var(infile, p.selected);
    }

    void entity(std::ifstream& infile, Struct::Entity& e) {
        Entity::Type t{0};
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
        
        size_t size;
        var(infile, size);
        m.entities.resize(size);
        for (size_t i = 0; i < size; i++)
            entity(infile, m.entities[i]);
    }

    void camera(std::ifstream& infile, Struct::Camera& c) {
        vector2D(infile, c.pos);
        var(infile, c.zoom);
    }


    void game(Struct::Game& g, const fs::path& path) {
        std::ifstream infile(path, std::ios::binary);

        camera(infile, g.camera);

        map(infile, g.map);

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
