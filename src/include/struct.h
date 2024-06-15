#pragma once

#include <map>
#include <SDL2/SDL.h>

#include "Event.h"

using EventID = Event::ID;
using KeyMap = std::map<Event::ID, SDL_Scancode>;

namespace Struct {
    struct Config {
        bool autosave;
        Uint32 window_mode;
        KeyMap controls;
    };

}; // namespace Struct
