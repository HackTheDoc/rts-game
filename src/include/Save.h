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
    
    static Struct::Entity CreatePawn(const std::string& faction, const int x, const int y);
    
    static Struct::Entity CreateWarrior(const std::string& faction, const int x, const int y);
    
    static Struct::Entity CreateArcher(const std::string& faction, const int x, const int y);

    static Struct::Entity CreateTree(const int x, const int y);

    static Struct::Entity CreateSheep(const int x, const int y);

        /* ----- BUILDINGS ----- */
    
    static Struct::Building CreateCastle(const std::string& faction, const int x, const int y);

    static Struct::Building CreateMine(const int x, const int y);

        /* ----- MAPS ------ */

    static Struct::Tile CreateTile(const TileType type, const int x, const int y);

    static Struct::Layer CreateLayer(const int mw, const int mh, const std::vector<std::vector<int>>& rlayer);

    static Struct::Map CreateMap_Test();
};
