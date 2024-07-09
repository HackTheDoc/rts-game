#pragma once

#include <fstream>
#include <filesystem>

#include "struct.h"

namespace fs = std::filesystem;

namespace serialize {
    void game(const Struct::Game& g, const fs::path& path);

    void config(const Struct::Config& config);
    
}; // namepsace serizalize

namespace deserialize {
    void game(Struct::Game& g, const fs::path& path);

    Struct::Config config();

}; // namespace deserialize
