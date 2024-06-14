#pragma once

#include "../WindowStates/WindowState.h"

class Game : public WindowState {
public:
    Game();
    ~Game();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
};
