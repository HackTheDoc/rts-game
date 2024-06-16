#include "include/Game/Faction.h"

#include "include/struct.h"

Faction::Faction(const std::string& n, const int f, const int g, const int w) {
    name = n;

    food = f;
    gold = g;
    wood = w;
    
    pawns.clear();
    warriors.clear();
    archers.clear();
}

Faction::~Faction() {
    pawns.clear();
    warriors.clear();
    archers.clear();
}

Struct::Faction Faction::getstructure() {
    return {name, food, gold, wood};
}
