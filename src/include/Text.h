#pragma once

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum Language : Uint8 {
    ENGLISH,
    FRENCH
};

class Text {
public:
    static Language language;

    /// @brief parse a text in the current language of the window
    /// @param tag text to translate
    /// @return
    static std::string Get(const std::string& tag);

private:
    /// @brief open the right translation file
    /// @return json structure with the translated texts
    static json OpenTranslation();
};
