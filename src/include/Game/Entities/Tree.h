#pragma once

#include "Entity.h"

class Tree : public Entity {
public:
    Tree();
    ~Tree() override;

    void update() override;
    void draw() override;
    void destroy() override;

    void placeAt(const Vector2D& pos);

    Struct::Object getStructure() override;

private:
    Vector2D entryPosition;

    Entity* lumberjack; // bucheron
    bool isLumberjackWorking;

    void updateWithLumberjack();
    void updateWithoutLumberjack();

    void freeLumberjack();
};
