#pragma once

#include <vector>

#include "Entities/Entities.h"
#include "Buildings/Buildings.h"

namespace Struct {
    struct Faction;
}

class Faction {
public:
    std::string name;

    int food;
    int gold;
    int wood;

    std::vector<Pawn*> pawns;
    std::vector<Warrior*> warriors;
    std::vector<Archer*> archers;

    std::vector<Castle*> castles;

    Faction(const std::string& n = "undifined", const int f = 0, const int g = 0, const int w = 0);
    ~Faction();
    
    bool hasEnoughRessourcesFor(const Building::Type btype);
    void consumeRessourcesFor(const Building::Type btype);

    Struct::Faction getstructure();

private:
    static std::array<std::array<int, 3>, 3> RessourceConsumptionOfBuildings;
};
