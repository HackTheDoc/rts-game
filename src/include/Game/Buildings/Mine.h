#pragma once

#include "../../UI/UILevelBar.h"
#include "../../UI/UILabel.h"

#include "Building.h"

class Mine : public Building {
public:
    static const int MAX_CAPACITY;

    Mine(const Vector2D& pos);
    ~Mine();
    
    void update() override;
    void draw() override;
    void destroy() override;

    void freeMiner();
    
    Struct::Building getStructure() override;

private:
    UILabel* lbl_capacity;
    UILevelBar* level;

    int capacity;

    Entity* miner;
    bool isMinerWorking;
    Vector2D entryPosition;

    void updateWithMiner();
    void updateWithoutMiner();
};
