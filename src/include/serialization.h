#pragma once

#include <fstream>
#include <filesystem>

#include "struct.h"

namespace fs = std::filesystem;

namespace serialize {
    template <typename T1, typename T2>
    void pair(std::ofstream& outfile, const std::pair<T1, T2>& pair);

    template <typename T>
    void var(std::ofstream& outfile, const T& var);

    void vector2D(std::ofstream& outfile, const Vector2D& v);

    void string(std::ofstream& outfile, const std::string& s);

    void archer(std::ofstream& outfile, const Struct::Archer& a);

    void warrior(std::ofstream& outfile, const Struct::Warrior& w);

    void pawn(std::ofstream& outfile, const Struct::Pawn& p);

    void tree(std::ofstream& outfile, const Struct::Tree& t);

    void entity(std::ofstream& outfile, const Struct::Entity& e);
    
    void construction(std::ofstream& outfile, const Struct::Construction& c);

    void house(std::ofstream& outfile, const Struct::House& h);
    
    void tower(std::ofstream& outfile, const Struct::Tower& t);

    void castle(std::ofstream& outfile, const Struct::Castle& c);

    void mine(std::ofstream& outfile, const Struct::Mine& m);

    void building(std::ofstream& outfile, const Struct::Building& b);

    void tile(std::ofstream& outfile, const Struct::Tile& t);

    void layer(std::ofstream& outfile, const Struct::Layer& l);

    void map(std::ofstream& outfile, const Struct::Map& m);

    void camera(std::ofstream& outfile, const Struct::Camera& c);

    void faction(std::ofstream& outfile, const Struct::Faction& f);

    void game(const Struct::Game& g, const fs::path& path);

    void config(const Struct::Config& config);
    
}; // namepsace serizalize

namespace deserialize {
    template<typename T1, typename T2>
    void pair(std::ifstream& infile, std::pair<T1, T2>& pair);

    template <typename T>
    void var(std::ifstream& infile, T& var);

    void vector2D(std::ifstream& infile, Vector2D& vec);

    void string(std::ifstream& infile, std::string& s);

    void archer(std::ifstream& infile, Struct::Archer& a);

    void warrior(std::ifstream& infile, Struct::Warrior& w);

    void pawn(std::ifstream& infile, Struct::Pawn& p);

    void tree(std::ifstream& infile, Struct::Tree& t);

    void entity(std::ifstream& infile, Struct::Entity& e);
    
    void construction(std::ifstream& infile, Struct::Construction& c);
    
    void house(std::ifstream& infile, Struct::House& h);
    
    void tower(std::ifstream& infile, Struct::Tower& t);
    
    void castle(std::ifstream& infile, Struct::Castle& c);

    void mine(std::ifstream& infile, Struct::Mine& m);

    void building(std::ifstream& infile, Struct::Building& b);

    void tile(std::ifstream& infile, Struct::Tile& t);

    void layer(std::ifstream& infile, Struct::Layer& l);

    void map(std::ifstream& infile, Struct::Map& m);

    void camera(std::ifstream& infile, Struct::Camera& c);

    void faction(std::ifstream& infile, Struct::Faction& f);

    void game(Struct::Game& g, const fs::path& path);

    Struct::Config config();

}; // namespace deserialize
