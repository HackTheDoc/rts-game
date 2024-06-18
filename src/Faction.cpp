#include "include/Game/Faction.h"

#include "include/struct.h"

std::array<std::array<int, 3>, 3> Faction::RessourceConsumptionOfBuildings = {
    std::array<int, 3>{50, 10, 20},
    std::array<int, 3>{25, 50, 100},
    std::array<int, 3>{200, 200, 200}
};

Faction::Faction(const std::string& n, const int f, const int g, const int w) {
    name = n;

    food = f;
    gold = g;
    wood = w;
    
    pawns.clear();
    warriors.clear();
    archers.clear();
    
    castles.clear();
}

Faction::~Faction() {
    pawns.clear();
    warriors.clear();
    archers.clear();

    castles.clear();
}


bool Faction::hasEnoughRessourcesFor(const Building::Type btype) {
    return  RessourceConsumptionOfBuildings[btype-1][0] <= food &&
            RessourceConsumptionOfBuildings[btype-1][1] <= gold &&
            RessourceConsumptionOfBuildings[btype-1][2] <= wood;
}   

void Faction::consumeRessourcesFor(const Building::Type btype) {
    food -= RessourceConsumptionOfBuildings[btype-1][0];
    gold -= RessourceConsumptionOfBuildings[btype-1][1];
    wood -= RessourceConsumptionOfBuildings[btype-1][2];
}

Struct::Faction Faction::getstructure() {
    return {name, food, gold, wood};
}
