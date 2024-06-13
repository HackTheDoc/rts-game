#include "include/Save.h"
#include "include/serialization.h"

#include "include/Window.h"

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

bool Save::Auto = false;
std::string Save::pathToSaveFolder = "./data/";

/* ----- CONFIG ----- */

void Save::CreateConfig() {
    Struct::Config config{
    .autosave = true,
    .language = Language::ENGLISH,
    .window_mode = 0,
    .controls = {
            {SDLK_z         , EventID::MOVE_CAMERA_UP            },
            {SDLK_s         , EventID::MOVE_CAMERA_DOWN          },
            {SDLK_q         , EventID::MOVE_CAMERA_LEFT          },
            {SDLK_d         , EventID::MOVE_CAMERA_RIGHT         },
        }
    };

    serialize::config(config);
}

void Save::SaveConfig() {
    Struct::Config config = LoadConfig();

    config.autosave = Save::Auto;

    config.language = Text::language;

    config.window_mode = 0;
    if (Window::fullscreen)
        config.window_mode = SDL_WINDOW_FULLSCREEN_DESKTOP;

    //config.controls = KeyMap::Key;

    serialize::config(config);
}

Struct::Config Save::LoadConfig() {
    if (!fs::exists("config")) CreateConfig();

    Struct::Config config = deserialize::config();

    return config;
}
