#pragma once

#include "struct.h"

class Save {
public:
    /* ----- CONFIG ----- */

    static void SaveConfig();

    static Struct::Config LoadConfig();

    /* ----- GAME ----- */

    /// @brief autosave mode
    static bool Auto;

    /// @brief new game ?
    static bool New;

    static bool Exist();

    static Struct::Game Create();

    static bool Update();

    static bool Erase();

    static Struct::Game Load();

private:
    /// @brief path to the folder where the save are stored
    static std::string pathToSaveFolder;

    /* ----- CONFIG ----- */

    static void CreateConfig();

    /* ----- GAME ----- */

        /* ----- UNCATEGORIZED ----- */
    
    static Struct::Camera CreateCamera(const int x, const int y);

    static Struct::Faction CreateFaction(const std::string& name);

        /* ----- ENTITIES ----- */
    
    static Struct::Object CreatePawn(const std::string& faction, const int x, const int y);
    
    static Struct::Object CreateWarrior(const std::string& faction, const int x, const int y);
    
    static Struct::Object CreateArcher(const std::string& faction, const int x, const int y);

    static Struct::Object CreateTree(const int x, const int y);

    static Struct::Object CreateSheep(const int x, const int y);

        /* ----- BUILDINGS ----- */
    
    static Struct::Object CreateCastle(const std::string& faction, const int x, const int y);

    static Struct::Object CreateMine(const int x, const int y);

        /* ----- MAPS ------ */

    static Struct::Tile CreateTile(const TileType type, const int x, const int y);

    static Struct::Layer CreateLayer(const int mw, const int mh, const std::vector<std::vector<int>>& rlayer);

    static Struct::Map CreateMap_Test();
};
