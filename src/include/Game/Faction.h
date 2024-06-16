#pragma once

#include <vector>

#include "Entities/Entities.h"

namespace Struct {
    struct Faction;
}

struct Faction {
    std::string name;

    int food;
    int gold;
    int wood;

    std::vector<Pawn*> pawns;
    std::vector<Warrior*> warriors;
    std::vector<Archer*> archers;

    Faction(const std::string& n = "undifined", const int f = 0, const int g = 0, const int w = 0);
    ~Faction();

    Struct::Faction getstructure();
};
