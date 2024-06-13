#pragma once

#include <fstream>
#include <filesystem>

#include "struct.h"

namespace fs = std::filesystem;

namespace serialize {

    template <typename K, typename V>
    void map(std::ofstream& outfile, const std::map<K, V>& map);

    template <typename T1, typename T2>
    void pair(std::ofstream& outfile, const std::pair<T1, T2>& pair);

    template <typename T>
    void var(std::ofstream& outfile, const T& var);

    void config(const Struct::Config& config);
    
}; // namepsace serizalize

namespace deserialize {

    template <typename K, typename V>
    void map(std::ifstream& infile, std::map<K, V>& map);

    template<typename T1, typename T2>
    void pair(std::ifstream& infile, std::pair<T1, T2>& pair);

    template <typename T>
    void var(std::ifstream& infile, T& var);

    Struct::Config config();

}; // namespace deserialize
