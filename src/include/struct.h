#pragma once

#include <map>
#include <SDL2/SDL.h>

#include "Event.h"

using EventID = Event::ID;

namespace Struct {
    struct Config {
        bool autosave;
        Uint32 window_mode;
        std::map<SDL_KeyCode, EventID> controls;
    };

}; // namespace Struct
