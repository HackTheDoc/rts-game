#include "include/Game/Faction.h"

#include "include/Game/Components/Heuristic.h"
#include "include/Game/Game.h"
#include "include/struct.h"

const std::array<std::array<int, 3>, 3> Faction::RessourceConsumptionOfBuildings = {
    std::array<int, 3>{50, 10, 20},
    std::array<int, 3>{25, 50, 100},
    std::array<int, 3>{200, 200, 200}
};

Faction::Faction(const std::string& n) {
    name = n;
    
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

void Faction::update() {
    food = gold = wood = 0;

    for (Castle* c : castles) {
        food += c->foodStorage;
        gold += c->goldStorage;
        wood += c->woodStorage;
    }
}

void Faction::storeFood(const int amount, Castle* c) {
    c->foodStorage += amount;
}

void Faction::storeFood(const int amount, const Vector2D& fromPos) {
    Castle* c = getNearestCastle(fromPos);

    if (c == nullptr) return;

    c->foodStorage += amount;
}

void Faction::storeGold(const int amount, const Vector2D& fromPos) {
    Castle* c = getNearestCastle(fromPos);

    if (c == nullptr) return;

    c->goldStorage += amount;
}

void Faction::storeWood(const int amount, const Vector2D& fromPos) {
    Castle* c = getNearestCastle(fromPos);

    if (c == nullptr) return;

    c->woodStorage += amount;
}

bool Faction::hasEnoughRessourcesFor(const Building::Type btype) {
    return  RessourceConsumptionOfBuildings[btype][0] <= food &&
            RessourceConsumptionOfBuildings[btype][1] <= gold &&
            RessourceConsumptionOfBuildings[btype][2] <= wood;
}   

void Faction::consumeRessourcesFor(const Building::Type btype) {
    consumeFood(RessourceConsumptionOfBuildings[btype][0]);
    consumeGold(RessourceConsumptionOfBuildings[btype][1]);
    consumeWood(RessourceConsumptionOfBuildings[btype][2]);
}

void Faction::consumeFood(int amount) {
    std::vector<Castle*> castle_buff;

    while (amount > 0) {
        const int i = getNearestCastleIndex(Game::builder.position);
        Castle* c = castles[i];
        castle_buff.push_back(c);
        castles.erase(castles.begin() + i);

        c->foodStorage -= amount;

        if (c->foodStorage < 0) {
            amount = -c->foodStorage;
            c->foodStorage = 0;
        }
        else amount = 0;
    }

    for (Castle* c : castle_buff)
        castles.push_back(c);
    castle_buff.clear();
}

void Faction::consumeGold(int amount) {
    std::vector<Castle*> castle_buff;

    while (amount > 0) {
        const int i = getNearestCastleIndex(Game::builder.position);
        Castle* c = castles[i];
        castle_buff.push_back(c);
        castles.erase(castles.begin() + i);

        c->goldStorage -= amount;

        if (c->goldStorage < 0) {
            amount = -c->goldStorage;
            c->goldStorage = 0;
        }
        else amount = 0;
    }

    for (Castle* c : castle_buff)
        castles.push_back(c);
    castle_buff.clear();
}

void Faction::consumeWood(int amount) {
    std::vector<Castle*> castle_buff;

    while (amount > 0) {
        const int i = getNearestCastleIndex(Game::builder.position);
        Castle* c = castles[i];
        castle_buff.push_back(c);
        castles.erase(castles.begin() + i);

        c->woodStorage -= amount;

        if (c->woodStorage < 0) {
            amount = -c->woodStorage;
            c->woodStorage = 0;
        }
        else amount = 0;
    }

    for (Castle* c : castle_buff)
        castles.push_back(c);
    castle_buff.clear();
}

Castle* Faction::getNearestCastle(const Vector2D& pos) {
    int i = getNearestCastleIndex(pos);
    if (i == -1) return nullptr;
    else return castles[i];    
}

Struct::Faction Faction::getstructure() {
    return {name};
}

int Faction::getNearestCastleIndex(const Vector2D& pos) {
    if (castles.empty()) return -1;

    uint j = 0;
    uint minDist = Heuristic::euclidean(pos, castles[0]->position);

    for (uint i = 1; i < castles.size(); i++) {
        uint dist = Heuristic::euclidean(pos, castles[i]->position);
        if (dist < minDist) {
            j = i;
            minDist = dist;
        }
    }

    return j;
}