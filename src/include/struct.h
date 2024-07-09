#pragma once

#include <map>
#include <variant>
#include <SDL2/SDL.h>

#include "Event.h"
#include "Game/Map/Map.h"

using EventID = Event::ID;
using KeyMap = std::map<Event::ID, SDL_Scancode>;
using TileType = Tile::Type;
using ObjectType = Object::Type;
using EntityState = Entity::State;

namespace Struct {
    struct Archer {
        std::string faction;
        Vector2D pos;
        bool selected;
        Vector2D dest;
    };

    struct Warrior {
        std::string faction;
        Vector2D pos;
        bool selected;
        Vector2D dest;
    };

    struct Pawn {
        std::string faction;
        Vector2D pos;
        bool selected;
        Vector2D dest;
        bool carryingSheep;
    };

    struct Tree {
        Vector2D pos;
        int hp;
    };

    struct Sheep {
        Vector2D pos;
    };

    struct UnknownEntity {};
    
    struct Construction  {
        std::string faction;
        Vector2D pos;
        int level;
        ObjectType type;
        Pawn builder;
    };

    struct House {
        std::string faction;
        Vector2D pos;
    };
    
    struct Tower {
        std::string faction;
        Vector2D pos;
    };

    struct Castle {
        std::string faction;
        Vector2D pos;
        int foodStorage;
        int goldStorage;
        int woodStorage;
    };

    struct Mine {
        Vector2D pos;
    };

    struct UnknownBuilding {};

    struct UnknownObject {};

    struct Object {
        std::variant<
            UnknownObject,
            UnknownEntity,
            UnknownBuilding,
            Archer,
            Warrior,
            Pawn,
            Tree,
            Sheep,
            Construction,
            House,
            Tower,
            Castle,
            Mine
        > o;
    };

    struct Tile {
        Vector2D pos;
        TileType type;
    };

    struct Layer {
        std::vector<Tile> tiles;
    };

    struct Map {
        std::string name;
        int width;
        int height;
        std::array<Layer, NUMBER_OF_LAYER> layers;
        std::vector<Object> objects;
    };

    struct Camera {
        Vector2D pos;
        float zoom;
    };

    struct Faction {
        std::string name;
    };

    struct Game {
        Camera camera;
        Map map;
        Faction faction;
    };

    struct Config {
        bool autosave;
        Uint32 window_mode;
        KeyMap controls;
    };

}; // namespace Struct

using ObjectStructure = Struct::Object;
