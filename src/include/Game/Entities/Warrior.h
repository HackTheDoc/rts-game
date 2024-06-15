#pragma once

#include "Entity.h"

class Warrior : public Entity {
public:
    Warrior(const std::string& f);
    ~Warrior();

    Struct::Entity getStructure() override;
};
