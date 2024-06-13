#include "include/Text.h"

#include "include/Window.h"

#include <fstream>

Language Text::language = Language::ENGLISH;

std::string Text::Get(const std::string& tag) {
    if (language == Language::ENGLISH) return tag;

    const json data = OpenTranslation();

    const std::string t = data[tag];

    return t;
}



json Text::OpenTranslation() {
    std::string path = "./data/translations/";

    switch (language) {
    case Language::ENGLISH:
        path += "english.json";
        break;
    case Language::FRENCH:
        path += "french.json";
        break;
    default:
        break;
    }

    std::fstream infile(path);
    json data;
    infile >> data;
    infile.close();

    return data;
}
