#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

class StartingUnitSelectionMenu : public WindowState {
public:
    static int avalaible;
    static UIUnitSelector* pawnSelector;
    static UIUnitSelector* warriorSelector;
    static UIUnitSelector* archerSelector;

    StartingUnitSelectionMenu();
    ~StartingUnitSelectionMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    UIButton* btn_valid;
};
