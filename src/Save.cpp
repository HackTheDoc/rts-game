#include "include/Save.h"
#include "include/serialization.h"

#include "include/Window.h"
#include "include/Game/Game.h"

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

bool Save::Auto = false;
bool Save::New = false;
std::string Save::pathToSaveFolder = "./data/";

/* ----- CONFIG ----- */

void Save::CreateConfig() {    
    Struct::Config config{
    .autosave = true,
    .window_mode = 0,
    .controls = {
            { EventID::MOVE_UP          , SDL_SCANCODE_W        },
            { EventID::MOVE_DOWN        , SDL_SCANCODE_S        },
            { EventID::MOVE_LEFT        , SDL_SCANCODE_A        },
            { EventID::MOVE_RIGHT       , SDL_SCANCODE_D        },
            { EventID::SELECT_MULTIPLE  , SDL_SCANCODE_LSHIFT   },
        }
    };

    serialize::config(config);
}

void Save::SaveConfig() {
    Struct::Config config = LoadConfig();

    config.autosave = Save::Auto;

    config.window_mode = 0;
    if (Window::fullscreen)
        config.window_mode = SDL_WINDOW_FULLSCREEN_DESKTOP;

    config.controls = Window::controls;

    serialize::config(config);
}

Struct::Config Save::LoadConfig() {
    if (!fs::exists("config")) CreateConfig();

    Struct::Config config = deserialize::config();

    return config;
}

/* ----- GAME ----- */

bool Save::Exist() {
    fs::path path(pathToSaveFolder+"game");
    return fs::exists(path);
}

Struct::Game Save::Create() {
    Save::New = true;    
    Struct::Game game{
        .camera = CreateCamera(0, 0),
        .map = CreateMap_Test(),
        .faction = CreateFaction("white")
    };
    serialize::game(game, pathToSaveFolder+"game");
    return game;
}

bool Save::Update() {
    if(!Exist()) return false;

    const Struct::Game game = Game::GetStructure();

    serialize::game(game, pathToSaveFolder + "game");

    return true;
}

bool Save::Erase() {
    if (!Exist()) return false;

    fs::remove(pathToSaveFolder + "game");

    return true;
}

Struct::Game Save::Load() {
    Save::New = false;
    
    if (!Exist()) {
        return Create();
    }

    Struct::Game game;
    deserialize::game(game, pathToSaveFolder+"game");

    return game;
}

/* ----- CREATION ----- */

    /* ----- UNCATEGORIZED ----- */

Struct::Camera Save::CreateCamera(const int x, const int y) {
    return {{x,y}, 1.0f};
}

Struct::Faction Save::CreateFaction(const std::string& name) {
    return {name}; 
}

    /* ----- ENTITIES ----- */

Struct::Object Save::CreatePawn(const std::string& faction, const int x, const int y) {
    const Struct::Pawn p{faction, {x*Tile::SIZE, y*Tile::SIZE}, false};
    return {p};
}

Struct::Object Save::CreateWarrior(const std::string& faction, const int x, const int y) {
    const Struct::Warrior w{faction, {x*Tile::SIZE, y*Tile::SIZE}, false};
    return {w};
}

Struct::Object Save::CreateArcher(const std::string& faction, const int x, const int y) {
    const Struct::Archer a{faction, {x*Tile::SIZE, y*Tile::SIZE}, false};
    return {a};
}

Struct::Object Save::CreateTree(const int x, const int y) {
    const Struct::Tree t{{x*Tile::SIZE, y*Tile::SIZE}, 10};
    return {t};
}

Struct::Object Save::CreateSheep(const int x, const int y) {
    const Struct::Sheep s{{x*Tile::SIZE, y*Tile::SIZE}};
    return {s};
}

    /* ----- BUILDINGS ----- */

/// TODO: change value to 100
Struct::Object Save::CreateCastle(const std::string& faction, const int x, const int y) {
    const Struct::Castle c{faction, {x, y},  500, 500, 500};
    return {c};
}

Struct::Object Save::CreateMine(const int x, const int y) {
    const Struct::Mine m{{x,y}};
    return {m};
}

    /* ----- MAPS ------ */

Struct::Tile Save::CreateTile(const TileType type, const int x, const int y) {
    if (type == TileType::FOAM)
        return {{x-1,y-1}, type};
    else
        return {{x,y}, type};
}

Struct::Layer Save::CreateLayer(const int mw, const int mh, const std::vector<std::vector<int>>& rlayer) {
    Struct::Layer l{{}};

    for (int y = 0; y < mh; y++)
        for (int x = 0; x < mw; x++)
            l.tiles.push_back(CreateTile(TileType(rlayer[y][x]), x, y));
    
    return l;
}

