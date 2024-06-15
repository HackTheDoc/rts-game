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

    static bool Exist();

    static void Create();

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

        /* ----- ENTITIES ----- */
    
    static Struct::Entity CreatePawn(const std::string& faction, const int x, const int y);
    
    static Struct::Entity CreateWarrior(const std::string& faction, const int x, const int y);
    
    static Struct::Entity CreateArcher(const std::string& faction, const int x, const int y);

        /* ----- MAPS ------ */

    static Struct::Tile CreateTile(const TileType type, const int x, const int y);

    static Struct::Layer CreateLayer(const int mw, const int mh, const std::vector<std::vector<int>>& rlayer);

    static Struct::Map CreateMap_Test();
};
