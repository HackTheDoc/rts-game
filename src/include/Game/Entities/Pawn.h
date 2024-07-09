#pragma once

#include "Entity.h"

namespace Struct {
    struct Pawn;
}

class Pawn : public Entity {
public:
    Pawn(const std::string& f);
    ~Pawn() override;

    void draw() override;
    void update() override;

    Struct::Pawn getDirectStructure();
    Struct::Object getStructure() override;
};
