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

    Faction(const std::string& n = "undifined");
    ~Faction();

    void update();

    void storeFood(const int amount, Castle* c);
    void storeFood(const int amount, const Vector2D& fromPos);
    void storeGold(const int amount, const Vector2D& fromPos);
    void storeWood(const int amount, const Vector2D& fromPos);
    
    bool hasEnoughRessourcesFor(const Building::Type btype);
    void consumeRessourcesFor(const Building::Type btype);

    Castle* getNearestCastle(const Vector2D& pos);

    Struct::Faction getstructure();

private:
    static std::array<std::array<int, 3>, 3> RessourceConsumptionOfBuildings;
    
    int getNearestCastleIndex(const Vector2D& pos);

    void consumeFood(int amount);
    void consumeGold(int amount);
    void consumeWood(int amount);
};
