#pragma once

#include "Entity.h"

class Warrior : public Entity {
public:
    Warrior(const std::string& f);
    ~Warrior() override;

    Struct::Object getStructure() override;
};
