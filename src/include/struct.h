#pragma once

#include <map>
#include <variant>
#include <SDL2/SDL.h>

#include "Event.h"
#include "Game/Map/Map.h"

using EventID = Event::ID;
using KeyMap = std::map<Event::ID, SDL_Scancode>;
using TileType = Tile::Type;
using BuildingType = Building::Type;
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
    };

    struct Entity {
        std::variant<
            Archer,
            Warrior,
            Pawn
        > e;
    };

    struct Construction {
        std::string faction;
        Vector2D pos;
        int level;
        BuildingType type;
        Entity builder;
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
    };

    struct Mine {
        Vector2D pos;
    };

    struct Building {
        std::variant<
            Construction,
            House,
            Tower,
            Castle,
            Mine
        > b;
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
        std::vector<Entity> entities;
        std::vector<Building> buildings;
    };

    struct Camera {
        Vector2D pos;
        float zoom;
    };

    struct Faction {
        std::string name;
        int food;
        int gold;
        int wood;
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
