#pragma once

#include "../../UI/UILabel.h"

#include "Building.h"

class Mine : public Building {
public:
    static const int MAX_CAPACITY;

    Mine(const Vector2D& pos);
    ~Mine() override;
    
    void update() override;
    void draw() override;
    void destroy() override;

    void freeMiner();
    
    Struct::Object getStructure() override;

private:
    UILabel* lbl_capacity;
    LevelBar* level;

    int capacity;

    Entity* miner;
    bool isMinerWorking;
    Vector2D entryPosition;

    void updateWithMiner();
    void updateWithoutMiner();
};