Struct::Map Save::CreateMap_Test() {
    const Struct::Map m{
        .name = "test",
        .width = 23,
        .height = 13,
        .layers = {
            CreateLayer(23,13, { // FOAM
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
                { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
                { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
                { 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
                { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
                { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
                { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
                { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2},
                { 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2},
                { 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2},
                { 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0},
                { 0, 0, 2, 2, 2, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2},
            }),
            CreateLayer(23,13, { // SAND
                {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
                { 21,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 22 },
                { 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 25 },
                { 27, 23, 23,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 25 },
                {  0, 24, 23, 23, 23, 23, 23,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 25 },
                { 21, 23, 23, 23, 23, 23, 23,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 23, 28 },
                { 24, 23, 23, 23, 23, 23, 23,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 25,  0 },
                { 24,  0,  0,  0,  0,  0, 23, 23, 23, 23,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 23, 22 },
                { 24, 23, 23, 23, 23, 23, 23, 23, 23, 23,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 25 },
                { 27, 26, 26, 26, 26, 23, 23, 23, 23, 28,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 25 },
                {  0,  0,  0,  0,  0, 27, 26, 26, 28,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 23, 23, 28 },
                { 19,  0, 21, 22,  0,  0,  0,  0,  0, 19,  0,  0,  0,  0,  0, 23, 23, 23, 23, 23, 23, 28,  0 },
                {  0,  0, 27, 26, 30,  0, 31, 30,  0,  0,  0,  0,  0,  0,  0, 27, 26, 26, 26, 26, 28,  0, 19 },
            }),
            CreateLayer(23,13, { // STONE
                { 0, 37, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 38,  0 },
                { 0, 40,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 41,  0 },
                { 0, 43, 39,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 41,  0 },
                { 0, 52, 43, 42, 42, 42, 42, 39,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 41,  0 },
                { 0,  0, 52, 53, 53, 53, 53, 40,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 39, 44,  0 },
                { 0,  0,  0,  0,  0,  0,  0, 40,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 39, 54,  0 },
                { 0, 37, 36, 36, 36, 36, 36, 42, 42, 42, 39,  0,  0,  0,  0,  0,  0,  0,  0,  0, 41,  0,  0 },
                { 0, 43, 42, 42, 42, 42, 44, 53, 53, 53, 43, 42, 42, 42, 39,  0,  0,  0,  0,  0, 39, 38,  0 },
                { 0, 52, 53, 53, 53, 53, 54,  0,  0,  0, 52, 53, 53, 53, 40,  0,  0,  0,  0,  0,  0, 41,  0 },
                { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 40,  0,  0,  0,  0, 39, 42, 44,  0 },
                { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 37, 38,  0, 43, 42, 42, 42, 42, 44, 53, 54,  0 },
                { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 43, 44,  0, 52, 53, 53, 53, 53, 54,  0,  0,  0 },
                { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 52, 54,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
            }),
            CreateLayer(23,13, { // GRASS
                { 0,  5,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  6,  0 },
                { 0,  8,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  9,  0 },
                { 0, 11,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  9,  0 },
                { 0,  0, 11, 10, 10, 10, 10,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  9,  0 },
                { 0,  0,  0,  0,  0,  0,  0,  8,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 12,  0 },
                { 0,  0,  0,  0,  0,  0,  0,  8,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  9,  0,  0 },
                { 0,  5,  4,  4,  4,  4,  4, 10, 10, 10,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  9,  0,  0 },
                { 0, 11, 10, 10, 10, 10, 12,  0,  0,  0, 11, 10, 10, 10,  7,  7,  7,  7,  7,  7,  7,  6,  0 },
                { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  7,  7,  7,  7,  7,  7,  9,  0 },
                { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  7,  7,  7,  7,  7, 10, 12,  0 },
                { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  6,  0, 11, 10, 10, 10, 10, 12,  0,  0,  0 },
                { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 11, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
                { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
            })
        },
        .objects = {
            CreateTree(16, 1),
            CreateTree(18, 1),
            CreateTree(20, 1),
            CreateTree(17, 2),
            CreateTree(19, 2),

            CreateSheep(8, 5),
            CreateSheep(10, 5),
            CreateSheep(11, 6),

            CreateWarrior("red", 10, 5),

            CreateCastle("white", 2, -2),
            CreateMine(18, 6),
        }
    };
    return m;
}
