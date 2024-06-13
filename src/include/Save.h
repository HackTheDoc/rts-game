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

private:
    /// @brief path to the folder where the save are stored
    static std::string pathToSaveFolder;

    /* ----- CONFIG ----- */

    static void CreateConfig();

};
