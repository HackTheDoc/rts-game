#pragma once

#include "../../UI/UILevelBar.h"

#include "Entity.h"

class Tree : public Entity {
public:
    Tree();
    ~Tree();

    void update() override;
    void draw() override;
    void kill() override;
    
    void placeAt(const Vector2D& pos);

    Struct::Entity getStructure() override;

private:
    Vector2D entryPosition;

    Entity* lumberjack; // bucheron
    bool isLumberjackWorking;

    UILevelBar* level;

    void updateWithLumberjack();
    void updateWithoutLumberjack();

    void freeLumberjack();
};
